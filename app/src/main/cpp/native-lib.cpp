#include <jni.h>
#include <android/log.h>
#include <gst/gst.h>
#include <unistd.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_nativeGetGStreamerInfo(JNIEnv *env, jobject thiz) {
    char *version_utf8 = gst_version_string ();
    return (*env).NewStringUTF(version_utf8);
}