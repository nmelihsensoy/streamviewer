cmake_minimum_required(VERSION 3.22.1)

project("streamviewer")

if(NOT DEFINED GSTREAMER_DEVEL_ANDROID)
    message(FATAL_ERROR "GSTREAMER_DEVEL_ANDROID is not defined!")
endif()

if ("${ANDROID_ABI}" STREQUAL "arm64-v8a")
    set(GST_ABI "arm64")
elseif("${ANDROID_ABI}" STREQUAL "armeabi-v7a")
    set(GST_ABI "armv7")
    set(NEEDS_NOTEXT_FIX TRUE)
elseif("${ANDROID_ABI}" STREQUAL "x86")
    set(GST_ABI "x86")
    set(NEEDS_NOTEXT_FIX TRUE)
elseif("${ANDROID_ABI}" STREQUAL "x86_64")
    set(GST_ABI "x86_64")
else()
    set(GST_ABI ${ANDROID_ABI})
endif()

set(GSTREAMER_ROOT "${GSTREAMER_DEVEL_ANDROID}/${GST_ABI}")

include_directories(
        ${GSTREAMER_ROOT}/include/gstreamer-1.0
        ${GSTREAMER_ROOT}/include/glib-2.0
        ${GSTREAMER_ROOT}/lib/glib-2.0/include
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/include
        ${GSTREAMER_ROOT}/include
)

link_directories(
        ${GSTREAMER_ROOT}/lib
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0
)

SET(GSTREAMER_PLUGINS_CORE
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcoreelements.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcoretracers.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstadder.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstapp.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudioconvert.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiomixer.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiorate.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudioresample.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiotestsrc.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcompositor.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstgio.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstoverlaycomposition.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstpango.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrawparse.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttypefindfunctions.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideoconvertscale.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideorate.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideotestsrc.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvolume.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstautodetect.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideofilter.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstinsertbin.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstswitchbin.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstfallbackswitch.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstgopbuffer.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstlivesync.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstoriginalbuffer.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrsinter.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrstracers.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgststreamgrouper.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstthreadshare.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttogglerecord.a
)

SET(GSTREAMER_PLUGINS_PLAYBACK
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstplayback.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsturiplaylistbin.a
)

set(GSTREAMER_PLUGINS_NET_RESTRICTED
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtmp2.a
)

set(GSTREAMER_PLUGINS_ENCODING
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstencoding.a
)

SET(GSTREAMER_PLUGINS_NET
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttcp.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtsp.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtp.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtpmanager.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsoup.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstudp.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdtls.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstnetsim.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrist.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtmp2.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtpmanagerbad.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtponvif.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsctp.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsdpelem.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsrtp.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsrt.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstwebrtc.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstnice.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrtspclientsink.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaws.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsthlssink3.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsthlsmultivariantsink.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmpegtslive.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstndi.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstquinn.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrsonvif.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstraptorq.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrsrelationmeta.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstreqwest.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrsrtp.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrsrtsp.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrebrtchttp.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrswebrtc.a
)

SET(GSTREAMER_PLUGINS_SYS
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopengl.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstipcpipeline.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttinyalsa.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopensles.a
)

SET(GSTREAMER_PLUGINS_CODECS
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsubparse.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstogg.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttheora.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvorbis.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopus.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstadaptivedemux2.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstalaw.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstamrnb.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstamrwbdec.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstapetag.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudioparsers.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstauparse.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstavi.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdv.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstflac.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstflv.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstflxdec.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsticydemux.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstid3demux.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstisomp4.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstjpeg.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstlame.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmatroska.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmpg123.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmulaw.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmultipart.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstpng.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstspeex.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttaglib.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvpx.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstwavenc.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstwavpack.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstwavparse.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstxingmux.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsty4menc.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstadpcmdec.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstadpcmenc.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstassrender.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstbz2.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcodecalpha.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcodectimestamper.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdash.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdvbsubenc.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdvbsuboverlay.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdvdspu.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsthls.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstid3tag.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstivfparse.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmidi.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmxf.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopenh264.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopusparse.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstpcapparse.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstpnm.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrfbsrc.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsiren.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsmoothstreaming.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsubenc.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttranscode.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideoparsersbad.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsty4mdec.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstjpegformat.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstgdp.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstopenjpeg.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstspandsp.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsbc.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstzbar.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrsvg.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsvtav1.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstx265.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstandroidmedia.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcdg.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstclaxon.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdav1d.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrsclosedcaption.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstffv1.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstfmp4.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmp4.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstgif.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsthsv.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstlewton.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrav1e.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstjson.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrspng.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstregex.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttextwrap.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttextahead.a
)

