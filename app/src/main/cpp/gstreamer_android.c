#include <gst/gst.h>
#include <gio/gio.h>
#include <jni.h>

#define GST_G_IO_MODULE_DECLARE(name) \
extern void G_PASTE(g_io_, G_PASTE(name, _load)) (gpointer module)

#define GST_G_IO_MODULE_LOAD(name) \
G_PASTE(g_io_, G_PASTE(name, _load)) (NULL)

/* Declaration of static plugins */
GST_PLUGIN_STATIC_DECLARE(coreelements);
//GST_PLUGIN_STATIC_DECLARE(coretracers);
GST_PLUGIN_STATIC_DECLARE(adder);
GST_PLUGIN_STATIC_DECLARE(app);
//GST_PLUGIN_STATIC_DECLARE(audioconvert);
//GST_PLUGIN_STATIC_DECLARE(audiomixer);
//GST_PLUGIN_STATIC_DECLARE(audiorate);
//GST_PLUGIN_STATIC_DECLARE(audioresample);
//GST_PLUGIN_STATIC_DECLARE(audiotestsrc);
GST_PLUGIN_STATIC_DECLARE(compositor);
//GST_PLUGIN_STATIC_DECLARE(dsd);
//GST_PLUGIN_STATIC_DECLARE(basedebug);
GST_PLUGIN_STATIC_DECLARE(encoding);
GST_PLUGIN_STATIC_DECLARE(gio);
//GST_PLUGIN_STATIC_DECLARE(overlaycomposition);
//GST_PLUGIN_STATIC_DECLARE(pbtypes);
GST_PLUGIN_STATIC_DECLARE(playback);
//GST_PLUGIN_STATIC_DECLARE(rawparse);
//GST_PLUGIN_STATIC_DECLARE(subparse);
GST_PLUGIN_STATIC_DECLARE(tcp);
GST_PLUGIN_STATIC_DECLARE(typefindfunctions);
GST_PLUGIN_STATIC_DECLARE(videoconvertscale);
//GST_PLUGIN_STATIC_DECLARE(videorate);
GST_PLUGIN_STATIC_DECLARE(videotestsrc);
//GST_PLUGIN_STATIC_DECLARE(volume);
GST_PLUGIN_STATIC_DECLARE(opengl);
//GST_PLUGIN_STATIC_DECLARE(ogg);
//GST_PLUGIN_STATIC_DECLARE(opus);
GST_PLUGIN_STATIC_DECLARE(pango);
//GST_PLUGIN_STATIC_DECLARE(vorbis);
//GST_PLUGIN_STATIC_DECLARE(alpha);
//GST_PLUGIN_STATIC_DECLARE(alphacolor);
//GST_PLUGIN_STATIC_DECLARE(apetag);
//GST_PLUGIN_STATIC_DECLARE(audiofx);
GST_PLUGIN_STATIC_DECLARE(audioparsers);
//GST_PLUGIN_STATIC_DECLARE(auparse);
//GST_PLUGIN_STATIC_DECLARE(autodetect);
//GST_PLUGIN_STATIC_DECLARE(avi);
//GST_PLUGIN_STATIC_DECLARE(cutter);
//GST_PLUGIN_STATIC_DECLARE(navigationtest);
//GST_PLUGIN_STATIC_DECLARE(debug);
//GST_PLUGIN_STATIC_DECLARE(deinterlace);
//GST_PLUGIN_STATIC_DECLARE(dtmf);
GST_PLUGIN_STATIC_DECLARE(effectv);
//GST_PLUGIN_STATIC_DECLARE(equalizer);
//GST_PLUGIN_STATIC_DECLARE(flv);
//GST_PLUGIN_STATIC_DECLARE(flxdec);
//GST_PLUGIN_STATIC_DECLARE(goom);
//GST_PLUGIN_STATIC_DECLARE(goom2k1);
//GST_PLUGIN_STATIC_DECLARE(icydemux);
//GST_PLUGIN_STATIC_DECLARE(id3demux);
//GST_PLUGIN_STATIC_DECLARE(imagefreeze);
//GST_PLUGIN_STATIC_DECLARE(interleave);
//GST_PLUGIN_STATIC_DECLARE(isomp4);
//GST_PLUGIN_STATIC_DECLARE(alaw);
//GST_PLUGIN_STATIC_DECLARE(mulaw);
//GST_PLUGIN_STATIC_DECLARE(level);
GST_PLUGIN_STATIC_DECLARE(matroska);
//GST_PLUGIN_STATIC_DECLARE(monoscope);
GST_PLUGIN_STATIC_DECLARE(multifile);
//GST_PLUGIN_STATIC_DECLARE(multipart);
//GST_PLUGIN_STATIC_DECLARE(replaygain);
GST_PLUGIN_STATIC_DECLARE(rtp);
//GST_PLUGIN_STATIC_DECLARE(rtpmanager);
GST_PLUGIN_STATIC_DECLARE(rtsp);
//GST_PLUGIN_STATIC_DECLARE(shapewipe);
//GST_PLUGIN_STATIC_DECLARE(smpte);
//GST_PLUGIN_STATIC_DECLARE(spectrum);
//GST_PLUGIN_STATIC_DECLARE(udp);
//GST_PLUGIN_STATIC_DECLARE(videobox);
//GST_PLUGIN_STATIC_DECLARE(videocrop);
//GST_PLUGIN_STATIC_DECLARE(videofilter);
//GST_PLUGIN_STATIC_DECLARE(videomixer);
//GST_PLUGIN_STATIC_DECLARE(wavenc);
//GST_PLUGIN_STATIC_DECLARE(wavparse);
//GST_PLUGIN_STATIC_DECLARE(xingmux);
//GST_PLUGIN_STATIC_DECLARE(y4menc);
//GST_PLUGIN_STATIC_DECLARE(oss4);
//GST_PLUGIN_STATIC_DECLARE(video4linux2);
//GST_PLUGIN_STATIC_DECLARE(adaptivedemux2);
//GST_PLUGIN_STATIC_DECLARE(cairo);
//GST_PLUGIN_STATIC_DECLARE(flac);
//GST_PLUGIN_STATIC_DECLARE(jack);
//GST_PLUGIN_STATIC_DECLARE(jpeg);
//GST_PLUGIN_STATIC_DECLARE(lame);
//GST_PLUGIN_STATIC_DECLARE(dv);
//GST_PLUGIN_STATIC_DECLARE(png);
//GST_PLUGIN_STATIC_DECLARE(soup);
//GST_PLUGIN_STATIC_DECLARE(accurip);
//GST_PLUGIN_STATIC_DECLARE(adpcmdec);
//GST_PLUGIN_STATIC_DECLARE(adpcmenc);
//GST_PLUGIN_STATIC_DECLARE(aiff);
//GST_PLUGIN_STATIC_DECLARE(asfmux);
//GST_PLUGIN_STATIC_DECLARE(audiobuffersplit);
//GST_PLUGIN_STATIC_DECLARE(audiofxbad);
//GST_PLUGIN_STATIC_DECLARE(audiomixmatrix);
//GST_PLUGIN_STATIC_DECLARE(audiolatency);
//GST_PLUGIN_STATIC_DECLARE(audiovisualizers);
//GST_PLUGIN_STATIC_DECLARE(autoconvert);
//GST_PLUGIN_STATIC_DECLARE(bayer);
//GST_PLUGIN_STATIC_DECLARE(camerabin);
//GST_PLUGIN_STATIC_DECLARE(codecalpha);
//GST_PLUGIN_STATIC_DECLARE(codectimestamper);
//GST_PLUGIN_STATIC_DECLARE(coloreffects);
//GST_PLUGIN_STATIC_DECLARE(debugutilsbad);
//GST_PLUGIN_STATIC_DECLARE(dvbsubenc);
//GST_PLUGIN_STATIC_DECLARE(dvbsuboverlay);
//GST_PLUGIN_STATIC_DECLARE(dvdspu);
//GST_PLUGIN_STATIC_DECLARE(faceoverlay);
//GST_PLUGIN_STATIC_DECLARE(festival);
//GST_PLUGIN_STATIC_DECLARE(fieldanalysis);
//GST_PLUGIN_STATIC_DECLARE(freeverb);
//GST_PLUGIN_STATIC_DECLARE(frei0r);
//GST_PLUGIN_STATIC_DECLARE(gaudieffects);
//GST_PLUGIN_STATIC_DECLARE(gdp);
//GST_PLUGIN_STATIC_DECLARE(geometrictransform);
//GST_PLUGIN_STATIC_DECLARE(id3tag);
//GST_PLUGIN_STATIC_DECLARE(insertbin);
//GST_PLUGIN_STATIC_DECLARE(inter);
//GST_PLUGIN_STATIC_DECLARE(interlace);
//GST_PLUGIN_STATIC_DECLARE(ivfparse);
//GST_PLUGIN_STATIC_DECLARE(ivtc);
//GST_PLUGIN_STATIC_DECLARE(jp2kdecimator);
//GST_PLUGIN_STATIC_DECLARE(jpegformat);
//GST_PLUGIN_STATIC_DECLARE(rfbsrc);
//GST_PLUGIN_STATIC_DECLARE(midi);
//GST_PLUGIN_STATIC_DECLARE(mpegpsdemux);
//GST_PLUGIN_STATIC_DECLARE(mpegpsmux);
//GST_PLUGIN_STATIC_DECLARE(mpegtsdemux);
GST_PLUGIN_STATIC_DECLARE(mpegtsmux);
//GST_PLUGIN_STATIC_DECLARE(mse);
//GST_PLUGIN_STATIC_DECLARE(mxf);
//GST_PLUGIN_STATIC_DECLARE(netsim);
//GST_PLUGIN_STATIC_DECLARE(rtponvif);
//GST_PLUGIN_STATIC_DECLARE(pcapparse);
//GST_PLUGIN_STATIC_DECLARE(pnm);
//GST_PLUGIN_STATIC_DECLARE(proxy);
//GST_PLUGIN_STATIC_DECLARE(legacyrawparse);
//GST_PLUGIN_STATIC_DECLARE(removesilence);
//GST_PLUGIN_STATIC_DECLARE(rist);
//GST_PLUGIN_STATIC_DECLARE(rtmp2);
//GST_PLUGIN_STATIC_DECLARE(rtpmanagerbad);
//GST_PLUGIN_STATIC_DECLARE(sdpelem);
//GST_PLUGIN_STATIC_DECLARE(segmentclip);
//GST_PLUGIN_STATIC_DECLARE(siren);
//GST_PLUGIN_STATIC_DECLARE(smooth);
//GST_PLUGIN_STATIC_DECLARE(speed);
//GST_PLUGIN_STATIC_DECLARE(subenc);
//GST_PLUGIN_STATIC_DECLARE(switchbin);
//GST_PLUGIN_STATIC_DECLARE(tensordecoders);
//GST_PLUGIN_STATIC_DECLARE(timecode);
//GST_PLUGIN_STATIC_DECLARE(transcode);
//GST_PLUGIN_STATIC_DECLARE(unixfd);
//GST_PLUGIN_STATIC_DECLARE(videofiltersbad);
//GST_PLUGIN_STATIC_DECLARE(videoframe_audiolevel);
GST_PLUGIN_STATIC_DECLARE(videoparsersbad);
//GST_PLUGIN_STATIC_DECLARE(videosignal);
//GST_PLUGIN_STATIC_DECLARE(vmnc);
//GST_PLUGIN_STATIC_DECLARE(y4mdec);
GST_PLUGIN_STATIC_DECLARE(androidmedia);
//GST_PLUGIN_STATIC_DECLARE(dvb);
//GST_PLUGIN_STATIC_DECLARE(fbdevsink);
//GST_PLUGIN_STATIC_DECLARE(ipcpipeline);
//GST_PLUGIN_STATIC_DECLARE(opensles);
//GST_PLUGIN_STATIC_DECLARE(analyticsoverlay);
//GST_PLUGIN_STATIC_DECLARE(closedcaption);
//GST_PLUGIN_STATIC_DECLARE(codec2json);
//GST_PLUGIN_STATIC_DECLARE(dash);
//GST_PLUGIN_STATIC_DECLARE(fdkaac);
GST_PLUGIN_STATIC_DECLARE(hls);
//GST_PLUGIN_STATIC_DECLARE(microdns);
//GST_PLUGIN_STATIC_DECLARE(openh264);
//GST_PLUGIN_STATIC_DECLARE(openjpeg);
//GST_PLUGIN_STATIC_DECLARE(opusparse);
//GST_PLUGIN_STATIC_DECLARE(sctp);
//GST_PLUGIN_STATIC_DECLARE(smoothstreaming);
//GST_PLUGIN_STATIC_DECLARE(soundtouch);
//GST_PLUGIN_STATIC_DECLARE(srtp);
//GST_PLUGIN_STATIC_DECLARE(ttmlsubs);
//GST_PLUGIN_STATIC_DECLARE(webrtcdsp);
//GST_PLUGIN_STATIC_DECLARE(asf);
//GST_PLUGIN_STATIC_DECLARE(dvdlpcmdec);
//GST_PLUGIN_STATIC_DECLARE(dvdsub);
//GST_PLUGIN_STATIC_DECLARE(realmedia);
GST_PLUGIN_STATIC_DECLARE(x264);
GST_PLUGIN_STATIC_DECLARE(libav);
//GST_PLUGIN_STATIC_DECLARE(rtspclientsink);
//GST_PLUGIN_STATIC_DECLARE(nle);
//GST_PLUGIN_STATIC_DECLARE(ges);


