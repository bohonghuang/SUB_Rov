QT += quick
QT += qml

CONFIG += c++11

win32{
INCLUDEPATH += D:/ImDeveloper/Environment/opencv-3.4.10/include \
    D:/ImDeveloper/Environment/opencv-3.4.10/include/opencv

CONFIG(debug, debug|release ){
#    message("Debug build" )
    LIBS += -LD:/ImDeveloper/Environment/opencv-3.4.10/x64/vc14/lib \
        -lopencv_world3410d
    CONFIG+= DebugBuild
} else : CONFIG(release, debug| release){
#    message("Release build" )
    LIBS += -LD:/ImDeveloper/Environment/opencv-3.4.10/x64/vc14/lib \
        -lopencv_world3410
    CONFIG += ReleaseBuild
}
}
unix {
    ANDROID_OPENCV = D:/ImDeveloper/Environment/OpenCV-android-sdk/sdk/native
    INCLUDEPATH += \
    $$ANDROID_OPENCV/jni/include/opencv2 \
    $$ANDROID_OPENCV/jni/include


    LIBS += \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_ml.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_objdetect.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_calib3d.a \
#    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_video.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_videoio.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_features2d.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_highgui.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_flann.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_imgproc.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_dnn.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_core.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_gapi.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_photo.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_imgcodecs.a \
    $$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_stitching.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libcpufeatures.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libittnotify.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libade.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libIlmImf.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibjpeg-turbo.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibpng.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibopenjp2.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibprotobuf.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibtiff.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibwebp.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libtbb.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libquirc.a \
    $$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libtegra_hal.a \
    $$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_java4.so


}
contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    message("armeabi-v7a")
    ANDROID_EXTRA_LIBS = \
    D:/ImDeveloper/Environment/OpenCV-android-sdk/sdk/native/libs/armeabi-v7a/libopencv_java4.so
}
#contains(ANDROID_TARGET_ARCH,arm64-v8a) {
#    message("arm64-v8a")
#    ANDROID_EXTRA_LIBS = \
#    D:/ImDeveloper/Environment/OpenCV-android-sdk/sdk/native/libs/arm64-v8a/libopencv_java4.so
#}
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        imageprovider.cpp \
        main.cpp \
        videomanager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    imageprovider.h \
    videomanager.h


android: include(F:/IDE/Android_SDK/android_openssl/openssl.pri)

ANDROID_ABIS = armeabi-v7a