SET(GSTREAMER_PLUGINS_EFFECTS
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstalpha.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstalphacolor.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiofx.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcairo.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcutter.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdebug.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdeinterlace.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdtmf.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsteffectv.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstequalizer.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstgdkpixbuf.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstimagefreeze.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstinterleave.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstlevel.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmultifile.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstreplaygain.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstshapewipe.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsmpte.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstspectrum.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideobox.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideocrop.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideomixer.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaccurip.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaes.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaiff.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiobuffersplit.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiofxbad.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiolatency.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiomixmatrix.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstautoconvert.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstbayer.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcoloreffects.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstclosedcaption.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdebugutilsbad.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstfieldanalysis.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstfreeverb.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstgaudieffects.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstgeometrictransform.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstinter.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstinterlace.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstivtc.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstlegacyrawparse.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstproxy.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstremovesilence.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsegmentclip.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsmooth.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstspeed.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstsoundtouch.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsttimecode.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideofiltersbad.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideoframe_audiolevel.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvideosignal.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstwebrtcdsp.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstladspa.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrsaudiofx.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrsvideofx.a
)

SET(GSTREAMER_PLUGINS_VIS
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstgoom.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstgoom2k1.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstaudiovisualizers.a
)

SET(GSTREAMER_PLUGINS_CAPTURE
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcamerabin.a
)

SET(GSTREAMER_PLUGINS_CODECS_RESTRICTED
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstasfmux.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdtsdec.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmpegpsdemux.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmpegpsmux.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmpegtsdemux.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstmpegtsmux.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvoaacenc.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgsta52dec.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstasf.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdvdsub.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstdvdlpcmdec.a
        #${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstrealmedia.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstx264.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstlibav.a
)

SET(GSTREAMER_PLUGINS_NET_RESTRICTED
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstcamerabin.a
)

SET(GSTREAMER_PLUGINS_VULKAN
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstvulkan.la
)

SET(GSTREAMER_PLUGINS_GES
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstnle.a
        ${GSTREAMER_ROOT}/lib/gstreamer-1.0/libgstges.a
)

