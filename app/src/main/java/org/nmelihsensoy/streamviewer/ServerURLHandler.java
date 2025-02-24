package org.nmelihsensoy.streamviewer;

import android.content.Context;
import android.content.SharedPreferences;
import android.net.Uri;
import android.widget.EditText;
import android.widget.Toast;
import androidx.appcompat.app.AlertDialog;

import java.util.function.Consumer;

public class ServerURLHandler {
    private final Context context;
    private final SharedPreferences prefs;
    public static final String PREF_STORE_NAME = "streamViewerStore";
    public static final String SERVER_URL_PREF = "streamUrl";

    public ServerURLHandler(Context context) {
        this.context = context;
        this.prefs = context.getSharedPreferences(PREF_STORE_NAME, Context.MODE_PRIVATE);
    }

    public boolean isUrlSet(){
        return prefs.contains(SERVER_URL_PREF);
    }

    public Uri getServerUrl(){
        String savedUrl = prefs.getString(SERVER_URL_PREF, "");
        return Uri.parse("tcp://"+savedUrl);
    }

    public void showServerUrlDialog(Consumer<Boolean> onUrlChangedCallback) {
        EditText editText = new EditText(context);
        editText.setSingleLine(true);

        String savedUrl = prefs.getString(SERVER_URL_PREF, "");
        editText.setText(savedUrl);

        new AlertDialog.Builder(context)
                .setTitle("Enter Stream URL (host:port)")
                .setView(editText)
                .setPositiveButton("OK", (dialog, which) -> {
                    String input = editText.getText().toString().trim();
                    if (isValidServerUrl(input)) {
                        if (!input.equals(savedUrl)) {
                            prefs.edit().putString(SERVER_URL_PREF, input).apply();
                            if (onUrlChangedCallback != null) {
                                onUrlChangedCallback.accept(true);
                            }
                        }
                    } else {
                        Toast.makeText(context, "Invalid format! Use localhost:5000 or 192.168.1.1:8080", Toast.LENGTH_LONG).show();
                    }
                })
                .setNegativeButton("Cancel", null)
                .show();
    }

    private static boolean isValidServerUrl(String input) {
        try {
            Uri uri = Uri.parse("tcp://" + input);
            String scheme = uri.getScheme();
            String host = uri.getHost();
            int port = uri.getPort();

            return "tcp".equalsIgnoreCase(scheme) && host != null && port > 0 && port <= 65535;
        } catch (Exception e) {
            return false;
        }
    }
}