# StreamViewer

StreamViewer is an Android application that allows users to view H.264 video streams over TCP using GStreamer.

![Walkthrough](.//media/walkthrough1.png)

## Features

- **Connect to a Stream** – View stream from a TCP source.
- **Capture Frame & Run Inference** – Take a snapshot and perform YOLO inference.
- **Load a Test Stream** – Quickly launch a built-in test stream.
- **HLS Restreaming** – Restream the current source as an HLS stream.

### Frame Capture

When a frame is captured, it is saved in the following location on the device: `/sdcard/Download/image_<id>.png`

### Inference Result

Once YOLO inference is performed on a captured frame, the output tensor's dimensions are printed in Logcat.

### HLS Restreaming

The restreamed HLS feed can be accessed via the following URL: `http://<server_ip>:8181/playlist.m3u8`

### Configuration

Update your `gradle.properties` file with the paths to GStreamer and OpenCV SDKs:

```properties
gstAndroidDevelRoot=D\:\\gstreamer-1.0-android-universal-1.25.90.1
opencvAndroidSdkRoot=D\:\\opencv-4.11.0-android-sdk\\OpenCV-android-sdk\\sdk\\native
```
