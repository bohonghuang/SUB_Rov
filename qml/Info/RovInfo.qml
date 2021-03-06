import QtQuick 2.0
import QtQuick.Controls 2.5


Item {
    id: infoElement
    width: 160
    height: 700

    signal opening
    signal closing

    onOpening: {
        info_open.start()
    }
    onClosing: {
        info_close.start()
    }



    Rectangle{
        width: 100
        height: 100
        color: "#00000000"
        anchors.right: info_body.left
        anchors.rightMargin: 20
        anchors.top: info_body.top
        anchors.topMargin: 10
        Image {
            id: pointBackground
            source: "qrc:/res/icon/the_back.png"
            anchors.fill: parent
        }
        Image{
            id: pointer
            source: "qrc:/res/icon/the_point.png"
            width: 70
            height: 70
            anchors.horizontalCenterOffset: 1
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit

            Behavior on rotation { RotationAnimation{ duration: 150 }}
        }
    }
    Rectangle {
        id: info_body
        width: parent.width
        height: parent.height
        radius: 10
        opacity: 0.838
        border.color: "#bcd2ee"
        border.width: 0
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
        MouseArea {
            id: info_area
            anchors.fill: parent
            hoverEnabled: true
            drag.target: parent.parent
            drag.minimumX: 0
            drag.minimumY: 66
            drag.maximumX: parent.parent.parent.width  - parent.parent.width
            drag.maximumY: parent.parent.parent.height - parent.parent.height
        }
    }

    Column{
        spacing: 20
        anchors.top: info_body.top
        anchors.topMargin: 10
        anchors.left: info_body.left
        anchors.leftMargin: 6
        Column {
            spacing: 9
            Repeater{
                id: info_text_repeat
                model: 10
                Text {
                    color: "white"
                    text: rovControl.getInfoText(index)
                    font.pointSize: 14
                }
            }
        }

        Grid {
            rows: 3
            columns: 3
            spacing: 9
            anchors.left: parent.left
            anchors.leftMargin: 3


            Repeater {
                id: info_flag_repeat
                model: 9
                RovFlag {
                    imgSource: rovControl.getFlagPath(index)

                }
            }
        }
        Connections {
            target: socketManager
            function onReceiveChanged(){
                for( var i=0; i<10 ;i++){
                    info_text_repeat.itemAt(i).text = rovControl.getInfoText(i);
                    if(i<9){
                        if( rovControl.getFlagShow(i) ){
                            info_flag_repeat.itemAt(i).lighting()
                        }
                        else{
                            info_flag_repeat.itemAt(i).darking()
                        }
                    }
                }
                pointer.rotation = rovControl.getPointerAngle()
            }
        }
        BodyDir{
            id: body_dir_body

            isUp: false
            z: 100
        }
//        Column {
//            Rectangle {
//                Image {
//                    id: rov_up
//                    x: 33
//                    y: 0
//                    source: "/res/icon/rov/up_light.png" //rovControl.getRovDirPath(index)
//                }
//                Image {
//                    id: rov_body_1
//                    x: 27
//                    y: 12
//                    source: ":/res/icon/rov/body1.png"
//                }
//            }
//        }

        Column {
            spacing: 5
            Switch {
                id: switch_deep
                text: qsTr("深度锁定")
                font.pointSize: 13
                background: Rectangle{
                    color: "#808080"
                    radius: 50
                    anchors.fill: parent
                }
                checked: socketManager.isDeepLocked()
                onCheckedChanged: {
                    if( checked === true)
                        rovControl.lockDeep()
                    else
                        rovControl.unlockDeep()
                }

            }
            Switch {
                id: switch_direction
                text: qsTr("方向锁定")
                font.pointSize: 13
                background: Rectangle{
                    color: "#808080"
                    radius: 50
                    anchors.fill: parent
                }
                checked: socketManager.isDirectionLocked()
                onCheckedChanged: {
                    if( checked === true)
                        rovControl.lockDirection()
                    else
                        rovControl.unlockDirection()
                }

            }
        }
    }



    ParallelAnimation{
        id: info_close
        PropertyAnimation {
            target: infoElement
            properties: "width, height, opacity"
            to: 0
            duration: 200
        }

    }

    ParallelAnimation{
        id: info_open
        onStarted: {
            y = 66
        }

        PropertyAnimation {
            target: infoElement
            properties: "width"
            to: 160
            duration: 200
        }
        PropertyAnimation {
            target: infoElement
            properties: "height"
            to: 700
            duration: 200
        }
        PropertyAnimation {
            target: infoElement
            properties: "opacity"
            to: 1
            duration: 200
        }
    }
}
