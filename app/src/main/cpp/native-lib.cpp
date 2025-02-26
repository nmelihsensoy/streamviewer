#include <jni.h>
#include <android/log.h>
#include <gst/gst.h>
#include <unistd.h>
#include <gst/video/videooverlay.h>
#include <android/native_window_jni.h>
#include <thread>
#include <gst/app/gstappsink.h>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "opencv2/dnn.hpp"

#define LOG_TAG "GStreamer"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static GstElement *pipeline = nullptr;
static ANativeWindow *native_window = nullptr;
static GMainLoop *main_loop = nullptr;
static GstElement *app_sink = nullptr;
static std::thread main_loop_thread;
static jobject global_app = nullptr;
static JavaVM *java_vm;

jint JNI_OnLoad(JavaVM *vm, void *) {
    java_vm = vm;
    return JNI_VERSION_1_6;
}

JNIEnv *GetJniEnv() {
    JNIEnv *env;
    jint result = java_vm->AttachCurrentThread(&env, nullptr);
    return result == JNI_OK ? env : nullptr;
}

void start_main_loop() {
    if (!main_loop) {
        main_loop = g_main_loop_new(nullptr, FALSE);
        LOGI("GMainLoop created for bus messages.");
    }
    if (!g_main_loop_is_running(main_loop)) {
        LOGI("Starting GMainLoop in a separate thread...");
        main_loop_thread = std::thread([]() {
            g_main_loop_run(main_loop);
        });
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_org_freedesktop_gstreamer_GStreamer_nativeInit(JNIEnv *env, jclass clazz, jobject context) {
}

void setWindow(){
    GstElement *videosink = gst_bin_get_by_interface(GST_BIN(pipeline), GST_TYPE_VIDEO_OVERLAY);
    if (videosink) {
        g_object_set(videosink, "force-aspect-ratio", TRUE, NULL);
        g_object_set(videosink, "sync", FALSE, NULL);
        g_object_set(videosink, "max-lateness", 0, NULL);
        g_object_set(videosink, "qos", TRUE, NULL);
        gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(videosink), (guintptr) native_window);
        gst_object_unref(videosink);
    }
}

void setAppSink(){
    app_sink = gst_bin_get_by_name(GST_BIN(pipeline), "app-sink");
    if (app_sink) {
        g_object_set(G_OBJECT(app_sink),
                     "emit-signals", FALSE,
                     "sync", FALSE,
                     "max-buffers", 1,
                     "drop", TRUE,
                     NULL);
        LOGI("AppSink element successfully configured.");
        gst_object_unref(app_sink);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_setSurface(JNIEnv *env, jclass clazz, jobject surface) {
    if (native_window) {
        ANativeWindow_release(native_window);
        native_window = nullptr;
    }

    if (surface) {
        native_window = ANativeWindow_fromSurface(env, surface);
        LOGI("Surface set");

        if (pipeline) {
            setWindow();
        }
    } else {
        LOGI("Surface cleared");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_nativeCleanup(JNIEnv *env, jclass clazz) {
    LOGI("Quitting main loop...");
    if (main_loop) {
        g_main_loop_quit(main_loop);
    }
    if (main_loop_thread.joinable()) {
        LOGI("Waiting for main loop thread to finish...");
        main_loop_thread.join();
    }
    LOGI("Deleting GlobalRef for app object at %p", global_app);
    if (global_app) {
        env->DeleteGlobalRef(global_app);
        global_app = nullptr;
    }
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        pipeline = nullptr;
    }
    if (main_loop) {
        g_main_loop_unref(main_loop);
        main_loop = nullptr;
    }
    if (native_window) {
        ANativeWindow_release(native_window);
        native_window = nullptr;
    }
    if (app_sink) {
        gst_object_unref(app_sink);
        app_sink = nullptr;
    }
    LOGI("GStreamer cleanup complete");
}

void callJavaMethod(const char *methodName, const char *signature, const char *message) {
    JNIEnv *env = GetJniEnv();
    if (env == nullptr) {
        LOGE("Failed to get JNI environment");
        return;
    }

    if (global_app == nullptr) {
        LOGE("Global app reference is null");
        return;
    }

    jclass appClass = env->GetObjectClass(global_app);
    if (appClass == nullptr) {
        LOGE("Failed to find app class");
        return;
    }

    jmethodID methodId = env->GetMethodID(appClass, methodName, signature);
    if (methodId == nullptr) {
        LOGE("Failed to find method: %s", methodName);
        return;
    }

    jstring jMessage = env->NewStringUTF(message);
    if (jMessage == nullptr) {
        LOGE("Failed to create Java string");
        return;
    }

    env->CallVoidMethod(global_app, methodId, jMessage);

    env->DeleteLocalRef(jMessage);
    env->DeleteLocalRef(appClass);
}

void sendStateUpdate(const char *message) {
    callJavaMethod("stateUpdates", "(Ljava/lang/String;)V", message);
}

static gboolean on_bus_message(GstBus *bus, GstMessage *msg, gpointer data) {
    GError *err;
    gchar *debug_info;
    const GstStructure *s = NULL;
    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_ERROR:
            gst_message_parse_error(msg, &err, &debug_info);
            sendStateUpdate("error");
            g_error_free(err);
            g_free(debug_info);
        break;

        case GST_MESSAGE_STATE_CHANGED:
            if (GST_MESSAGE_SRC(msg) == GST_OBJECT(pipeline)) {
                GstState old_state, new_state, pending_state;
                gst_message_parse_state_changed(msg, &old_state, &new_state, &pending_state);

                if (new_state == GST_STATE_PAUSED) {
                    sendStateUpdate("connecting");
                } else if (new_state == GST_STATE_PLAYING) {
                    sendStateUpdate("playing");
                }
            }
            break;


        case GST_MESSAGE_ELEMENT:
            // Check for a network-status message.
            s = gst_message_get_structure(msg);
            if (gst_structure_has_name(s, "network-status")) {
                const gchar *status = gst_structure_get_string(s, "status");
                if (status) {
                    if (g_strcmp0(status, "connecting") == 0) {
                        sendStateUpdate("Attempting to connect to network resource.");
                    } else if (g_strcmp0(status, "connected") == 0) {
                        sendStateUpdate("Network resource connected.");
                    } else if (g_strcmp0(status, "disconnected") == 0) {
                        sendStateUpdate("Network resource disconnected unexpectedly.");
                    }
                }
            }
            break;

        default:
            const gchar *msg_type_name = gst_message_type_get_name(GST_MESSAGE_TYPE(msg));
            //g_print("Message type: %s\n", msg_type_name);
            sendStateUpdate(msg_type_name);
        break;
    }
    return true;
}
extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_setPipeline(JNIEnv *env, jclass clazz, jstring pipelineDesc) {
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        pipeline = nullptr;
    }

    const char *pipeline_str = env->GetStringUTFChars(pipelineDesc, nullptr);
    if (!pipeline_str) {
        LOGE("Failed to get pipeline string");
        return;
    }

    pipeline = gst_parse_launch(pipeline_str, nullptr);
    env->ReleaseStringUTFChars(pipelineDesc, pipeline_str);

    if (!pipeline) {
        LOGE("Failed to create pipeline");
        return;
    }

    setWindow();
    setAppSink();

    GstBus *bus = gst_element_get_bus(pipeline);
    gst_bus_add_watch(bus, on_bus_message, nullptr);
    gst_object_unref(bus);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_nativeGetGStreamerInfo(JNIEnv *env, jobject thiz) {
    char *version_utf8 = gst_version_string();
    return env->NewStringUTF(version_utf8);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_gstListPlugins(JNIEnv *env, jclass clazz) {
    //gst_init(nullptr, nullptr);
    GList *g;
    GstRegistry *registry = gst_registry_get();
    GList *list = gst_registry_get_plugin_list(registry);
    for (g = list; g; g = g->next) {
        GstPlugin *plugin = GST_PLUGIN(g->data);
        LOGI("found Plugin %s", gst_plugin_get_name(plugin));
        gst_object_unref(plugin);
    }
    g_list_free(list);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_pausePipeline(JNIEnv *env, jclass clazz) {
    if(pipeline){
        gst_element_set_state(pipeline, GST_STATE_PAUSED);
        LOGI("Pipeline set paused");
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_playPipeline(JNIEnv *env, jclass clazz) {
    if(pipeline){
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
        LOGI("Pipeline set and playing");
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_nativeInit(JNIEnv *env, jobject thiz, jobject context) {
    gst_init(nullptr, nullptr);
    LOGI("GStreamer initialized");
    global_app = env->NewGlobalRef(context);
    if (!global_app) {
        LOGE("Failed to create global reference for application context");
    } else {
        LOGI("Successfully stored global application reference: %p", global_app);
    }
    start_main_loop();
}

std::string callJavaGetOnnxModelPath() {
    JNIEnv* env = GetJniEnv();
    if (env == nullptr) {
        LOGE("Failed to get JNI environment");
        return "";
    }
    if (global_app == nullptr) {
        LOGE("Global app reference is null");
        return "";
    }

    // Get the class of the global app object.
    jclass appClass = env->GetObjectClass(global_app);
    if (appClass == nullptr) {
        LOGE("Failed to find app class");
        return "";
    }

    // Get the method ID for getOnnxModelPath: "()Ljava/lang/String;"
    jmethodID methodId = env->GetMethodID(appClass, "getOnnxModelPath", "()Ljava/lang/String;");
    if (methodId == nullptr) {
        LOGE("Failed to find getOnnxModelPath method");
        env->DeleteLocalRef(appClass);
        return "";
    }

    // Call the method.
    jstring jModelPath = (jstring)env->CallObjectMethod(global_app, methodId);
    if (jModelPath == nullptr) {
        LOGE("getOnnxModelPath returned null");
        env->DeleteLocalRef(appClass);
        return "";
    }

    // Convert the jstring to a C++ std::string.
    const char* cStr = env->GetStringUTFChars(jModelPath, nullptr);
    std::string modelPath(cStr);
    env->ReleaseStringUTFChars(jModelPath, cStr);

    // Clean up local references.
    env->DeleteLocalRef(jModelPath);
    env->DeleteLocalRef(appClass);

    return modelPath;
}

extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_saveRawFrame(JNIEnv *env, jobject thiz) {
    if (!pipeline) {
        LOGE("Pipeline is not initialized.");
        return;
    }

    if (!app_sink) {
        LOGE("Failed to get appsink element.");
        return;
    }

    GstSample *sample = gst_app_sink_try_pull_sample(GST_APP_SINK(app_sink), 0);
    if (!sample) {
        LOGE("Failed to pull sample from appsink.");
        return;
    }

    GstBuffer *buffer = gst_sample_get_buffer(sample);
    if (!buffer) {
        LOGE("Failed to get buffer from sample.");
        gst_sample_unref(sample);
        return;
    }

    GstMapInfo map;
    if (!gst_buffer_map(buffer, &map, GST_MAP_READ)) {
        LOGE("Failed to map buffer.");
        gst_sample_unref(sample);
        return;
    }

    GstCaps *caps = gst_sample_get_caps(sample);
    const gchar *format = gst_caps_to_string(caps);
    LOGI("Frame format: %s", format);

    const char *filePath = "/sdcard/Download/frame2.raw";
    //const char *filePath = "/data/data/org.nmelihsensoy.streamviewer/files/frame1.raw";
    std::ofstream outFile(filePath, std::ios::out | std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(map.data), map.size);
        LOGI("Frame saved to %s, size: %zu bytes", filePath, map.size);
        outFile.close();
    } else {
        LOGE("Failed to open file for writing.");
    }

    gst_buffer_unmap(buffer, &map);
    gst_sample_unref(sample);
}
extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_savePngFrame(JNIEnv *env, jobject thiz) {
    if (!pipeline) {
        LOGE("Pipeline is not initialized.");
        return;
    }

    if (!app_sink) {
        LOGE("Failed to get appsink element.");
        return;
    }

    // Pull a sample from the appsink
    GstSample *sample = gst_app_sink_try_pull_sample(GST_APP_SINK(app_sink), 0);
    if (!sample) {
        LOGE("Failed to pull sample from appsink.");
        return;
    }

    GstBuffer *buffer = gst_sample_get_buffer(sample);
    if (!buffer) {
        LOGE("Failed to get buffer from sample.");
        gst_sample_unref(sample);
        return;
    }

    // Map the buffer to access its memory
    GstMapInfo map;
    if (!gst_buffer_map(buffer, &map, GST_MAP_READ)) {
        LOGE("Failed to map buffer.");
        gst_sample_unref(sample);
        return;
    }

    // Retrieve the caps from the sample and get video info
    GstCaps *caps = gst_sample_get_caps(sample);
    if (!caps) {
        LOGE("Failed to get caps from sample.");
        gst_buffer_unmap(buffer, &map);
        gst_sample_unref(sample);
        return;
    }

    GstVideoInfo vinfo;
    if (!gst_video_info_from_caps(&vinfo, caps)) {
        LOGE("Failed to parse video info from caps.");
        gst_buffer_unmap(buffer, &map);
        gst_sample_unref(sample);
        return;
    }

    int width = GST_VIDEO_INFO_WIDTH(&vinfo);
    int height = GST_VIDEO_INFO_HEIGHT(&vinfo);
    GstVideoFormat gst_format = GST_VIDEO_INFO_FORMAT(&vinfo);
    const gchar *format = gst_caps_to_string(caps);
    LOGI("Frame format: %s", format);

    // Determine the OpenCV type and whether a color conversion is needed.
    cv::Mat frame;
    bool needsConversion = false;
    int conversionCode = 0;

    switch (gst_format) {
        case GST_VIDEO_FORMAT_BGR:
            // Data is already in BGR format (CV_8UC3)
            frame = cv::Mat(height, width, CV_8UC3, map.data);
            break;
        case GST_VIDEO_FORMAT_RGB:
            // Data is in RGB; convert to BGR for OpenCV
            frame = cv::Mat(height, width, CV_8UC3, map.data);
            needsConversion = true;
            conversionCode = cv::COLOR_RGB2BGR;
            break;
        case GST_VIDEO_FORMAT_BGRA:
            // Data is in BGRA; remove alpha channel (convert to BGR)
            frame = cv::Mat(height, width, CV_8UC4, map.data);
            needsConversion = true;
            conversionCode = cv::COLOR_BGRA2BGR;
            break;
        case GST_VIDEO_FORMAT_RGBA:
            // Data is in RGBA; convert to BGR
            frame = cv::Mat(height, width, CV_8UC4, map.data);
            needsConversion = true;
            conversionCode = cv::COLOR_RGBA2BGR;
            break;
        case GST_VIDEO_FORMAT_I420:
            frame = cv::Mat(height, width, CV_8UC4, map.data);
            needsConversion = true;
            conversionCode = cv::COLOR_YUV2BGR_I420;
            break;
        case GST_VIDEO_FORMAT_RGBx:
            frame = cv::Mat(height, width, CV_8UC4, map.data);
            needsConversion = true;
            conversionCode = cv::COLOR_RGBA2BGR;
            break;
        case GST_VIDEO_FORMAT_NV12:
            frame = cv::Mat(height + height / 2, width, CV_8UC1, map.data);
            //cv::Mat NV12 = cv::Mat(height * 3/2, Width, CV_8UC1, nv12Buffer);
            needsConversion = true;
            conversionCode = cv::COLOR_YUV2BGR_NV12;
            break;

        default:
            LOGE("Unsupported video format.");
            const gchar *format_str = gst_video_format_to_string(gst_format);
            LOGI("%s", format_str);
            gst_buffer_unmap(buffer, &map);
            gst_sample_unref(sample);
            return;
    }

    // If needed, convert the color format to BGR (OpenCV default)
    if (needsConversion) {
        cv::Mat converted;
        cv::cvtColor(frame, converted, conversionCode);
        frame = converted;
    }

    // Save the frame as a PNG image using OpenCV's imwrite
    const char *filePath = "/sdcard/Download/frame.png";
    if (cv::imwrite(filePath, frame)) {
        LOGI("Frame saved to %s, size: %zu bytes (raw buffer size: %zu)", filePath, frame.total() * frame.elemSize(), map.size);
    } else {
        LOGE("Failed to write PNG image to file.");
    }

    // Cleanup: unmap the buffer and unref the sample
    gst_buffer_unmap(buffer, &map);
    gst_sample_unref(sample);
}

void printMatShape(const cv::Mat &mat) {
    LOGI("Rows: %d, Cols: %d, Channels: %d", mat.rows, mat.cols, mat.channels());
    std::ostringstream oss;
    oss << "[";
    for (int i = 0; i < mat.dims; i++) {
        oss << mat.size[i];
        if (i < mat.dims - 1) {
            oss << ", ";
        }
    }
    oss << "]";
    LOGI("Output shape: %s", oss.str().c_str());
    LOGI("Type: %d", mat.type());
}

extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_runFrameInference(JNIEnv *env, jobject thiz) {
    if (!pipeline) {
        LOGE("Pipeline is not initialized.");
        return;
    }

    if (!app_sink) {
        LOGE("Failed to get appsink element.");
        return;
    }

    // Pull a sample from the appsink
    GstSample *sample = gst_app_sink_try_pull_sample(GST_APP_SINK(app_sink), 0);
    if (!sample) {
        LOGE("Failed to pull sample from appsink.");
        return;
    }

    GstBuffer *buffer = gst_sample_get_buffer(sample);
    if (!buffer) {
        LOGE("Failed to get buffer from sample.");
        gst_sample_unref(sample);
        return;
    }

    // Map the buffer to access its memory
    GstMapInfo map;
    if (!gst_buffer_map(buffer, &map, GST_MAP_READ)) {
        LOGE("Failed to map buffer.");
        gst_sample_unref(sample);
        return;
    }

    // Retrieve the caps from the sample and get video info
    GstCaps *caps = gst_sample_get_caps(sample);
    if (!caps) {
        LOGE("Failed to get caps from sample.");
        gst_buffer_unmap(buffer, &map);
        gst_sample_unref(sample);
        return;
    }

    GstVideoInfo vinfo;
    if (!gst_video_info_from_caps(&vinfo, caps)) {
        LOGE("Failed to parse video info from caps.");
        gst_buffer_unmap(buffer, &map);
        gst_sample_unref(sample);
        return;
    }

    int width = GST_VIDEO_INFO_WIDTH(&vinfo);
    int height = GST_VIDEO_INFO_HEIGHT(&vinfo);
    GstVideoFormat gst_format = GST_VIDEO_INFO_FORMAT(&vinfo);
    const gchar *format = gst_caps_to_string(caps);
    LOGI("Frame format: %s", format);

    // Determine the OpenCV type and whether a color conversion is needed.
    cv::Mat frame;
    bool needsConversion = false;
    int conversionCode = 0;

    switch (gst_format) {
        case GST_VIDEO_FORMAT_BGR:
            // Data is already in BGR format (CV_8UC3)
            frame = cv::Mat(height, width, CV_8UC3, map.data);
            break;
        case GST_VIDEO_FORMAT_RGB:
            // Data is in RGB; convert to BGR for OpenCV
            frame = cv::Mat(height, width, CV_8UC3, map.data);
            needsConversion = true;
            conversionCode = cv::COLOR_RGB2BGR;
            break;
        case GST_VIDEO_FORMAT_BGRA:
            // Data is in BGRA; remove alpha channel (convert to BGR)
            frame = cv::Mat(height, width, CV_8UC4, map.data);
            needsConversion = true;
            conversionCode = cv::COLOR_BGRA2BGR;
            break;
        case GST_VIDEO_FORMAT_RGBA:
            // Data is in RGBA; convert to BGR
            frame = cv::Mat(height, width, CV_8UC4, map.data);
            needsConversion = true;
            conversionCode = cv::COLOR_RGBA2BGR;
            break;
        case GST_VIDEO_FORMAT_I420:
            frame = cv::Mat(height, width, CV_8UC4, map.data);
            needsConversion = true;
            conversionCode = cv::COLOR_YUV2BGR_I420;
            break;
        case GST_VIDEO_FORMAT_RGBx:
            frame = cv::Mat(height, width, CV_8UC4, map.data);
            needsConversion = true;
            conversionCode = cv::COLOR_RGBA2BGR;
            break;
        case GST_VIDEO_FORMAT_NV12:
            frame = cv::Mat(height + height / 2, width, CV_8UC1, map.data);
            //cv::Mat NV12 = cv::Mat(height * 3/2, Width, CV_8UC1, nv12Buffer);
            needsConversion = true;
            conversionCode = cv::COLOR_YUV2BGR_NV12;
            break;

        default:
            LOGE("Unsupported video format.");
            const gchar *format_str = gst_video_format_to_string(gst_format);
            LOGI("%s", format_str);
            gst_buffer_unmap(buffer, &map);
            gst_sample_unref(sample);
            return;
    }

    if (needsConversion) {
        cv::Mat converted;
        cv::cvtColor(frame, converted, conversionCode);
        frame = converted;
    }

    // Prepare a square image for inference
    int length = std::max(height, width);
    cv::Mat image = cv::Mat::zeros(length, length, CV_8UC3);
    frame.copyTo(image(cv::Rect(0, 0, width, height)));
    double scaleFactor = static_cast<double>(length) / 640.0;
    cv::Mat blob = cv::dnn::blobFromImage(image, 1.0 / 255.0, cv::Size(640, 640),
                                          cv::Scalar(), true, false);

    std::string modelAssetsPath = callJavaGetOnnxModelPath();
    LOGI("onnx model path: %s", modelAssetsPath.c_str());
    cv::dnn::Net model = cv::dnn::readNetFromONNX(modelAssetsPath);
    if (model.empty()) {
        LOGE("Failed to load model");
        return;
    }
    model.setInput(blob);
    cv::Mat output = model.forward();
    printMatShape(output); //Output shape: [1, 84, 8400] Rows: -1, Cols: -1, Channels: 1

    cv::Mat reshaped = output.reshape(1, output.size[1]);
    printMatShape(reshaped); //Output shape: [84, 8400] Rows: 84, Cols: 8400, Channels: 1

    cv::Mat transposed;
    cv::transpose(reshaped, transposed);
    printMatShape(transposed); //Output shape: [8400, 84] Rows: 8400, Cols: 84, Channels: 1



    gst_buffer_unmap(buffer, &map);
    gst_sample_unref(sample);
}
extern "C"
JNIEXPORT void JNICALL
Java_org_nmelihsensoy_streamviewer_MainActivity_nativeOpenCVInfo(JNIEnv *env, jclass clazz) {
    LOGI("OpenCV Version: %s, Version String: %s", CV_VERSION, cv::getVersionString().c_str());
    std::string buildInfo = cv::getBuildInformation();
    LOGI("OpenCV Build Information:\n%s", buildInfo.c_str());

    try {
        cv::Mat identity = cv::Mat::eye(3, 3, CV_32F);
        if (!identity.empty()) {
            LOGI("Core module test (Mat::eye): Success");
        } else {
            LOGE("Core module test (Mat::eye): Failed");
        }

        cv::Mat dummyImage = cv::Mat::zeros(100, 100, CV_8UC3);
        cv::Mat blob = cv::dnn::blobFromImage(dummyImage);
        if (!blob.empty()) {
            LOGI("DNN module test (blobFromImage): Success");
        } else {
            LOGE("DNN module test (blobFromImage): Failed");
        }
    } catch (const cv::Exception& e) {
        LOGE("Exception during plugin tests: %s", e.what());
    }
}