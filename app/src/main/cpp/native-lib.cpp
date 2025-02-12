#include <jni.h>
#include <android/log.h>
#include <gst/gst.h>
#include <unistd.h>

#define LOG_TAG "GStreamer"  // Define a log tag
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_nativeGetGStreamerInfo(JNIEnv *env, jobject thiz) {
    char *version_utf8 = gst_version_string ();
    return (*env).NewStringUTF(version_utf8);
}
extern "C"
JNIEXPORT void JNICALL
Java_org_freedesktop_gstreamer_GStreamer_nativeInit(JNIEnv *env, jclass clazz, jobject context) {
    gst_init(nullptr, nullptr);

    if (!gst_element_factory_find("testvideosrc")) {
        LOGE("testvideosrc is missing! Check if libgstvideotestsrc.a is linked.");
    } else {
        LOGI("testvideosrc found!");
    }

    if (!gst_element_factory_find("tcpclientsrc")) {
        LOGE("tcpclientsrc is missing! Check if libgsttcp.a is linked.");
    } else {
        LOGI("tcpclientsrc found!");
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_nativeGetGStreamerTest1(JNIEnv *env, jclass clazz, jobject context) {
    gst_init(nullptr, nullptr);

    if (!gst_element_factory_find("testvideosrc")) {
        LOGE("testvideosrc is missing! Check if libgstvideotestsrc.a is linked.");
    } else {
        LOGI("testvideosrc found!");
    }

    if (!gst_element_factory_find("tcpclientsrc")) {
        LOGE("tcpclientsrc is missing! Check if libgsttcp.a is linked.");
    } else {
        LOGI("tcpclientsrc found!");
    }
}