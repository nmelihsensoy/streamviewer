cmake_minimum_required(VERSION 3.22.1)

project("streamviewer")

#set(GSTREAMER_ROOT_ANDROID "C:/Users/melih.sensoy/Downloads/gstreamer-1.0-android-universal-1.24.12-tar/gstreamer-1.0-android-universal-1.24.12")
set(GSTREAMER_ROOT_ANDROID2 "C:/Users/melih.sensoy/Desktop/gstreamer-1.0-android-universal-1.25.1.1")
set(GSTREAMER_ROOT_ANDROID "C:/Users/melih.sensoy/gstreamer-1.0-android-universal-1.25.1.1-runtime.tar/gstreamer-1.0-android-universal-1.25.1.1-runtime")


if ("${ANDROID_ABI}" STREQUAL "arm64-v8a")
    set(GST_ABI "arm64")
elseif("${ANDROID_ABI}" STREQUAL "armeabi-v7a")
    set(GST_ABI "armv7")
elseif("${ANDROID_ABI}" STREQUAL "x86")
    set(GST_ABI "x86")
elseif("${ANDROID_ABI}" STREQUAL "x86_64")
    set(GST_ABI "x86_64")
else()
    set(GST_ABI ${ANDROID_ABI})
endif()

set(GSTREAMER_ROOT "${GSTREAMER_ROOT_ANDROID}/${GST_ABI}")
set(GSTREAMER_ROOT2 "${GSTREAMER_ROOT_ANDROID2}/${GST_ABI}")

include_directories(
        ${GSTREAMER_ROOT2}/include/gstreamer-1.0
        ${GSTREAMER_ROOT2}/include/glib-2.0
        ${GSTREAMER_ROOT2}/lib/glib-2.0/include
        ${GSTREAMER_ROOT2}/lib/gstreamer-1.0/include
        ${GSTREAMER_ROOT2}/include
)


include_directories(
        ${GSTREAMER_ROOT}/include/gstreamer-1.0
        ${GSTREAMER_ROOT}/include/glib-2.0
        ${GSTREAMER_ROOT}/lib/glib-2.0/include
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/include
        ${GSTREAMER_ROOT}/include
)

link_directories(
        ${GSTREAMER_ROOT}/lib
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0)


SET(GST_LIBS
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcoreelements.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttypefindfunctions.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideoconvertscale.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideorate.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideofilter.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstautodetect.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideotestsrc.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstplayback.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstx264.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideoparsersbad.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstandroidmedia.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtp.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtpmanager.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtpmanagerbad.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtponvif.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopengl.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstwebrtc.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstnice.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsdpelem.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstxingmux.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrealmedia.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstlibav.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsta52dec.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstamrnb.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstasf.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudioconvert.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudioresample.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstasf.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstavi.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstisomp4.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmatroska.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstogg.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstwavparse.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstbz2.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdtls.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsrtp.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopus.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvolume.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcompositor.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvpx.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtsp.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtspclientsink.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiotestsrc.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopenh264.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopensles.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstencoding.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstplayback.so
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttcp.so
)

SET(GST_PLUGINS_CORE_LIBS
        ${GSTREAMER_ROOT}/lib/liborc-0.4.so
        ${GSTREAMER_ROOT}/lib/libgstgl-1.0.so
        ${GSTREAMER_ROOT}/lib/libgraphene-1.0.so
        ${GSTREAMER_ROOT}/lib/libpng16.so
        ${GSTREAMER_ROOT}/lib/libjpeg.so
        ${GSTREAMER_ROOT}/lib/libx264.so
        ${GSTREAMER_ROOT}/lib/libgstvideo-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstrtp-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstsdp-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstwebrtc-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstwebrtcnice-1.0.so
        ${GSTREAMER_ROOT}/lib/libopencore-amrnb.so
        ${GSTREAMER_ROOT}/lib/libgstriff-1.0.so
        ${GSTREAMER_ROOT}/lib/libFLAC.so
        ${GSTREAMER_ROOT}/lib/libogg.so
        ${GSTREAMER_ROOT}/lib/libavformat.so
        ${GSTREAMER_ROOT}/lib/libbz2.so
        ${GSTREAMER_ROOT}/lib/libbz2.so
        ${GSTREAMER_ROOT}/lib/libfreetype.so
        ${GSTREAMER_ROOT}/lib/libgstrtsp-1.0.so
        ${GSTREAMER_ROOT}/lib/liba52.so
        ${GSTREAMER_ROOT}/lib/libavcodec.so
        ${GSTREAMER_ROOT}/lib/libavutil.so
        ${GSTREAMER_ROOT}/lib/libavfilter.so
        ${GSTREAMER_ROOT}/lib/libswresample.so
        ${GSTREAMER_ROOT}/lib/libswresample.so
        ${GSTREAMER_ROOT}/lib/libopus.so
        ${GSTREAMER_ROOT}/lib/libgstrtspserver-1.0.so
        ${GSTREAMER_ROOT}/lib/libopenh264.so

        ${GSTREAMER_ROOT}/lib/libgstaudio-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstpbutils-1.0.so
        ${GSTREAMER_ROOT}/lib/libgsttag-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstphotography-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstcontroller-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstcodecparsers-1.0.so
        EGL GLESv2 OpenSLES

        ${GSTREAMER_ROOT}/lib/libgio-2.0.so
        ${GSTREAMER_ROOT}/lib/libglib-2.0.so
        ${GSTREAMER_ROOT}/lib/libgobject-2.0.so
        ${GSTREAMER_ROOT}/lib/libnice.so
        ${GSTREAMER_ROOT}/lib/libgstapp-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstsctp-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstnet-1.0.so

        ${GSTREAMER_ROOT}/lib/libgstallocators-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstfft-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstpbutils-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstriff-1.0.so
)

SET(GST_PLUGINS_BASE
        ${GSTREAMER_ROOT}/lib/libgstbase-1.0.so
        ${GSTREAMER_ROOT}/lib/libgstreamer-1.0.so
        ${GSTREAMER_ROOT}/lib/libgmodule-2.0.so
        ${GSTREAMER_ROOT}/lib/libgobject-2.0.so
        ${GSTREAMER_ROOT}/lib/libglib-2.0.so
        ${GSTREAMER_ROOT}/lib/libffi.so
        #LIBS += $${GSTREAMER_ROOT}/lib/libpcre.so
        ${GSTREAMER_ROOT}/lib/libsrtp2.so
        ${GSTREAMER_ROOT}/lib/libpcre2-8.so
        ${GSTREAMER_ROOT}/lib/libiconv.so
        ${GSTREAMER_ROOT}/lib/libintl.so
        ${GSTREAMER_ROOT}/lib/libz.so
        ${GSTREAMER_ROOT}/lib/libcrypto.so
        ${GSTREAMER_ROOT}/lib/libssl.so
)

add_library(gstreamer_android SHARED gstreamer_android.c)
target_link_libraries(gstreamer_android log android ${GST_LIBS} ${GST_PLUGINS_CORE_LIBS} ${GST_PLUGINS_BASE})

add_library(${CMAKE_PROJECT_NAME} SHARED native-lib.cpp)
#target_link_libraries(${CMAKE_PROJECT_NAME} log android gstreamer_android)
target_link_libraries(${CMAKE_PROJECT_NAME} log android gstreamer_android)
