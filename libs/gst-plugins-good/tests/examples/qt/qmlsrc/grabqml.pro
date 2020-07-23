TEMPLATE = app

QT += qml quick widgets

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig debug
PKGCONFIG = \
    gstreamer-1.0 \
    gstreamer-video-1.0
INCLUDEPATH += D:/Library/gstreamer/1.0/x86_64/include \
    D:/Library/gstreamer/1.0/x86_64/include/gstreamer-1.0/ \
    D:/Library/gstreamer/1.0/x86_64/include/glib-2.0 \
    D:/Library/gstreamer/1.0/x86_64/include/glib-2.0/glib \
    D:/Library/gstreamer/1.0/x86_64/lib/glib-2.0/include

GST_ROOT = D:/Library/gstreamer/1.0/x86_64/
#LIBS += -LD:/Library/gstreamer/1.0/x86_64/lib
LIBS        += -L$$GST_ROOT/lib -lgstreamer-1.0 -lgstgl-1.0 -lgstvideo-1.0 -lgstbase-1.0
LIBS        += -lglib-2.0 -lintl -lgobject-2.0
#INCLUDEPATH +=

DEFINES += GST_USE_UNSTABLE_API

INCLUDEPATH += ../lib

SOURCES += main.cpp

RESOURCES += qmlsrc.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
