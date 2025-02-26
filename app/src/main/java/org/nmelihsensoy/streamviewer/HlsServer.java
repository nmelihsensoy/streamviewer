package org.nmelihsensoy.streamviewer;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import fi.iki.elonen.NanoHTTPD;

public class HlsServer extends NanoHTTPD {
    private final File hlsDirectory;

    public HlsServer(int port, File hlsDir) throws IOException {
        super(port);
        this.hlsDirectory = hlsDir;
        start(SOCKET_READ_TIMEOUT, false);
        System.out.println("HLS Server running on http://localhost:" + port);
    }

    @Override
    public Response serve(IHTTPSession session) {
        String uri = session.getUri().substring(1); // Remove leading "/"
        File requestedFile = new File(hlsDirectory, uri);

        if (!requestedFile.exists()) {
            return createCORSResponse(Response.Status.NOT_FOUND, "text/plain", "File not found: " + uri);
        }

        try {
            FileInputStream fis = new FileInputStream(requestedFile);
            String mimeType = uri.endsWith(".m3u8") ? "application/vnd.apple.mpegurl" : "video/mp2t";
            return createCORSResponse(Response.Status.OK, mimeType, fis);
        } catch (IOException e) {
            e.printStackTrace();
            return createCORSResponse(Response.Status.INTERNAL_ERROR, "text/plain", "Error reading file");
        }
    }

    /**
     * Creates a response with CORS headers.
     */
    private Response createCORSResponse(Response.Status status, String mimeType, InputStream data) {
        Response res = newChunkedResponse(status, mimeType, data);
        addCORSHeaders(res);
        return res;
    }

    private Response createCORSResponse(Response.Status status, String mimeType, String message) {
        Response res = newFixedLengthResponse(status, mimeType, message);
        addCORSHeaders(res);
        return res;
    }

    /**
     * Adds CORS headers to allow cross-origin requests.
     */
    private void addCORSHeaders(Response response) {
        response.addHeader("Access-Control-Allow-Origin", "*");
        response.addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        response.addHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    }
}
