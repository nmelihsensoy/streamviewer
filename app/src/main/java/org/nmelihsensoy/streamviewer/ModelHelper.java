package org.nmelihsensoy.streamviewer;
import android.content.Context;
import android.content.res.AssetManager;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

public class ModelHelper {
    public static String copyModelFile(Context context, String assetFileName) {
        AssetManager assetManager = context.getAssets();
        File outFile = new File(context.getFilesDir(), assetFileName);
        try (InputStream in = assetManager.open(assetFileName);
             OutputStream out = new FileOutputStream(outFile)) {
            byte[] buffer = new byte[1024];
            int read;
            while ((read = in.read(buffer)) != -1) {
                out.write(buffer, 0, read);
            }
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
        return outFile.getAbsolutePath();
    }
}