SET(GST_DEPENDENCIES
    ${GSTREAMER_ROOT}/lib/libFLAC.a
    ${GSTREAMER_ROOT}/lib/libSoundTouch.a
    ${GSTREAMER_ROOT}/lib/libSvtAv1Enc.a
    ${GSTREAMER_ROOT}/lib/liba52.a
    ${GSTREAMER_ROOT}/lib/libass.a
    ${GSTREAMER_ROOT}/lib/libavcodec.a
    ${GSTREAMER_ROOT}/lib/libavfilter.a
    ${GSTREAMER_ROOT}/lib/libavformat.a
    ${GSTREAMER_ROOT}/lib/libavutil.a
    ${GSTREAMER_ROOT}/lib/libbz2.a
    ${GSTREAMER_ROOT}/lib/libcairo-gobject.a
    ${GSTREAMER_ROOT}/lib/libcairo-script-interpreter.a
    ${GSTREAMER_ROOT}/lib/libcairo.a
    ${GSTREAMER_ROOT}/lib/libcharset.a
    ${GSTREAMER_ROOT}/lib/libcrypto.a
    ${GSTREAMER_ROOT}/lib/libdav1d.a
    ${GSTREAMER_ROOT}/lib/libdca.a
    ${GSTREAMER_ROOT}/lib/libdv.a
    ${GSTREAMER_ROOT}/lib/libexpat.a
    ${GSTREAMER_ROOT}/lib/libffi.a
    ${GSTREAMER_ROOT}/lib/libfontconfig.a
    ${GSTREAMER_ROOT}/lib/libfreetype.a
    ${GSTREAMER_ROOT}/lib/libfribidi.a
    ${GSTREAMER_ROOT}/lib/libgdk_pixbuf-2.0.a
    ${GSTREAMER_ROOT}/lib/libges-1.0.a
    ${GSTREAMER_ROOT}/lib/libgio-2.0.a
    ${GSTREAMER_ROOT}/lib/libglib-2.0.a
    ${GSTREAMER_ROOT}/lib/libgmodule-2.0.a
    ${GSTREAMER_ROOT}/lib/libgobject-2.0.a
    ${GSTREAMER_ROOT}/lib/libgraphene-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstadaptivedemux-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstallocators-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstanalytics-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstapp-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstaudio-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstbadaudio-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstbase-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstbasecamerabinsrc-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstcheck-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstcodecparsers-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstcodecs-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstcontroller-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstfft-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstgl-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstinsertbin-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstisoff-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstmpegts-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstmse-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstnet-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstpbutils-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstphotography-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstplay-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstplayer-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstreamer-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstriff-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstrtp-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstrtsp-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstrtspserver-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstsctp-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstsdp-1.0.a
    ${GSTREAMER_ROOT}/lib/libgsttag-1.0.a
    ${GSTREAMER_ROOT}/lib/libgsttranscoder-1.0.a
    ${GSTREAMER_ROOT}/lib/libgsturidownloader-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstvalidate-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstvideo-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstvulkan-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstwebrtc-1.0.a
    ${GSTREAMER_ROOT}/lib/libgstwebrtcnice-1.0.a
    ${GSTREAMER_ROOT}/lib/libgthread-2.0.a
    ${GSTREAMER_ROOT}/lib/libharfbuzz-gobject.a
    ${GSTREAMER_ROOT}/lib/libharfbuzz.a
    ${GSTREAMER_ROOT}/lib/libiconv.a
    ${GSTREAMER_ROOT}/lib/libintl.a
    ${GSTREAMER_ROOT}/lib/libjpeg.a
    ${GSTREAMER_ROOT}/lib/libjson-glib-1.0.a
    ${GSTREAMER_ROOT}/lib/libltc.a
    ${GSTREAMER_ROOT}/lib/libmp3lame.a
    ${GSTREAMER_ROOT}/lib/libmpg123.a
    ${GSTREAMER_ROOT}/lib/libnghttp2.a
    ${GSTREAMER_ROOT}/lib/libnice.a
    ${GSTREAMER_ROOT}/lib/libogg.a
    ${GSTREAMER_ROOT}/lib/libopencore-amrnb.a
    ${GSTREAMER_ROOT}/lib/libopencore-amrwb.a
    ${GSTREAMER_ROOT}/lib/libopenh264.a
    ${GSTREAMER_ROOT}/lib/libopenjp2.a
    ${GSTREAMER_ROOT}/lib/libopus.a
    ${GSTREAMER_ROOT}/lib/liborc-0.4.a
    ${GSTREAMER_ROOT}/lib/liborc-test-0.4.a
    ${GSTREAMER_ROOT}/lib/libpango-1.0.a
    ${GSTREAMER_ROOT}/lib/libpangocairo-1.0.a
    ${GSTREAMER_ROOT}/lib/libpangoft2-1.0.a
    ${GSTREAMER_ROOT}/lib/libpcre2-8.a
    ${GSTREAMER_ROOT}/lib/libpixman-1.a
    ${GSTREAMER_ROOT}/lib/libpng16.a
    ${GSTREAMER_ROOT}/lib/libpsl.a
    ${GSTREAMER_ROOT}/lib/libqrencode.a
    ${GSTREAMER_ROOT}/lib/librsvg-2.a
    ${GSTREAMER_ROOT}/lib/librtmp.a
    ${GSTREAMER_ROOT}/lib/libsbc.a
    ${GSTREAMER_ROOT}/lib/libsoup-3.0.a
    ${GSTREAMER_ROOT}/lib/libspandsp.a
    ${GSTREAMER_ROOT}/lib/libspeex.a
    ${GSTREAMER_ROOT}/lib/libsqlite3.a
    ${GSTREAMER_ROOT}/lib/libsrt.a
    ${GSTREAMER_ROOT}/lib/libsrtp2.a
    ${GSTREAMER_ROOT}/lib/libssl.a
    ${GSTREAMER_ROOT}/lib/libswresample.a
    ${GSTREAMER_ROOT}/lib/libswscale.a
    ${GSTREAMER_ROOT}/lib/libtag.a
    ${GSTREAMER_ROOT}/lib/libtheora.a
    ${GSTREAMER_ROOT}/lib/libtheoradec.a
    ${GSTREAMER_ROOT}/lib/libtheoraenc.a
    ${GSTREAMER_ROOT}/lib/libtiff.a
    ${GSTREAMER_ROOT}/lib/libtinyalsa.a
    ${GSTREAMER_ROOT}/lib/libturbojpeg.a
    ${GSTREAMER_ROOT}/lib/libvo-aacenc.a
    ${GSTREAMER_ROOT}/lib/libvorbis.a
    ${GSTREAMER_ROOT}/lib/libvorbisenc.a
    ${GSTREAMER_ROOT}/lib/libvorbisfile.a
    ${GSTREAMER_ROOT}/lib/libvpx.a
    ${GSTREAMER_ROOT}/lib/libwavpack.a
    ${GSTREAMER_ROOT}/lib/libwebrtc-audio-processing-2.a
    ${GSTREAMER_ROOT}/lib/libx264.a
    ${GSTREAMER_ROOT}/lib/libx265.a
    ${GSTREAMER_ROOT}/lib/libxml2.a
    ${GSTREAMER_ROOT}/lib/libz.a
    ${GSTREAMER_ROOT}/lib/libzbar.a
)

include_directories(${OpenCV_DIR}/jni/include)
add_library( lib_opencv SHARED IMPORTED )
set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION ${OpenCV_DIR}/libs/${ANDROID_ABI}/libopencv_java4.so)

add_library(gstreamer_android SHARED gstreamer_android.c)
target_link_libraries(gstreamer_android log android GLESv2 EGL OpenSLES vulkan
        ${GSTREAMER_PLUGINS_CORE} ${GSTREAMER_PLUGINS_EFFECTS} ${GSTREAMER_PLUGINS_CODECS_RESTRICTED}
        ${GSTREAMER_PLUGINS_CODECS} ${GSTREAMER_PLUGINS_SYS} ${GSTREAMER_PLUGINS_NET}
        ${GSTREAMER_PLUGINS_PLAYBACK} ${GSTREAMER_PLUGINS_ENCODING} ${GST_DEPENDENCIES}
)
target_link_options(
        gstreamer_android
        PRIVATE
        "-Wl,-Bsymbolic"
)
if(DEFINED NEEDS_NOTEXT_FIX)
    target_link_options(
            gstreamer_android
            PRIVATE
            "-Wl,-z,notext"
    )
endif()

add_library(${CMAKE_PROJECT_NAME} SHARED native-lib.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} log android gstreamer_android lib_opencv)