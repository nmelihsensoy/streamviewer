# StreamViewer

`gradle.properties`
````
gstAndroidDevelRoot=C\:\\Users\\melih.sensoy\\Desktop\\gstreamer-1.0-android-universal-1.25.1.1
gstAndroidRuntimeRoot=C\:\\Users\\melih.sensoy\\gstreamer-1.0-android-universal-1.25.1.1-runtime.tar\\gstreamer-1.0-android-universal-1.25.1.1-runtime
````

Test Tcp Stream:
```
gst-launch-1.0 -v videotestsrc ! clockoverlay time-format="%H:%M:%S" font-desc="Sans, 48" ! videoscale ! videoconvert ! video/x-raw,width=1920,height=1080 ! x264enc tune=zerolatency bitrate=4000 speed-preset=superfast ! h264parse ! video/x-h264,stream-format=byte-stream ! tcpserversink host=0.0.0.0 port=5001
```

Raw Frame Conversion:
```
For Frame format: video/x-raw, format=(string)Y444, width=(int)1920, height=(int)1080, interlace-mode=(string)progressive, pixel-aspect-ratio=(fraction)1/1, chroma-site=(string)mpeg2, colorimetry=(string)bt709, framerate=(fraction)30/1
ffmpeg -f rawvideo -pixel_format yuv444p -video_size 1920x1080 -i frame.raw -vf format=rgb24 frame.png

For Frame format: video/x-raw, format=(string)RGBx, width=(int)1920, height=(int)1080, framerate=(fraction)30/1, multiview-mode=(string)mono, pixel-aspect-ratio=(fraction)1/1, interlace-mode=(string)progressive
ffmpeg -f rawvideo -pixel_format rgb32 -video_size 1920x1080 -i frame.raw -vf format=rgb32 frame.png
```

