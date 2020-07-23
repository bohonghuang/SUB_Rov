################################################################################
#
# (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
#
# QGroundControl is licensed according to the terms in the file
# COPYING.md in the root of the source code directory.
#
################################################################################

#
#-- Depends on gstreamer, which can be found at: http://gstreamer.freedesktop.org/download/
#

WindowsBuild {
    #- gstreamer installed by default under c:/gstreamer
    GST_ROOT = C:/gstreamer/1.0/x86_64
    message("in WindowsBuild")
    exists($$GST_ROOT) {
        message("in GST_ROOT")
        CONFIG      += VideoEnabled

        LIBS        += -L$$GST_ROOT/lib -lgstreamer-1.0 -lgstgl-1.0 -lgstvideo-1.0 -lgstbase-1.0
        LIBS        += -lglib-2.0 -lintl -lgobject-2.0

        INCLUDEPATH += \
            $$GST_ROOT/include \
            $$GST_ROOT/include/gstreamer-1.0 \
            $$GST_ROOT/include/glib-2.0 \
            $$GST_ROOT/lib/gstreamer-1.0/include \
            $$GST_ROOT/lib/glib-2.0/include

        DESTDIR_WIN = $$replace(DESTDIR, "/", "\\")
        GST_ROOT_WIN = $$replace(GST_ROOT, "/", "\\")

        # Copy main GStreamer runtime files
        QMAKE_POST_LINK += $$escape_expand(\\n) xcopy \"$$GST_ROOT_WIN\\bin\*.dll\" \"$$DESTDIR_WIN\" /S/Y $$escape_expand(\\n)
        QMAKE_POST_LINK += xcopy \"$$GST_ROOT_WIN\\bin\*.\" \"$$DESTDIR_WIN\" /S/Y $$escape_expand(\\n)

        # Copy GStreamer plugins
        QMAKE_POST_LINK += $$escape_expand(\\n) xcopy \"$$GST_ROOT_WIN\\lib\\gstreamer-1.0\\*.dll\" \"$$DESTDIR_WIN\\gstreamer-plugins\\\" /Y $$escape_expand(\\n)
        QMAKE_POST_LINK += $$escape_expand(\\n) xcopy \"$$GST_ROOT_WIN\\lib\\gstreamer-1.0\\validate\\*.dll\" \"$$DESTDIR_WIN\\gstreamer-plugins\\validate\\\" /Y $$escape_expand(\\n)
    }
}

VideoEnabled {

    message("Including support for video streaming")

    DEFINES += \
        QGC_GST_STREAMING

    iOSBuild {
        OBJECTIVE_SOURCES += \
            $$PWD/iOS/gst_ios_init.m
        INCLUDEPATH += \
            $$PWD/iOS
    }

    SOURCES += \
        $$PWD/gstqgcvideosinkbin.c \
        $$PWD/gstqgc.c

    include($$PWD/../../qmlglsink.pri)
} else {
    LinuxBuild|MacBuild|iOSBuild|WindowsBuild|AndroidBuild {
        message("Skipping support for video streaming (GStreamer libraries not installed)")
        message("Installation instructions here: https://github.com/mavlink/qgroundcontrol/blob/master/src/VideoStreaming/README.md")
    } else {
        message("Skipping support for video streaming (Unsupported platform)")
    }
}
