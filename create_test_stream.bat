@echo off
setlocal

gst-launch-1.0 -v videotestsrc ! clockoverlay time-format="%H:%M:%S" font-desc="Sans, 48" ! videoscale ! videoconvert ! video/x-raw,format=I420,width=2960,height=1848 ! x264enc tune=zerolatency bitrate=4000 speed-preset=superfast ! h264parse ! video/x-h264,stream-format=byte-stream ! tcpserversink host=0.0.0.0 port=5001

endlocal