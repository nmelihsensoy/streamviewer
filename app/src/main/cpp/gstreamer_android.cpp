#include <gst/gst.h>
#include <gio/gio.h>
#include <jni.h>

#define GST_G_IO_MODULE_DECLARE(name) \
extern void G_PASTE(g_io_, G_PASTE(name, _load)) (gpointer module)

#define GST_G_IO_MODULE_LOAD(name) \
G_PASTE(g_io_, G_PASTE(name, _load)) (NULL)

/* Declaration of static plugins */

//GST_PLUGIN_STATIC_DECLARE(coreelements);

/* Declaration of static gio modules */

GST_G_IO_MODULE_DECLARE(openssl);;

#ifdef GSTREAMER_INCLUDE_CA_CERTIFICATES
static void
gst_android_load_certificates (void)
{
  GTlsBackend *backend;
  const gchar *ca_certs;

  ca_certs = g_getenv ("CA_CERTIFICATES");

  backend = g_tls_backend_get_default ();
  if (backend && ca_certs) {
    GTlsDatabase *db;
    GError *error = NULL;

    db = g_tls_file_database_new (ca_certs, &error);
    if (db) {
      g_tls_backend_set_default_database (backend, db);
      g_object_unref (db);
    } else {
      g_warning ("Failed to create a database from file: %s",
          error ? error->message : "Unknown");
    }
  }
}
#endif

/* Call this function to load GIO modules */
static void
gst_android_load_gio_modules (void)
{

    //GST_G_IO_MODULE_LOAD(openssl);

#ifdef GSTREAMER_INCLUDE_CA_CERTIFICATES
    gst_android_load_certificates ();
#endif
}

/* This is called by gst_init() */
void
gst_init_static_plugins (void)
{

    //GST_PLUGIN_STATIC_REGISTER(coreelements);
    gst_android_load_gio_modules ();
}

extern "C"
JNIEXPORT void JNICALL
Java_org_freedesktop_gstreamer_GStreamer_nativeInit(JNIEnv *env, jclass clazz, jobject context) {
    gst_init(nullptr, nullptr);
}