/* Declaration of static gio modules */
GST_G_IO_MODULE_DECLARE(openssl);

#ifdef GSTREAMER_INCLUDE_CA_CERTIFICATES
static void gst_android_load_certificates(void) {
    GTlsBackend *backend;
    const gchar *ca_certs;

    ca_certs = g_getenv("CA_CERTIFICATES");

    backend = g_tls_backend_get_default();
    if (backend && ca_certs) {
        GTlsDatabase *db;
        GError *error = NULL;

        db = g_tls_file_database_new(ca_certs, &error);
        if (db) {
            g_tls_backend_set_default_database(backend, db);
            g_object_unref(db);
        } else {
            g_warning("Failed to create a database from file: %s",
                      error ? error->message : "Unknown");
        }
    }
}
#endif

/* Call this function to load GIO modules */
static void gst_android_load_gio_modules(void) {
    //GST_G_IO_MODULE_LOAD(openssl);

#ifdef GSTREAMER_INCLUDE_CA_CERTIFICATES
    gst_android_load_certificates();
#endif
}

/* This is called by gst_init() */
void gst_init_static_plugins(void) {
GST_PLUGIN_STATIC_REGISTER(coreelements);
//GST_PLUGIN_STATIC_REGISTER(coretracers);
GST_PLUGIN_STATIC_REGISTER(adder);
GST_PLUGIN_STATIC_REGISTER(app);
//GST_PLUGIN_STATIC_REGISTER(audioconvert);
//GST_PLUGIN_STATIC_REGISTER(audiomixer);
//GST_PLUGIN_STATIC_REGISTER(audiorate);
//GST_PLUGIN_STATIC_REGISTER(audioresample);
//GST_PLUGIN_STATIC_REGISTER(audiotestsrc);
GST_PLUGIN_STATIC_REGISTER(compositor);
//GST_PLUGIN_STATIC_REGISTER(dsd);
//GST_PLUGIN_STATIC_REGISTER(basedebug);
GST_PLUGIN_STATIC_REGISTER(encoding);
GST_PLUGIN_STATIC_REGISTER(gio);
//GST_PLUGIN_STATIC_REGISTER(overlaycomposition);
//GST_PLUGIN_STATIC_REGISTER(pbtypes);
GST_PLUGIN_STATIC_REGISTER(playback);
//GST_PLUGIN_STATIC_REGISTER(rawparse);
//GST_PLUGIN_STATIC_REGISTER(subparse);
GST_PLUGIN_STATIC_REGISTER(tcp);
GST_PLUGIN_STATIC_REGISTER(typefindfunctions);
GST_PLUGIN_STATIC_REGISTER(videoconvertscale);
//GST_PLUGIN_STATIC_REGISTER(videorate);
GST_PLUGIN_STATIC_REGISTER(videotestsrc);
//GST_PLUGIN_STATIC_REGISTER(volume);
GST_PLUGIN_STATIC_REGISTER(opengl);
//GST_PLUGIN_STATIC_REGISTER(ogg);
//GST_PLUGIN_STATIC_REGISTER(opus);
GST_PLUGIN_STATIC_REGISTER(pango);
//GST_PLUGIN_STATIC_REGISTER(vorbis);
//GST_PLUGIN_STATIC_REGISTER(alpha);
//GST_PLUGIN_STATIC_REGISTER(alphacolor);
//GST_PLUGIN_STATIC_REGISTER(apetag);
//GST_PLUGIN_STATIC_REGISTER(audiofx);
GST_PLUGIN_STATIC_REGISTER(audioparsers);
//GST_PLUGIN_STATIC_REGISTER(auparse);
//GST_PLUGIN_STATIC_REGISTER(autodetect);
//GST_PLUGIN_STATIC_REGISTER(avi);
//GST_PLUGIN_STATIC_REGISTER(cutter);
//GST_PLUGIN_STATIC_REGISTER(navigationtest);
//GST_PLUGIN_STATIC_REGISTER(debug);
//GST_PLUGIN_STATIC_REGISTER(deinterlace);
//GST_PLUGIN_STATIC_REGISTER(dtmf);
GST_PLUGIN_STATIC_REGISTER(effectv);
//GST_PLUGIN_STATIC_REGISTER(equalizer);
//GST_PLUGIN_STATIC_REGISTER(flv);
//GST_PLUGIN_STATIC_REGISTER(flxdec);
//GST_PLUGIN_STATIC_REGISTER(goom);
//GST_PLUGIN_STATIC_REGISTER(goom2k1);
//GST_PLUGIN_STATIC_REGISTER(icydemux);
//GST_PLUGIN_STATIC_REGISTER(id3demux);
//GST_PLUGIN_STATIC_REGISTER(imagefreeze);
//GST_PLUGIN_STATIC_REGISTER(interleave);
//GST_PLUGIN_STATIC_REGISTER(isomp4);
//GST_PLUGIN_STATIC_REGISTER(alaw);
//GST_PLUGIN_STATIC_REGISTER(mulaw);
//GST_PLUGIN_STATIC_REGISTER(level);
GST_PLUGIN_STATIC_REGISTER(matroska);
//GST_PLUGIN_STATIC_REGISTER(monoscope);
GST_PLUGIN_STATIC_REGISTER(multifile);
//GST_PLUGIN_STATIC_REGISTER(multipart);
//GST_PLUGIN_STATIC_REGISTER(replaygain);
GST_PLUGIN_STATIC_REGISTER(rtp);
//GST_PLUGIN_STATIC_REGISTER(rtpmanager);
GST_PLUGIN_STATIC_REGISTER(rtsp);
//GST_PLUGIN_STATIC_REGISTER(shapewipe);
//GST_PLUGIN_STATIC_REGISTER(smpte);
//GST_PLUGIN_STATIC_REGISTER(spectrum);
//GST_PLUGIN_STATIC_REGISTER(udp);
//GST_PLUGIN_STATIC_REGISTER(videobox);
//GST_PLUGIN_STATIC_REGISTER(videocrop);
//GST_PLUGIN_STATIC_REGISTER(videofilter);
//GST_PLUGIN_STATIC_REGISTER(videomixer);
//GST_PLUGIN_STATIC_REGISTER(wavenc);
//GST_PLUGIN_STATIC_REGISTER(wavparse);
//GST_PLUGIN_STATIC_REGISTER(xingmux);
//GST_PLUGIN_STATIC_REGISTER(y4menc);
//GST_PLUGIN_STATIC_REGISTER(oss4);
//GST_PLUGIN_STATIC_REGISTER(video4linux2);
//GST_PLUGIN_STATIC_REGISTER(adaptivedemux2);
//GST_PLUGIN_STATIC_REGISTER(cairo);
//GST_PLUGIN_STATIC_REGISTER(flac);
//GST_PLUGIN_STATIC_REGISTER(jack);
//GST_PLUGIN_STATIC_REGISTER(jpeg);
//GST_PLUGIN_STATIC_REGISTER(lame);
//GST_PLUGIN_STATIC_REGISTER(dv);
//GST_PLUGIN_STATIC_REGISTER(png);
//GST_PLUGIN_STATIC_REGISTER(soup);
//GST_PLUGIN_STATIC_REGISTER(accurip);
//GST_PLUGIN_STATIC_REGISTER(adpcmdec);
//GST_PLUGIN_STATIC_REGISTER(adpcmenc);
//GST_PLUGIN_STATIC_REGISTER(aiff);
//GST_PLUGIN_STATIC_REGISTER(asfmux);
//GST_PLUGIN_STATIC_REGISTER(audiobuffersplit);
//GST_PLUGIN_STATIC_REGISTER(audiofxbad);
//GST_PLUGIN_STATIC_REGISTER(audiomixmatrix);
//GST_PLUGIN_STATIC_REGISTER(audiolatency);
//GST_PLUGIN_STATIC_REGISTER(audiovisualizers);
//GST_PLUGIN_STATIC_REGISTER(autoconvert);
//GST_PLUGIN_STATIC_REGISTER(bayer);
//GST_PLUGIN_STATIC_REGISTER(camerabin);
//GST_PLUGIN_STATIC_REGISTER(codecalpha);
//GST_PLUGIN_STATIC_REGISTER(codectimestamper);
//GST_PLUGIN_STATIC_REGISTER(coloreffects);
//GST_PLUGIN_STATIC_REGISTER(debugutilsbad);
//GST_PLUGIN_STATIC_REGISTER(dvbsubenc);
//GST_PLUGIN_STATIC_REGISTER(dvbsuboverlay);
//GST_PLUGIN_STATIC_REGISTER(dvdspu);
//GST_PLUGIN_STATIC_REGISTER(faceoverlay);
//GST_PLUGIN_STATIC_REGISTER(festival);
//GST_PLUGIN_STATIC_REGISTER(fieldanalysis);
//GST_PLUGIN_STATIC_REGISTER(freeverb);
//GST_PLUGIN_STATIC_REGISTER(frei0r);
//GST_PLUGIN_STATIC_REGISTER(gaudieffects);
//GST_PLUGIN_STATIC_REGISTER(gdp);
//GST_PLUGIN_STATIC_REGISTER(geometrictransform);
//GST_PLUGIN_STATIC_REGISTER(id3tag);
//GST_PLUGIN_STATIC_REGISTER(insertbin);
//GST_PLUGIN_STATIC_REGISTER(inter);
//GST_PLUGIN_STATIC_REGISTER(interlace);
//GST_PLUGIN_STATIC_REGISTER(ivfparse);
//GST_PLUGIN_STATIC_REGISTER(ivtc);
//GST_PLUGIN_STATIC_REGISTER(jp2kdecimator);
//GST_PLUGIN_STATIC_REGISTER(jpegformat);
//GST_PLUGIN_STATIC_REGISTER(rfbsrc);
//GST_PLUGIN_STATIC_REGISTER(midi);
//GST_PLUGIN_STATIC_REGISTER(mpegpsdemux);
//GST_PLUGIN_STATIC_REGISTER(mpegpsmux);
//GST_PLUGIN_STATIC_REGISTER(mpegtsdemux);
GST_PLUGIN_STATIC_REGISTER(mpegtsmux);
//GST_PLUGIN_STATIC_REGISTER(mse);
//GST_PLUGIN_STATIC_REGISTER(mxf);
//GST_PLUGIN_STATIC_REGISTER(netsim);
//GST_PLUGIN_STATIC_REGISTER(rtponvif);
//GST_PLUGIN_STATIC_REGISTER(pcapparse);
//GST_PLUGIN_STATIC_REGISTER(pnm);
//GST_PLUGIN_STATIC_REGISTER(proxy);
//GST_PLUGIN_STATIC_REGISTER(legacyrawparse);
//GST_PLUGIN_STATIC_REGISTER(removesilence);
//GST_PLUGIN_STATIC_REGISTER(rist);
//GST_PLUGIN_STATIC_REGISTER(rtmp2);
//GST_PLUGIN_STATIC_REGISTER(rtpmanagerbad);
//GST_PLUGIN_STATIC_REGISTER(sdpelem);
//GST_PLUGIN_STATIC_REGISTER(segmentclip);
//GST_PLUGIN_STATIC_REGISTER(siren);
//GST_PLUGIN_STATIC_REGISTER(smooth);
//GST_PLUGIN_STATIC_REGISTER(speed);
//GST_PLUGIN_STATIC_REGISTER(subenc);
//GST_PLUGIN_STATIC_REGISTER(switchbin);
//GST_PLUGIN_STATIC_REGISTER(tensordecoders);
//GST_PLUGIN_STATIC_REGISTER(timecode);
//GST_PLUGIN_STATIC_REGISTER(transcode);
//GST_PLUGIN_STATIC_REGISTER(unixfd);
//GST_PLUGIN_STATIC_REGISTER(videofiltersbad);
//GST_PLUGIN_STATIC_REGISTER(videoframe_audiolevel);
GST_PLUGIN_STATIC_REGISTER(videoparsersbad);
//GST_PLUGIN_STATIC_REGISTER(videosignal);
//GST_PLUGIN_STATIC_REGISTER(vmnc);
//GST_PLUGIN_STATIC_REGISTER(y4mdec);
GST_PLUGIN_STATIC_REGISTER(androidmedia);
//GST_PLUGIN_STATIC_REGISTER(dvb);
//GST_PLUGIN_STATIC_REGISTER(fbdevsink);
//GST_PLUGIN_STATIC_REGISTER(ipcpipeline);
//GST_PLUGIN_STATIC_REGISTER(opensles);
//GST_PLUGIN_STATIC_REGISTER(analyticsoverlay);
//GST_PLUGIN_STATIC_REGISTER(closedcaption);
//GST_PLUGIN_STATIC_REGISTER(codec2json);
//GST_PLUGIN_STATIC_REGISTER(dash);
//GST_PLUGIN_STATIC_REGISTER(fdkaac);
GST_PLUGIN_STATIC_REGISTER(hls);
//GST_PLUGIN_STATIC_REGISTER(microdns);
//GST_PLUGIN_STATIC_REGISTER(openh264);
//GST_PLUGIN_STATIC_REGISTER(openjpeg);
//GST_PLUGIN_STATIC_REGISTER(opusparse);
//GST_PLUGIN_STATIC_REGISTER(sctp);
//GST_PLUGIN_STATIC_REGISTER(smoothstreaming);
//GST_PLUGIN_STATIC_REGISTER(soundtouch);
//GST_PLUGIN_STATIC_REGISTER(srtp);
//GST_PLUGIN_STATIC_REGISTER(ttmlsubs);
//GST_PLUGIN_STATIC_REGISTER(webrtcdsp);
//GST_PLUGIN_STATIC_REGISTER(asf);
//GST_PLUGIN_STATIC_REGISTER(dvdlpcmdec);
//GST_PLUGIN_STATIC_REGISTER(dvdsub);
//GST_PLUGIN_STATIC_REGISTER(realmedia);
GST_PLUGIN_STATIC_REGISTER(x264);
GST_PLUGIN_STATIC_REGISTER(libav);
//GST_PLUGIN_STATIC_REGISTER(rtspclientsink);
//GST_PLUGIN_STATIC_REGISTER(nle);
//GST_PLUGIN_STATIC_REGISTER(ges);
    gst_android_load_gio_modules();
}