cmake_minimum_required(VERSION 3.22.1)

project("streamviewer")

set(GSTREAMER_ROOT "C:/Users/melih.sensoy/Downloads/gstreamer-1.0-android-universal-1.24.12.tar/gstreamer-1.0-android-universal-1.24.12" CACHE PATH "GStreamer root folder")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

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

include_directories(
        ${GSTREAMER_ROOT_ABI}/include/gstreamer-1.0
        ${GSTREAMER_ROOT_ABI}/include/glib-2.0
        ${GSTREAMER_ROOT_ABI}/lib/glib-2.0/include
        ${GSTREAMER_ROOT_ABI}/lib/gstreamer-1.0/include
        ${GSTREAMER_ROOT_ABI}/include
)

link_directories(
        ${GSTREAMER_ROOT_ABI}/lib
        ${GSTREAMER_ROOT_ABI}/lib/gstreamer-1.0)


set(
        GST_PLUGINS
        CACHE STRING
        "GStreamer plugins to use"
)

set(
        GST_PlUGIN_LIBS
        CACHE STRING
        "Libs for GStreamer plugins"
)

set(
        GST_LIBS
        glib-2.0
        gobject-2.0
        ssl
        crypto
        CACHE STRING
        "GStreamer main libs"
)

add_library(gstreamer_android SHARED gstreamer_android.cpp)
target_link_libraries(gstreamer_android log android ${GST_LIBS} ${GST_PLUGINS_CORE_LIBS} ${GST_PLUGINS_BASE})

add_library(${CMAKE_PROJECT_NAME} SHARED native-lib.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} log android gstreamer_android)

