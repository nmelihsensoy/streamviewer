#include <string.h>
#include <jni.h>
#include <android/log.h>
#include <gst/gst.h>

extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    GstElement *pipeline;
    GError *error = NULL;

    /* Initialize GStreamer */
    gst_init(NULL, NULL);

    /* Create the pipeline */
    pipeline = gst_parse_launch(
            "tcpclientsrc host=localhost port=5000 ! h264parse ! avdec_h264 ! autovideosink",
            &error
    );

    if (error) {
        //LOGE("Pipeline error: %s", error->message);
        g_clear_error(&error);
        return;
    }

    /* Start playback */
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}