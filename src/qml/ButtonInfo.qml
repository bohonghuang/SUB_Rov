import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id: info_updown_btn
    width: 40
    height: 40
    color: "#6179e3"
    radius: 20
    border.width: 0
    opacity: 0.5

    property alias btn_animation_toDown: animation_toDown.running
    property alias btn_animation_toUp: animation_toUp.running

    Image {
        id: imginfo
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectFit
        source: "../../resource/icon/arrow_up.png"
    }
    RotationAnimation{
        id: animation_toUp
        target: info_updown_btn
        to: 0
        duration: 200
    }

    RotationAnimation{
        id: animation_toDown
        target: info_updown_btn
        to: -180
        duration: 200
    }

    PropertyAnimation{
        id: updown_animation_enter
        target: info_updown_btn
        property: "opacity"
        to: 1
        duration: 100
    }

    PropertyAnimation{
        id: updown_animation_exit
        target: info_updown_btn
        property: "opacity"
        to: 0.5
        duration: 100
    }


    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            updown_animation_enter.running = true;
        }
        onExited: {
            updown_animation_exit.running = true;
        }
    }
    function changeDireciton(){

    }


}

