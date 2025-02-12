cmake_minimum_required(VERSION 3.22.1)

project("streamviewer")

set(GSTREAMER_ROOT_ANDROID "C:/Users/melih.sensoy/Downloads/gstreamer-1.0-android-universal-1.24.12-tar/gstreamer-1.0-android-universal-1.24.12")

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
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcoreelements.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttypefindfunctions.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideoconvertscale.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideorate.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideofilter.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstautodetect.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideotestsrc.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstplayback.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstx264.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideoparsersbad.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstandroidmedia.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtp.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtpmanager.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtpmanagerbad.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtponvif.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopengl.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstwebrtc.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstnice.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsdpelem.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstxingmux.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrealmedia.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstlibav.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsta52dec.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstamrnb.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstasf.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudioconvert.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudioresample.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstasf.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstavi.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstisomp4.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmatroska.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstogg.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstwavparse.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstbz2.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdtls.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsrtp.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopus.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvolume.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcompositor.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvpx.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtsp.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtspclientsink.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiotestsrc.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopenh264.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopensles.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstencoding.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstplayback.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttcp.a
)

SET(GST_PLUGINS_CORE_LIBS
        ${GSTREAMER_ROOT}/lib/liborc-0.4.a
        ${GSTREAMER_ROOT}/lib/libgstgl-1.0.a
        ${GSTREAMER_ROOT}/lib/libgraphene-1.0.a
        ${GSTREAMER_ROOT}/lib/libpng16.a
        ${GSTREAMER_ROOT}/lib/libjpeg.a
        ${GSTREAMER_ROOT}/lib/libx264.a
        ${GSTREAMER_ROOT}/lib/libgstvideo-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstrtp-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstsdp-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstwebrtc-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstwebrtcnice-1.0.a
        ${GSTREAMER_ROOT}/lib/libopencore-amrnb.a
        ${GSTREAMER_ROOT}/lib/libgstriff-1.0.a
        ${GSTREAMER_ROOT}/lib/libFLAC.a
        ${GSTREAMER_ROOT}/lib/libogg.a
        ${GSTREAMER_ROOT}/lib/libavformat.a
        ${GSTREAMER_ROOT}/lib/libbz2.a
        ${GSTREAMER_ROOT}/lib/libfreetype.a
        ${GSTREAMER_ROOT}/lib/libgstrtsp-1.0.a
        ${GSTREAMER_ROOT}/lib/liba52.a
        ${GSTREAMER_ROOT}/lib/libavcodec.a
        ${GSTREAMER_ROOT}/lib/libavutil.a
        ${GSTREAMER_ROOT}/lib/libavfilter.a
        ${GSTREAMER_ROOT}/lib/libswresample.a
        ${GSTREAMER_ROOT}/lib/libopus.a
        ${GSTREAMER_ROOT}/lib/libvpx.a
        ${GSTREAMER_ROOT}/lib/libgstrtspserver-1.0.a
        ${GSTREAMER_ROOT}/lib/libopenh264.a

        ${GSTREAMER_ROOT}/lib/libgstaudio-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstpbutils-1.0.a
        ${GSTREAMER_ROOT}/lib/libgsttag-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstphotography-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstcontroller-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstcodecparsers-1.0.a
        EGL GLESv2 OpenSLES

        ${GSTREAMER_ROOT}/lib/libgio-2.0.a
        ${GSTREAMER_ROOT}/lib/libglib-2.0.a
        ${GSTREAMER_ROOT}/lib/libgobject-2.0.a
        ${GSTREAMER_ROOT}/lib/libnice.a
        ${GSTREAMER_ROOT}/lib/libgstapp-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstsctp-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstnet-1.0.a

        ${GSTREAMER_ROOT}/lib/libgstallocators-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstfft-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstpbutils-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstriff-1.0.a

)

SET(GST_PLUGINS_BASE
        ${GSTREAMER_ROOT}/lib/libgstbase-1.0.a
        ${GSTREAMER_ROOT}/lib/libgstreamer-1.0.a
        ${GSTREAMER_ROOT}/lib/libgmodule-2.0.a
        ${GSTREAMER_ROOT}/lib/libgobject-2.0.a
        ${GSTREAMER_ROOT}/lib/libglib-2.0.a
        ${GSTREAMER_ROOT}/lib/libffi.a
        #LIBS += $${GSTREAMER_ROOT}/lib/libpcre.a
        ${GSTREAMER_ROOT}/lib/libsrtp2.a
        ${GSTREAMER_ROOT}/lib/libpcre2-8.a
        ${GSTREAMER_ROOT}/lib/libiconv.a
        ${GSTREAMER_ROOT}/lib/libintl.a
        ${GSTREAMER_ROOT}/lib/libz.a
)

add_library(gstreamer_android SHARED gstreamer_android.c)
target_link_libraries(gstreamer_android log android ${GST_LIBS} ${GST_PLUGINS_CORE_LIBS} ${GST_PLUGINS_BASE})

add_library(${CMAKE_PROJECT_NAME} SHARED native-lib.cpp)
#target_link_libraries(${CMAKE_PROJECT_NAME} log android gstreamer_android)
target_link_libraries(${CMAKE_PROJECT_NAME} log android gstreamer_android)
