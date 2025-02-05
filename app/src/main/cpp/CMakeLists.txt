cmake_minimum_required(VERSION 3.22.1)
project("streamviewer")
set(GSTREAMER_ROOT "C:/Users/melih.sensoy/Downloads/gstreamer-1.0-android-universal-1.24.12.tar/gstreamer-1.0-android-universal-1.24.12" CACHE PATH "GStreamer root folder")

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

set(GSTREAMER_ROOT_ABI "${GSTREAMER_ROOT}/${GST_ABI}")

set(
        GST_PLUGINS
        gstadaptivedemux2
        gstadder
        gstadpcmdec
        gstadpcmenc
        gstalaw
        gstandroidmedia
        gstapetag
        gstapp
        gstassrender
        gstaudioconvert
        gstaudiomixer
        gstaudioparsers
        gstaudiorate
        gstaudioresample
        gstauparse
        gstautodetect
        gstavi
        gstbz2
        gstcairo
        gstcodecalpha
        gstcodectimestamper
        gstcompositor
        gstcoreelements
        gstcoretracers
        gstdash
        gstdv
        gstflac
        gstflv
        gstflxdec
        gstgdp
        gstgio
        gsthls
        gstid3demux
        gstid3tag
        gsticydemux
        gstinterlace
        gstdeinterlace
        gstipcpipeline
        gstisomp4
        gstjpeg
        gstjpegformat
        gstlame
        gstmatroska
        gstmidi
        gstmpg123
        gstmulaw
        gstmultipart
        gstmxf
        gstogg
        gstopengl
        gstopenh264
        gstopenjpeg
        gstopensles
        gstopus
        gstopusparse
        gstpcapparse
        gstplayback
        gstpng
        gstpnm
        gstrawparse
        gstrfbsrc
        gstrsvg
        gstsiren
        gstspandsp
        gstsbc
        gstspeex
        gstsubenc
        gstsubparse
        gsttaglib
        gsttheora
        gsttypefindfunctions
        gstvideoconvertscale
        gstvideofilter
        gstvideofiltersbad
        gstvideoparsersbad
        gstvideorate
        gstvolume
        gstvorbis
        gstvpx
        gstwavenc
        gstwavpack
        gstwavparse
        gstxingmux
        gsty4mdec
        gsty4menc
        gstsoup
        CACHE STRING
        "GStreamer plugins to use"
)

# Define additional libraries required by the GStreamer plugins
set(
        GST_PlUGIN_LIBS
        orc-0.4
        gstvideo-1.0
        gstallocators-1.0
        gstadaptivedemux-1.0
        gsturidownloader-1.0
        gstgl-1.0
        graphene-1.0
        vpx
        gstapp-1.0
        gstaudio-1.0
        gstnet-1.0
        gsttag-1.0
        gstpbutils-1.0
        gstriff-1.0
        gstrtp-1.0
        gstsdp-1.0
        gstrtsp-1.0
        gstphotography-1.0
        gstcontroller-1.0
        gstcodecparsers-1.0
        gstplay-1.0
        avutil
        swresample
        avfilter
        avcodec
        avformat
        FLAC
        ogg
        vorbis
        vorbisenc
        mp3lame
        mpg123
        openh264
        openjp2
        opus
        pango-1.0
        pangocairo-1.0
        pangoft2-1.0
        rsvg-2
        gstsdp-1.0
        spandsp
        croco-0.6
        sbc
        speex
        tag
        theora
        wavpack
        zbar
        soup-2.4
        CACHE STRING
        "Libs for GStreamer plugins"
)

# Define the core libraries required by GStreamer
set(
        GST_LIBS
        pcre2-8
        iconv
        ffi
        png16
        jpeg
        tiff
        glib-2.0
        gobject-2.0
        gmodule-2.0
        gio-2.0
        gstreamer-1.0
        gstbase-1.0
        intl
        bz2
        z
        dv
        xml2
        ssl
        crypto
        expat
        fontconfig
        harfbuzz
        fribidi
        freetype
        ass
        pixman-1
        gdk_pixbuf-2.0
        cairo
        stdc++
        psl
        CACHE STRING
        "GStreamer main libs"
)

add_library(
        ${CMAKE_PROJECT_NAME} SHARED
        gstreamer_android.cpp
)

include_directories(
        ${GSTREAMER_ROOT_ABI}/include/gstreamer-1.0
        ${GSTREAMER_ROOT_ABI}/include/glib-2.0
        ${GSTREAMER_ROOT_ABI}/lib/glib-2.0/include
        ${GSTREAMER_ROOT_ABI}/lib/gstreamer-1.0/include
        ${GSTREAMER_ROOT_ABI}/include
)

target_link_directories(
        ${CMAKE_PROJECT_NAME} PUBLIC
        ${GSTREAMER_ROOT_ABI}/lib
        ${GSTREAMER_ROOT_ABI}/lib/gstreamer-1.0
)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        android
        log
        ${OPENSL_LIBRARY}
        ${GST_LIBS}
        ${GST_PlUGIN_LIBS}
        ${GST_PLUGINS}
)