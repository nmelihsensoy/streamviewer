package org.nmelihsensoy.streamviewer;

import androidx.annotation.OptIn;
import androidx.appcompat.app.AppCompatActivity;
import androidx.media3.common.util.UnstableApi;
import androidx.media3.exoplayer.ExoPlayer;
import androidx.media3.ui.PlayerView;

import android.os.Bundle;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.Button;
import android.widget.Toast;

import org.freedesktop.gstreamer.GStreamer;
import org.nmelihsensoy.streamviewer.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("gstreamer_android");
        System.loadLibrary("streamviewer");
    }

    private native String nativeGetGStreamerInfo();

    private native void nativeGetGStreamerTest1();
    private native void initMyPipeline(Surface surface);
    private native void stopMyPipeline();
    //private native void nativePlayVideo(String videoPath);
    private SurfaceView surfaceView;

    private ActivityMainBinding binding;
    private ExoPlayer player;

    @OptIn(markerClass = UnstableApi.class)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        nativeGetGStreamerInfo();
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        try {
            GStreamer.init(this);
        } catch (Exception e) {
            Toast.makeText(this, e.getMessage(), Toast.LENGTH_LONG).show();
            finish();
            return;
        }

        // Example of a call to a native method
        //TextView tv = binding.sampleText;
        //tv.setText(stringFromJNI());
        PlayerView playerView = binding.playerView;
        Button btnPlay = binding.btnPlay;
        Button btnPause = binding.btnPause;
        player = new ExoPlayer.Builder(this).build();
        playerView.setPlayer(player);

        //Uri hlsUri = Uri.parse("http://content.jwplatform.com/manifests/vM7nH0Kl.m3u8");
        //MediaItem mediaItem = MediaItem.fromUri(hlsUri);

        // Set the media item to be played
        //player.setMediaItem(mediaItem);
        player.prepare();


        // Load media (replace with your own URL)
        //Uri mediaUri = Uri.parse("https://storage.googleapis.com/exoplayer-test-media-0/BigBuckBunny_320x180.mp4");
        //MediaItem mediaItem = MediaItem.fromUri(mediaUri);
        //player.setMediaItem(mediaItem);
        //player.prepare();

        // Play button
        btnPlay.setOnClickListener(v -> {
            player.play();
            Log.d("myTag1", nativeGetGStreamerInfo());
            nativeGetGStreamerTest1();
            //nativePlayVideo("file:///android_asset/Feed.mp4");
        });

        // Pause button
        btnPause.setOnClickListener(v -> player.pause());

        surfaceView = binding.gstreamerSurface;
        surfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder holder) {
                //gStreamerNative.initPipeline(holder.getSurface()); // Pass the Surface to JNI
                initMyPipeline(holder.getSurface());
            }

            @Override
            public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
                // Handle resize if needed
            }

            @Override
            public void surfaceDestroyed(SurfaceHolder holder) {
                //gStreamerNative.stopPipeline();
                stopMyPipeline();
            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // Release player when activity is destroyed
        if (player != null) {
            player.release();
        }
        //gStreamerNative.stopPipeline();
        stopMyPipeline();
    }
}