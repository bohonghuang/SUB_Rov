QT += quick \
    widgets
    network

CONFIG += c++11

INCLUDEPATH += d:/Library/opencv-3.4.10/include\
    d:/Library/opencv-3.4.10/include/opencv

LIBS += -Ld:/Library/opencv-3.4.10/x64/vc14/lib \
    -lopencv_world3410d -lopencv_world3410


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/Keyboard/KeyManager.cpp \
        src/Log/MyLogging.cpp \
        src/Robot/Oilvalve.cpp \
        src/RovApplication.cpp \
        src/RovControlCore.cpp \
        src/RovToolbox.cpp \
        src/Settings/SettingsManager.cpp \
        src/Socket/ReceiveManager.cpp \
        src/Socket/SendManager.cpp \
        src/Socket/SocketManager.cpp \
        src/Socket/SocketThread.cpp \
        src/VideoStreaming/ImageProvider.cpp \
        src/VideoStreaming/VideoManager.cpp \
        src/VideoStreaming/VideoReceiver.cpp

RESOURCES += qml.qrc \
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/Keyboard/KeyManager.h \
    src/Log/MyLogging.h \
    src/Robot/Oilvalve.h \
    src/RovApplication.h \
    src/RovControlCore.h \
    src/RovController.h \
    src/RovToolbox.h \
    src/Settings/SettingsManager.h \
    src/Socket/ReceiveManager.h \
    src/Socket/SendManager.h \
    src/Socket/SocketManager.h \
    src/Socket/SocketThread.h \
    src/VideoStreaming/ImageProvider.h \
    src/VideoStreaming/VideoManager.h \
    src/VideoStreaming/VideoReceiver.h
