package org.nmelihsensoy.streamviewer;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.animation.ValueAnimator;
import android.content.pm.PackageManager;
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

import java.util.Locale;

public class MainActivity extends AppCompatActivity {

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
    private native void saveFrame();
    private static final String TAG = "FrameDebug";
    private ValueAnimator stateTextAnimator;

    private SurfaceView surfaceView;

    private ActivityMainBinding binding;
    private ServerURLHandler serverURLHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        getWindow().getDecorView().setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
        );

        getWindow().setStatusBarColor(Color.TRANSPARENT);
        getWindow().setNavigationBarColor(Color.TRANSPARENT);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        try {
            GStreamer.init(this);
            nativeInit(this);
            Log.i("Gstreamer Debug", nativeGetGStreamerInfo());
            gstListPlugins();
        } catch (Exception e) {
            Toast.makeText(this, e.getMessage(), Toast.LENGTH_LONG).show();
            finish();
            return;
        }

        serverURLHandler = new ServerURLHandler(this);
        Log.i(TAG, "onCreate ServerURL: "+ serverURLHandler.getServerUrl().toString()+" host:"+ serverURLHandler.getServerUrl().getHost());

        surfaceView = binding.gstreamerSurface;
        surfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder holder) {
                setSurface(holder.getSurface());
            }

            @Override
            public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
            }

            @Override
            public void surfaceDestroyed(SurfaceHolder holder) {
            }
        });
        binding.btnTest.setOnClickListener(v -> { connectToStreamUi(); });
        binding.btnConnect.setOnClickListener(v -> {
            serverURLHandler.showServerUrlDialog(isUrlChanged -> {
                if (isUrlChanged) {
                    connectToStreamUi();
                    Log.i(TAG, "URL changed. ");
                } else {
                    Log.i(TAG, "URL unchanged or canceled");
                }
            });
        });
        binding.btnPhoto.setOnClickListener(v -> {
            saveFrame();
            Log.i(TAG, "onCreate: saveFrame called");
        });
        binding.btnRefresh.setOnClickListener(v -> playTestStream());
        binding.btnReconnect.setOnClickListener(v -> connectToStreamUi());

        //connectToStreamUi();
    }

    private void connectToStreamUi(){
        try {
            if(serverURLHandler.isUrlSet()){
                Uri serverUri = serverURLHandler.getServerUrl();
                setStateConnecting();
                new Thread(() -> {
                    connectToStream(serverUri.getHost(), serverUri.getPort());
                }).start();
            }
        } catch (Exception e) {
            Log.e("connectToStreamUi", "connectToStreamUi: "+e.getMessage());
        }
    }

    private void connectToStream(String host, int port) {
        String pipeline = String.format(
                Locale.US,
                "tcpclientsrc host=%s port=%d ! queue ! decodebin ! tee name=t t. ! queue ! glimagesink sync=false t. ! queue ! appsink name=app-sink sync=false",
                host, port
        );
        setPipeline(pipeline);
        playPipeline();
    }

    private void playTestStream() {
        //String pipeline = "videotestsrc is-live=true ! videoscale ! video/x-raw,width=1920,height=1080 ! warptv ! queue ! glimagesink sync=false";
        String pipeline = "videotestsrc is-live=true ! videoscale ! video/x-raw,width=1920,height=1080 ! warptv ! tee name=t ! queue ! glimagesink sync=false t. ! queue ! appsink name=app-sink sync=false";
        setPipeline(pipeline);
        playPipeline();
        stopStateAnimation();
        binding.connection.setText("TEST");
    }

    public void stateUpdates(final String message) {
        Log.i("TAG", "GST State Update: " + message);
        //runOnUiThread(() -> Toast.makeText(this, message, Toast.LENGTH_SHORT).show());
    }

    private void setStateConnecting(){
        stateTextAnimator = ValueAnimator.ofInt(0, 5);
        stateTextAnimator.setDuration(2000);
        stateTextAnimator.setRepeatCount(ValueAnimator.INFINITE);
        //binding.connection.setTextColor(getResources().getColor(android.R.color.holo_orange_dark, null));

        stateTextAnimator.addUpdateListener(animation -> {
            int dotCount = (int) stateTextAnimator.getAnimatedValue();
            binding.connection.setText(".".repeat(dotCount));
        });

        stateTextAnimator.start();
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
}