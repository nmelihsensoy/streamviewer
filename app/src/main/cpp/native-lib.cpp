#include <jni.h>
#include <android/log.h>
#include <gst/gst.h>
#include <unistd.h>
#include <gst/video/videooverlay.h>
#include <android/native_window_jni.h>

#define LOG_TAG "GStreamer"  // Define a log tag
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
static GstElement *pipeline = NULL;
#define ARRAYSIZE(a) \
  ((sizeof(a) / sizeof(*(a))) / \
  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

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
}
extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_nativeGetGStreamerTest1(JNIEnv *env, jclass clazz, jobject context) {
    gst_init(nullptr, nullptr);
    //gst_element_factory_find("videotestsrc")

    GstElementFactory *androidOpusFactory = gst_element_factory_find("amcauddec-omxgoogleopusdecoder");
    if (androidOpusFactory == NULL) {
        LOGI("androidmedia not found");
    }

    GList *g;
    GstRegistry *registry = gst_registry_get();

    GList *list = gst_registry_get_plugin_list (registry);
    for (g = list; g; g = g->next) {
        GstPlugin *plugin = GST_PLUGIN (g->data);
        LOGI ("found Plugin %s", gst_plugin_get_name (plugin));
        gst_object_unref (plugin);
    }
    g_list_free (list);

    //GstRegistry *registry = gst_registry_get();

    if (!registry) {
        LOGE("Failed to get gstreamer registry");
    }

    char *omx_decode_element_list[] = {
            "amcviddec-omxqcomvideodecoderh263",
            "amcviddec-omxqcomvideodecoderavc",
            "amcviddec-omxqcomvideodecoderhevc",
            "amcviddec-omxqcomvideodecodermpeg2",
            "amcviddec-omxqcomvideodecodermpeg4",
            "amcviddec-omxqcomvideodecodervp8",
            "amcviddec-omxqcomvideodecodervp9",
            "amcvidenc-omxqcomvideoencoderavc",
            "amcvidenc-omxqcomvideoencoderh263",
            "amcvidenc-omxqcomvideoencoderhevc",
            "amcvidenc-omxqcomvideoencodermpeg4",
            "amcvidenc-omxqcomvideoencodervp8"
    };

    for (int i = 0; i < ARRAYSIZE(omx_decode_element_list); i++) {
        GstPluginFeature *feature =
                gst_registry_lookup_feature(registry, omx_decode_element_list[i]);
        if (!feature) {
            LOGE("Featuer does not exist: %s", omx_decode_element_list[i]);
            continue;
        }

        gst_plugin_feature_set_rank(feature, GST_RANK_PRIMARY + 1);
        gst_registry_add_feature(registry, feature);
        gst_object_unref(feature);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_initMyPipeline(JNIEnv *env, jobject thiz, jobject surface) {
    GError *error = NULL;
    ANativeWindow *native_window = ANativeWindow_fromSurface(env, surface);

    // Initialize GStreamer
    gst_init(NULL, NULL);

    // Create the pipeline
    pipeline = gst_parse_launch("tcpclientsrc host=10.0.2.100 port=5000 ! h264parse ! avdec_h264 ! glimagesink", &error);
    //pipeline = gst_parse_launch("tcpclientsrc host=localhost port=5001 ! queue ! decodebin ! glimagesink", &error);
    //pipeline = gst_parse_launch("videotestsrc ! glimagesink", &error);
    if (!pipeline) {
        LOGE("Failed to create GStreamer pipeline: %s", error->message);
        g_clear_error(&error);
        return;
    }

    LOGI("GStreamer pipeline created successfully!");

    // Get glimagesink and set the SurfaceView as output
    GstElement *sink = gst_bin_get_by_interface(GST_BIN(pipeline), GST_TYPE_VIDEO_OVERLAY);
    if (!sink) {
        LOGE("glimagesink not found!");
        return;
    }

    LOGI("glimagesink found, setting native window...");
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(sink), (guintptr) native_window);
    gst_object_unref(sink);

    // Start playing the pipeline
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    LOGI("GStreamer pipeline playing...");
}
extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_stopMyPipeline(JNIEnv *env, jobject thiz) {
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        pipeline = NULL;
        LOGI("GStreamer pipeline stopped and cleaned up.");
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_org_freedesktop_gstreamer_GstAmcOnFrameAvailableListener_native_1onFrameAvailable(JNIEnv *env,
                                                                                       jobject thiz,
                                                                                       jlong context,
                                                                                       jobject surface_texture) {
    //
}