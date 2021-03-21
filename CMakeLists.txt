cmake_minimum_required(VERSION 3.8.2)

project(SUB_ROV LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "D:/MinGW/OpenCV" "D:/Qt/6.0.2/mingw81_64")


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets REQUIRED)
find_package(OpenCV REQUIRED)

set(SOURCES
        main.cpp
        src/Log/MyLogging.cpp
        src/RovApplication.cpp
        src/RovControlCore.cpp
        src/RovToolBox.cpp
        src/Settings/SettingsManager.cpp
        src/Settings/joysticksettings.cpp
        src/joystick/joysticker.cpp
        src/joystick/joystickmanager.cpp
        src/joystick/joythread.cpp
        src/keyboard/KeyManager.cpp
        src/robot/Oilvalve.cpp
        src/socket/ReceiveManager.cpp
        src/socket/SendManager.cpp
        src/socket/SocketManager.cpp
        src/socket/SocketThread.cpp
        src/videostreaming/ImageProvider.cpp
        src/videostreaming/ImageProvider2.cpp
        src/videostreaming/VideoManager.cpp
        src/videostreaming/VideoReceiver.cpp
        )

set(HEADERS
        src/Log/MyLogging.h
        src/RovApplication.h
        src/RovControlCore.h
        src/RovToolBox.h
        src/Settings/SettingsManager.h
        src/Settings/joysticksettings.h
        src/joystick/joysticker.h
        src/joystick/joystickmanager.h
        src/joystick/joythread.h
        src/keyboard/KeyManager.h
        src/robot/Oilvalve.h
        src/socket/ReceiveManager.h
        src/socket/SendManager.h
        src/socket/SocketManager.h
        src/socket/SocketThread.h
        src/user_proc/user_proc.h
        src/videostreaming/ImageProvider.h
        src/videostreaming/ImageProvider2.h
        src/videostreaming/VideoManager.h
        src/videostreaming/VideoReceiver.h
        )

include_directories(
        src/
        src/videostreaming
        src/socket
        src/keyboard
        src/Log
        src/Settings
        src/user_proc
        src/joystick
        src/robot
)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        res.qrc
        )

link_directories(libs_mingw/users/)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SUB_ROV
            ${PROJECT_SOURCES} ${SOURCES} ${HEADERS}
            )
else ()
    if (ANDROID)
        add_library(SUB_ROV SHARED
                ${PROJECT_SOURCES}
                )
    else ()
        add_executable(SUB_ROV
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()


target_compile_definitions(SUB_ROV
        PUBLIC $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(SUB_ROV
        PUBLIC Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(SUB_ROV PUBLIC ${OpenCV_LIBS})
