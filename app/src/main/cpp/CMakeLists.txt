cmake_minimum_required(VERSION 3.22.1)

project("streamviewer")

if(NOT DEFINED GSTREAMER_DEVEL_ANDROID)
    message(FATAL_ERROR "GSTREAMER_DEVEL_ANDROID is not defined!")
endif()

if(NOT DEFINED GSTREAMER_RUNTIME_ANDROID)
    message(FATAL_ERROR "GSTREAMER_RUNTIME_ANDROID is not defined!")
endif()

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

set(GSTREAMER_DEVEL_ROOT "${GSTREAMER_DEVEL_ANDROID}/${GST_ABI}")
set(GSTREAMER_RUNTIME_ROOT "${GSTREAMER_RUNTIME_ANDROID}/${GST_ABI}")

#Include headers
include_directories(
        ${GSTREAMER_DEVEL_ROOT}/include/gstreamer-1.0
        ${GSTREAMER_DEVEL_ROOT}/include/glib-2.0
        ${GSTREAMER_DEVEL_ROOT}/lib/glib-2.0/include
        ${GSTREAMER_DEVEL_ROOT}/lib/gstreamer-1.0/include
        ${GSTREAMER_DEVEL_ROOT}/include
)

link_directories(
        ${GSTREAMER_RUNTIME_ROOT}/lib
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0)

SET(GST_LIBS
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstcoreelements.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgsttypefindfunctions.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstvideoconvertscale.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstvideorate.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstvideofilter.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstautodetect.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstvideotestsrc.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstplayback.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstx264.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstvideoparsersbad.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstandroidmedia.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstrtp.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstrtpmanager.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstrtpmanagerbad.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstrtponvif.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstopengl.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstwebrtc.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstnice.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstsdpelem.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstxingmux.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstrealmedia.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstlibav.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgsta52dec.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstamrnb.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstasf.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstaudioconvert.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstaudioresample.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstasf.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstavi.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstisomp4.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstmatroska.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstogg.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstwavparse.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstbz2.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstdtls.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstsrtp.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstopus.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstvolume.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstcompositor.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstvpx.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstrtsp.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstrtspclientsink.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstaudiotestsrc.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstopenh264.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstopensles.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstencoding.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstplayback.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgsttcp.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstoverlaycomposition.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgsteffectv.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstaudioparsers.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstapp.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstadder.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstgio.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/gstreamer-1.0/libgstpango.so
)

SET(GST_PLUGINS_CORE_LIBS
        ${GSTREAMER_RUNTIME_ROOT}/lib/liborc-0.4.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstgl-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgraphene-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libpng16.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libjpeg.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libx264.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstvideo-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstrtp-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstsdp-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstwebrtc-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstwebrtcnice-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libopencore-amrnb.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstriff-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libFLAC.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libogg.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libavformat.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libbz2.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libbz2.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libfreetype.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstrtsp-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/liba52.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libavcodec.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libavutil.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libavfilter.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libswresample.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libswresample.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libopus.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstrtspserver-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libopenh264.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstaudio-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstpbutils-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgsttag-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstphotography-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstcontroller-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstcodecparsers-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgio-2.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libglib-2.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgobject-2.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libnice.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstapp-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstsctp-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstnet-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstallocators-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstfft-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstpbutils-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstriff-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstapp-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libpango-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libpangocairo-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libpangoft2-1.0.so
        EGL GLESv2 OpenSLES
)

SET(GST_PLUGINS_BASE
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstbase-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgstreamer-1.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgmodule-2.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libgobject-2.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libglib-2.0.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libffi.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libsrtp2.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libpcre2-8.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libiconv.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libintl.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libz.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libcrypto.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libssl.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libcairo.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libfribidi.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libharfbuzz.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libharfbuzz-gobject.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libfontconfig.so
        ${GSTREAMER_RUNTIME_ROOT}/lib/libpixman-1.so
)

include_directories(${OpenCV_DIR}/jni/include)
add_library( lib_opencv SHARED IMPORTED )
set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION ${OpenCV_DIR}/libs/${ANDROID_ABI}/libopencv_java4.so)

add_library(gstreamer_android SHARED gstreamer_android.c)
target_link_libraries(gstreamer_android log android ${GST_LIBS} ${GST_PLUGINS_CORE_LIBS} ${GST_PLUGINS_BASE})

add_library(${CMAKE_PROJECT_NAME} SHARED native-lib.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} log android gstreamer_android lib_opencv)
