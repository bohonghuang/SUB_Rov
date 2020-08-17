import QtQuick 2.0

Item {
    width: 50
    height: 50

    signal open
    signal close

    Rectangle {
        id: background
        anchors.fill: parent
        radius: width/2
        color: "#7d92e6"
        opacity: 0.3
    }

    Image {
        id: infoSwitch_img
        source: "qrc:/res/icon/arrow_up.png"
        anchors.fill: parent
    }
    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            if( infoSwitch_img.rotation == 0){
                mouse_click_close.start()
                close()
            }
            else{
                mouse_click_open.start()
                open()
            }
        }
        onEntered: {
            mouse_enter.start()
        }
        onExited: {
            mouse_exit.start()
        }
    }

    ParallelAnimation{
        id: mouse_click_close
        RotationAnimation {
            target: infoSwitch_img
            to: 180
            duration: 200
        }
    }
    ParallelAnimation {
        id: mouse_click_open
        RotationAnimation{
            target: infoSwitch_img
            to: 0
            duration: 200
        }
    }
    ParallelAnimation{
        id: mouse_enter
        PropertyAnimation {
            target: background
            property: "opacity"
            to: 1
            duration: 120
        }
    }
    ParallelAnimation{
        id: mouse_exit
        PropertyAnimation {
            target: background
            property: "opacity"
            to: 0.3
            duration: 200
        }
    }
}
