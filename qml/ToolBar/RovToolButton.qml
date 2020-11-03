import QtQuick 2.0

Item {
    id: element
    width: 100
    height: 66
    signal click
    property alias btnImage: btn_img.source
    property alias btnText: btn_text.text

    Rectangle{
        id: back_rec
        anchors.fill: parent
        color: "gray"
        opacity: 0
    }

    Image {
        id: btn_img
        height: parent.height - 10
        width: height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 5
        source: "res/icon/setting.png"
    }

    Text {
        id: btn_text
        text: qsTr("text")
        color: "white"
        anchors.top: parent.top
        anchors.topMargin: 33
        anchors.horizontalCenter: parent.horizontalCenter

        opacity: 0
        font.pointSize: 13
    }

    MouseArea {
        id: mousearea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: "PointingHandCursor"
        onEntered: {
            mouse_enter.start();
        }
        onExited: {
            mouse_exit.start()
        }
        onClicked: {
            click()
        }
    }

    ParallelAnimation{
        id: mouse_enter

        onStarted: {

        }

        PropertyAnimation{
            target: back_rec
            property: "opacity"
            to: 0.5
            duration: 55
        }
        PropertyAnimation{
            target: btn_img
            property: "height"
            to: 33
            duration: 66
        }
        PropertyAnimation{
            target: btn_img
            property: "y"
            to: 6
            duration: 66
        }
        PropertyAnimation{
            target: btn_text
            property: "opacity"
            to: 1
            duration: 40
        }
        PropertyAnimation{
            target: btn_text
            property: "anchors.topMargin"
            to: 45
            duration: 66
        }
    }

    ParallelAnimation{
        id: mouse_exit

        onStopped: {
            back_rec.opacity = 0
            btn_img.height = element.height - 10
            btn_img.y = 0
            btn_text.opacity = 0
        }
        PropertyAnimation{
            target: back_rec
            property: "opacity"
            to: 0
            duration: 55
        }
        PropertyAnimation{
            target: btn_img
            property: "height"
            to: element.height - 10
            duration: 40
        }
        PropertyAnimation{
            target: btn_img
            property: "y"
            to: 0
            duration: 40
        }
        PropertyAnimation{
            target: btn_text
            property: "opacity"
            to: 0
            duration: 40
        }
        PropertyAnimation{
            target: btn_text
            property: "anchors.topMargin"
            to: 33
            duration: 40
        }
    }
}
