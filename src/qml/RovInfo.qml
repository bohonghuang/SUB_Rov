import QtQuick 2.0

Item {
    id: element
    width: 160
    height: 520
    property alias deepTxtText: deepTxt.text
    property alias innerTemTxtText: innerTemTxt.text
    property alias waterTemTxtText: waterTemTxt.text
    property alias toUpTxtText: toUpTxt.text
    property alias toLeftRightTxtText: toLeftRightTxt.text
    property alias speedTxtText: speedTxt.text
    property alias elecUTxtText: elecUTxt.text
    property alias elecATxtText: elecATxt.text
    property alias elecPTxtText: elecPTxt.text
    property alias rectangleWidth: rectangle.width

    property alias rovinfo_animation_show: animation_show.running
    property alias rovinfo_animation_hidden: animation_hidden.running

    property alias pointAngle: point_animation.to

    onPointAngleChanged: {
        point_animation.running = true;
    }

    Rectangle {
        id: rectangle
        height: parent.height
        color: "#434343"
        width: parent.width
        radius: 10
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#434343"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }
        opacity: 0.838

        border.color: "#bcd2ee"
        border.width: 0


    }



    Grid {
        id: grid
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 163
        anchors.right: parent.right
        anchors.rightMargin: 9
        anchors.left: parent.left
        anchors.leftMargin: 9
        anchors.top: parent.top
        anchors.topMargin: 44
        spacing: 10
        rows: 10
        columns: 1

        Text {
            id: deepTxt
            color: "#ffffff"
            text: qsTr("深度：")
            font.bold: false
            font.family: "Tahoma"
            z: 5
            verticalAlignment: Text.AlignTop
            font.pixelSize: 20
        }

        Text {
            id: innerTemTxt
            color: "#ffffff"
            text: qsTr("内温：")
            font.bold: false
            font.family: "Tahoma"
            verticalAlignment: Text.AlignTop
            z: 5
            font.pixelSize: 20
        }

        Text {
            id: waterTemTxt
            color: "#ffffff"
            text: qsTr("外温:")
            font.bold: false
            font.family: "Tahoma"
            verticalAlignment: Text.AlignTop
            z: 5
            font.pixelSize: 20
        }

        Text {
            id: toUpTxt
            color: "#ffffff"
            text: qsTr("俯仰：")
            font.bold: false
            font.family: "Tahoma"
            verticalAlignment: Text.AlignTop
            z: 5
            font.pixelSize: 20
        }

        Text {
            id: toLeftRightTxt
            color: "#ffffff"
            text: qsTr("横滚：")
            font.bold: false
            font.family: "Tahoma"
            verticalAlignment: Text.AlignTop
            z: 5
            font.pixelSize: 20
        }

        Text {
            id: speedTxt
            color: "#ffffff"
            text: qsTr("航速：")
            font.bold: false
            font.family: "Tahoma"
            verticalAlignment: Text.AlignTop
            z: 5
            font.pixelSize: 20
        }

        Text {
            id: elecUTxt
            color: "#ffffff"
            text: qsTr("电压：")
            font.bold: false
            font.family: "Tahoma"
            verticalAlignment: Text.AlignTop
            z: 5
            font.pixelSize: 20
        }

        Text {
            id: elecATxt
            color: "#ffffff"
            text: qsTr("电流：")
            font.bold: false
            font.family: "Tahoma"
            verticalAlignment: Text.AlignTop
            z: 5
            font.pixelSize: 20
        }

        Text {
            id: elecPTxt
            color: "#ffffff"
            text: qsTr("功率：")
            font.bold: false
            font.family: "Tahoma"
            verticalAlignment: Text.AlignTop
            z: 5
            font.pixelSize: 20
        }


    }


    ParallelAnimation{
        id: animation_show

        onStarted: {
            element.visible = true;
        }

        PropertyAnimation{
            target: element
            property: "opacity"
            to: 1
            duration: 200
        }
        PropertyAnimation{
            target: element
            property: "height"
            to: 520
            duration: 200
        }
        PropertyAnimation{
            target: element
            property: "width"
            to: 160
            duration: 200
        }
        PropertyAnimation{
            target: element
            property: "x"
            to: root.width - 160 - 5
            duration: 200
        }
    }
    ParallelAnimation{
        id: animation_hidden
        onStopped: {
            element.visible = false;
            element.x = root.width - 6;
            element.y = 80;
        }

        PropertyAnimation{
            target: element
            properties: "opacity,height,width"
            to: 0
            duration: 200
        }
        PropertyAnimation{
            target: element
            property: "x"
            to: root.width - 6
            duration: 200
        }
        PropertyAnimation{
            target: element
            property: "y"
            to: 80
            duration: 200
        }
    }
    RotationAnimation{
        id: point_animation
        target: imgSouthPoint
        to: 0
        duration: 200
    }

    Rectangle {
        id: southRec
        x: -120
        y: 10
        width: 100
        height: 100
        color: "#00000000"


        Image {
            id: imgSouthBack
            anchors.fill: parent
            source: "../../resource/icon/the_back.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: imgSouthPoint
            width: 70
            height: 70
            anchors.horizontalCenterOffset: 1
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: "../../resource/icon/the_point.png"
            fillMode: Image.PreserveAspectFit
        }
    }
}


