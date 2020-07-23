TEMPLATE = app

QT += qml quick widgets

#QT_CONFIG -= no-pkg-config
#CONFIG += link_pkgconfig debug
#PKGCONFIG = \
#    gstreamer-1.0 \
#    gstreamer-video-1.0

win32 {
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
#INCLUDEPATH +=

DEFINES += GST_USE_UNSTABLE_API

INCLUDEPATH += ../lib

SOURCES += main.cpp

RESOURCES += qmlsink.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
