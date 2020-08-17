QT += \
    quick \
    network \
    quickwidgets \
    qml \
    gui-private

CONFIG += c++11 \
    qt \
    thread


INCLUDEPATH += d:/Library/opencv-3.4.10/include \
    d:/Library/opencv-3.4.10/include/opencv

CONFIG(debug, debug|release ){
#    message("Debug build" )
    LIBS += -Ld:/Library/opencv-3.4.10/x64/vc14/lib \
        -lopencv_world3410d
    CONFIG+= DebugBuild
} else : CONFIG(release, debug| release){
#    message("Release build" )
    LIBS += -Ld:/Library/opencv-3.4.10/x64/vc14/lib \
        -lopencv_world3410
    CONFIG += ReleaseBuild
}
DebugBuild{
    DESTDIR  = $${OUT_PWD}/debug
    CONFIG += DebugBuild
}
else{
    DESTDIR = $${OUT_PWD}/release
    CONFIG += ReleaseBuild
}

win32{
    CONFIG += WindowsBuild
}

iOSBuild{
    ICON = logo.ico
}
WindowsBuild{
    RC_ICONS = "./res/sys/favicon_1.ico"
}

!iOSBuild {
    OBJECTS_DIR  = $${OUT_PWD}/obj
    MOC_DIR      = $${OUT_PWD}/moc
    UI_DIR       = $${OUT_PWD}/ui
    RCC_DIR      = $${OUT_PWD}/rcc
}

WindowsBuild {
    QMAKE_CFLAGS -= -Zc:strictStrings
    QMAKE_CFLAGS_RELEASE -= -Zc:strictStrings
    QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO -= -Zc:strictStrings
    QMAKE_CXXFLAGS -= -Zc:strictStrings
    QMAKE_CXXFLAGS_RELEASE -= -Zc:strictStrings
    QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO -= -Zc:strictStrings
    QMAKE_CXXFLAGS_WARN_ON += /W3 \
        /wd4996 \   # silence warnings about deprecated strcpy and whatnot, these come from the shapefile code with is external
        /wd4005 \   # silence warnings about macro redefinition, these come from the shapefile code with is external
        /wd4290 \   # ignore exception specifications
        /wd4267     # silence conversion from 'size_t' to 'int', possible loss of data, these come from gps drivers shared with px4
    WarningsAsErrorsOn {
        QMAKE_CXXFLAGS_WARN_ON += /WX
    }
}
ReleaseBuild {
    DEFINES += QT_NO_DEBUG QT_MESSAGELOGCONTEXT
    CONFIG += force_debug_info  # Enable debugging symbols on release builds
    !iOSBuild {
        !AndroidBuild {
            CONFIG += ltcg              # Turn on link time code generation
        }
    }

    WindowsBuild {
        # Run compilation using VS compiler using multiple threads
        QMAKE_CXXFLAGS += -MP

        # Enable function level linking and enhanced optimized debugging
        QMAKE_CFLAGS_RELEASE   += /Gy /Zo
        QMAKE_CXXFLAGS_RELEASE += /Gy /Zo
        QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO   += /Gy /Zo
        QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO += /Gy /Zo

        # Eliminate duplicate COMDATs
        QMAKE_LFLAGS_RELEASE += /OPT:ICF
#        QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO += /OPT:ICF
    }
}

installer {
    CONFIG -= debug
    CONFIG -= debug_and_release
    CONFIG += release
    message(Build Installer)
}


INCLUDEPATH += src \
    src/VideoStreaming \
    src/Socket \
    src/Keyboard \
    src/Log \
    src/Settings


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
        src/RovApplication.cpp \
        src/RovControlCore.cpp \
        src/RovToolbox.cpp \
        src/Keyboard/KeyManager.cpp \
        src/Log/MyLogging.cpp \
        src/Settings/SettingsManager.cpp \
        src/Socket/ReceiveManager.cpp \
        src/Socket/SendManager.cpp \
        src/Socket/SocketManager.cpp \
        src/Socket/SocketThread.cpp \
        src/VideoStreaming/ImageProvider.cpp \
        src/VideoStreaming/ImageProvider2.cpp \
        src/VideoStreaming/VideoManager.cpp

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
    src/RovApplication.h \
    src/RovControlCore.h \
    src/RovToolbox.h \
    src/Log/MyLogging.h \
    src/Keyboard/KeyManager.h \
    src/Settings/SettingsManager.h \
    src/Socket/ReceiveManager.h \
    src/Socket/SendManager.h \
    src/Socket/SocketManager.h \
    src/Socket/SocketThread.h \
    src/VideoStreaming/ImageProvider.h \
    src/VideoStreaming/ImageProvider2.h \
    src/VideoStreaming/VideoManager.h
