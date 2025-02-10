#include <jni.h>
#include <android/log.h>
#include <gst/gst.h>
#include <unistd.h>

#define LOG_TAG "GStreamerExample"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

typedef struct {
    GstElement *pipeline;
    GstElement *video_sink;
} CustomData;

static CustomData data;

extern "C"
JNIEXPORT jstring JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_nativeGetGStreamerInfo(JNIEnv *env, jobject thiz) {
    const gchar *version_utf8 = gst_version_string();
    return env->NewStringUTF(version_utf8);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_nativePlayVideo(JNIEnv *env, jobject thiz,
                                                              jstring video_path) {
    gst_init(NULL, NULL);

    // Create a playbin pipeline
    data.pipeline = gst_element_factory_make("fakesrc", "pipeline");
    if (!data.pipeline) {
        g_printerr("Failed to create pipeline.\n");
        LOGE("Failed to create pipeline.");
        return;
    }

    GstState state;
    GstState pending;
    if (gst_element_get_state(data.pipeline, &state, &pending, GST_CLOCK_TIME_NONE) == GST_STATE_CHANGE_SUCCESS) {
        LOGE("Pipeline state: %s", gst_element_state_get_name(state));
    }
    /*
    // Set the video sink to autovideosink (default for Android)
    data.video_sink = gst_element_factory_make("autovideosink", "video_sink");
    if (!data.video_sink) {
        LOGE("Failed to create video sink.");
        //g_printerr("Failed to create video sink.\n");
        return;
    }


     *     g_object_set(data.pipeline, "video-sink", data.video_sink, NULL);
    gst_debug_set_active(TRUE);
    gst_debug_set_default_threshold(GST_LEVEL_DEBUG);

    GstState state;
    GstState pending;
    if (gst_element_get_state(data.pipeline, &state, &pending, GST_CLOCK_TIME_NONE) == GST_STATE_CHANGE_SUCCESS) {
        LOGE("Pipeline state: %s", gst_element_state_get_name(state));
    }

    gst_debug_bin_to_dot_file(GST_BIN(data.pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "/sdcard/pipeline_debug");
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        LOGE("Current working directory: %s", cwd);
    } else {
        LOGE("Failed to get current working directory");
    }
     * */
}