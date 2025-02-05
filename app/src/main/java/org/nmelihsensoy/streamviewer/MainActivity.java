package org.nmelihsensoy.streamviewer;

import androidx.annotation.OptIn;
import androidx.appcompat.app.AppCompatActivity;
import androidx.media3.common.MediaItem;
import androidx.media3.common.Player;
import androidx.media3.common.util.UnstableApi;
import androidx.media3.exoplayer.ExoPlayer;
import androidx.media3.ui.PlayerView;

import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;

import org.nmelihsensoy.streamviewer.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    static {
        //System.loadLibrary("streamviewer");
        System.loadLibrary("streamviewer");
    }

    private ActivityMainBinding binding;
    private ExoPlayer player;

    @OptIn(markerClass = UnstableApi.class)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        //TextView tv = binding.sampleText;
        //tv.setText(stringFromJNI());
        PlayerView playerView = binding.playerView;
        Button btnPlay = binding.btnPlay;
        Button btnPause = binding.btnPause;
        player = new ExoPlayer.Builder(this).build();
        playerView.setPlayer(player);

        Uri hlsUri = Uri.parse("http://content.jwplatform.com/manifests/vM7nH0Kl.m3u8");
        MediaItem mediaItem = MediaItem.fromUri(hlsUri);

        // Set the media item to be played
        player.setMediaItem(mediaItem);
        player.prepare();


        // Load media (replace with your own URL)
        //Uri mediaUri = Uri.parse("https://storage.googleapis.com/exoplayer-test-media-0/BigBuckBunny_320x180.mp4");
        //MediaItem mediaItem = MediaItem.fromUri(mediaUri);
        //player.setMediaItem(mediaItem);
        //player.prepare();

        // Play button
        btnPlay.setOnClickListener(v -> player.play());

        // Pause button
        btnPause.setOnClickListener(v -> player.pause());
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // Release player when activity is destroyed
        if (player != null) {
            player.release();
        }
    }

    public native void stringFromJNI();
}