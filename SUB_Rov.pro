QT += \
    gui \
    network \
    qml \
    quick \
    quickwidgets\
    network\
    core\
    gui-private


CONFIG += qt \
    thread \
    c++11




win32 {
    contains(QMAKE_TARGET.arch, x86_64) {
        message("Windows build")
        CONFIG += WindowsBuild
        CONFIG += WarningsAsErrorsOn
    } else {
        error("Unsupported Windows toolchain, only Visual Studio 2017 64 bit is supported")
    }
}

BASEDIR      = $$IN_PWD
LANGUAGE = C++

TEMPLATE = app
ROVRoot = $$PWD

iOSBuild{
    ICON = logo.ico
}
WindowsBuild{
    RC_ICONS = "./resource/sys/favicon_1.ico"
}
DebugBuild{
    DESTDIR  = $${OUT_PWD}/debug
    CONFIG += DebugBuild
}
else{
    DESTDIR = $${OUT_PWD}/release
    CONFIG += ReleaseBuild
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


AndroidBuild || iOSBuild {
    # Android and iOS don't unclude these
} else {
    QT += \
        printsupport \
        serialport \
}

include(src/videostreaming/VideoStreaming.pri);


DEFINES += QT_DEPRECATED_WARNINGS
#INCLUDEPATH += D:/Library/boost_1_73_0


INCLUDEPATH += \
    src \
    src/videostreaming \
    src/keyboard \
    src/joystick \
    src/robot \
    src/setting \
    src/socket

SOURCES += \
        main.cpp \
        src/RovControlCore.cpp \
        src/RovApplication.cpp \
        src/RovToolBox.cpp \
        src/keyboard/KeyManager.cpp \
        src/robot/Oilvalve.cpp \
        src/setting/SettingManager.cpp \
        src/socket/ReceiveCommand.cpp \
        src/socket/ReceiveManager.cpp \
        src/socket/SendManager.cpp \
        src/socket/Sendcommand.cpp \
        src/socket/SocketManager.cpp \
        src/socket/ReceiveCommand.cpp \
        src/socket/receivecommand.cpp \
        src/videostreaming/GLVideoItemStub.cc \
        src/videostreaming/VideoManager.cpp \
        src/videostreaming/VideoReceiver.cpp \
        src/videostreaming/VideoStreaming.cpp

RESOURCES += qml.qrc \
    img.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/modules

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/RovControlCore.h \
    src/RovApplication.h \
    src/RovToolBox.h \
    src/keyboard/KeyManager.h \
    src/robot/Oilvalve.h \
    src/setting/SettingManager.h \
    src/socket/ReceiveCommand.h \
    src/socket/ReceiveManager.h \
    src/socket/SendCommand.h \
    src/socket/SendManager.h \
    src/socket/SocketManager.h \
    src/videostreaming/GLVideoItemStub.h \
    src/videostreaming/VideoManager.h \
    src/videostreaming/VideoReceiver.h \
    src/videostreaming/VideoStreaming.h

#FORMS += \
#    SettingWidget.ui


FORMS +=



