package org.nmelihsensoy.streamviewer;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.animation.ValueAnimator;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Toast;

import org.freedesktop.gstreamer.GStreamer;
import org.nmelihsensoy.streamviewer.databinding.ActivityMainBinding;

import java.io.File;
import java.io.IOException;
import java.util.Locale;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    private ValueAnimator stateTextAnimator;
    private SurfaceView surfaceView;
    private ActivityMainBinding binding;
    private ServerURLHandler serverURLHandler;
    private String modelAssetPath = "";
    private static String hlsSegmentPath;
    private static String hlsPlaylistPath;
    private ExecutorService executor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        shouldHideSystemUI();
        setContentView(binding.getRoot());

        try {
            GStreamer.init(this);
            nativeInit(this);
            shouldDebugPrint();
        } catch (Exception e) {
            Toast.makeText(this, e.getMessage(), Toast.LENGTH_LONG).show();
            finish();
            return;
        }

        serverURLHandler = new ServerURLHandler(this);
        Log.i(TAG, "Stored Server URL: "+ serverURLHandler.getServerUrl().toString()+" host:"+ serverURLHandler.getServerUrl().getHost());

        surfaceView = binding.gstreamerSurface;
        surfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(@NonNull SurfaceHolder holder) {
                setSurface(holder.getSurface());
            }

            @Override
            public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int width, int height) {
            }

            @Override
            public void surfaceDestroyed(@NonNull SurfaceHolder holder) {
            }
        });

        binding.btnConnect.setOnClickListener(v -> serverURLHandler.showServerUrlDialog(isUrlChanged -> {
            if (isUrlChanged) {
                Log.i(TAG, "URL changed. ");
            } else {
                Log.i(TAG, "URL unchanged or canceled");
            }
        }));
        binding.btnTest.setOnClickListener(v -> connectToStreamUi());
        executor = Executors.newSingleThreadExecutor();
        binding.btnPhoto.setOnClickListener(v -> {
            executor.execute(() -> {
                runFrameInference();
                Log.i(TAG, "Frame inference called");
            });
        });
        binding.btnRefresh.setOnClickListener(v -> playTestStream());

        initStateTextAnimation();
        loadONNXModel();
    }

    private void loadONNXModel(){
        modelAssetPath = ModelHelper.copyModelFile(this, "yolov5su.onnx");
        Log.i(TAG, "Model Path: "+modelAssetPath);
    }

    public void shouldDebugPrint(){
        Log.i("Gstreamer Debug", nativeGetGStreamerInfo());
        gstListPlugins();
        nativeOpenCVInfo();
    }

    public void shouldHideSystemUI(){
        getWindow().getDecorView().setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
        );

        getWindow().setStatusBarColor(Color.TRANSPARENT);
        getWindow().setNavigationBarColor(Color.TRANSPARENT);
    }

    public String getOnnxModelPath(){
        return modelAssetPath;
    }

    private void connectToStreamUi(){
        try {
            if(serverURLHandler.isUrlSet()){
                Uri serverUri = serverURLHandler.getServerUrl();
                //setStateConnecting();
                new Thread(() -> connectToStream(serverUri.getHost(), serverUri.getPort())).start();
            }
        } catch (Exception e) {
            Log.e(TAG, "connectToStreamUi: "+e.getMessage());
        }
    }

    private void initializeHLSPaths() {
        if (hlsSegmentPath == null || hlsPlaylistPath == null) {
            File cacheDir = new File(getCacheDir(), "hls");
            if (!cacheDir.exists()) {
                cacheDir.mkdirs();
            }

            hlsSegmentPath = new File(cacheDir, "segment_%05d.ts").getAbsolutePath();
            hlsPlaylistPath = new File(cacheDir, "playlist.m3u8").getAbsolutePath();
        }

        Log.i(TAG, "initializeHLSPaths: Playlist Path:"+hlsPlaylistPath);
    }

    private void connectToStream(String host, int port) {
        initializeHLSPaths();
        String pipeline = String.format(
                Locale.US,
                "tcpclientsrc host=%s port=%d ! queue ! decodebin ! tee name=t " +
                        "t. ! queue ! glimagesink sync=false " +
                        "t. ! queue ! appsink name=app-sink sync=false " +
                        "t. ! queue ! x264enc bitrate=2048 speed-preset=ultrafast tune=zerolatency ! " +
                        "h264parse config-interval=1 ! hlssink2 location=%s playlist-location=%s " +
                        "target-duration=1 max-files=10 playlist-length=3",
                host, port, hlsSegmentPath, hlsPlaylistPath
        );

        setPipeline(pipeline);
        playPipeline();
        serveHls();
    }

    private void playTestStream() {
        initializeHLSPaths();

        String pipeline = String.format(
                Locale.US,
                "videotestsrc is-live=true ! videoscale ! video/x-raw,format=NV12,width=2960,height=1848 ! " +
                        "clockoverlay time-format=\"%%H:%%M:%%S\" font-desc=\"Sans, 48\" ! tee name=t " +
                        "t. ! queue ! glimagesink sync=false " +
                        "t. ! queue ! appsink name=app-sink sync=false " +
                        "t. ! queue ! x264enc bitrate=2048 speed-preset=ultrafast tune=zerolatency ! " +
                        "h264parse ! mpegtsmux ! hlssink location=%s playlist-location=%s " +
                        "target-duration=5 max-files=10",
                hlsSegmentPath, hlsPlaylistPath
        );

        setPipeline(pipeline);
        playPipeline();
        stopStateAnimation();
        binding.connection.setText("TEST");
        serveHls();
    }

    private void serveHls(){
        File hlsDir = new File(getCacheDir(), "hls");
        try {
            HlsServer hlsServer = HlsServer.getInstance(8181, hlsDir);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void stateUpdates(final String message) {
        Log.i("TAG", "GST State Update: " + message);
        switch (message) {
            case "connecting":
                runOnUiThread(() -> {
                    binding.connection.setText(".");
                    stateTextAnimator.start();
                });
                break;
            case "playing":
                runOnUiThread(() -> {
                    stopStateAnimation();
                    binding.connection.setText("LIVE");
                });
                break;
            case "error":
                runOnUiThread(() -> {
                    stopStateAnimation();
                    binding.connection.setText("ERR");
                    surfaceView.getHolder().getSurface().release();
                });
                break;
            default:
                // State update received
                break;
        }
    }

    private void initStateTextAnimation(){
        stateTextAnimator = ValueAnimator.ofInt(0, 5);
        stateTextAnimator.setDuration(2000);
        stateTextAnimator.setRepeatCount(ValueAnimator.INFINITE);
        //binding.connection.setTextColor(getResources().getColor(android.R.color.holo_orange_dark, null));

        stateTextAnimator.addUpdateListener(animation -> {
            int dotCount = (int) stateTextAnimator.getAnimatedValue();
            binding.connection.setText(".".repeat(dotCount));
        });
    }

    public void stopStateAnimation() {
        if (stateTextAnimator != null && stateTextAnimator.isRunning()) {
            stateTextAnimator.cancel();
        }
    }
    private void hideSystemUI() {
        View decorView = getWindow().getDecorView();
        decorView.setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                        | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_FULLSCREEN);
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        if (hasFocus) {
            hideSystemUI();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        nativeCleanup();
    }

    @Override
    protected void onPause() {
        super.onPause();
        pausePipeline();
        surfaceView.getHolder().getSurface().release();
    }

    @Override
    protected void onResume() {
        super.onResume();
        playPipeline();
    }

    static {
        System.loadLibrary("gstreamer_android");
        System.loadLibrary("streamviewer");
    }
    private native String nativeGetGStreamerInfo();
    private static native void setSurface(Surface surface);
    private static native void nativeCleanup();
    private static native void gstListPlugins();
    private static native void setPipeline(String pipelineDesc);
    private static native void pausePipeline();
    private static native void playPipeline();
    public native void nativeInit(MainActivity app);
    private static native void nativeOpenCVInfo();
    private native void saveRawFrame();
    private native void runFrameInference();
}