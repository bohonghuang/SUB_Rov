﻿import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4

Item {
    id: element
    width: 160
    height: 600
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



    property bool isDeepLock: false
    property bool isDirectionLock: false


    onPointAngleChanged: {
        point_animation.running = true;
    }

    Rectangle {
        id: rectangle
        color: "#434343"
        width: parent.width
        height: 600
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
        anchors.right: parent.right
        anchors.rightMargin: 9
        anchors.left: parent.left
        anchors.leftMargin: 9
        anchors.top: parent.top
        anchors.topMargin: 20
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


    Flow {
        id: flag_flow
        x: 8
        width: 141
        height: 154
        anchors.top: grid.bottom
        anchors.topMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10


        MyFlag{
            id: flag_deep
            x: 8
            y: 365
            img_source: "../../resource/icon/flag/白字_深.png"
        }

        MyFlag {
            id: flag_zoom
            x: 8
            y: 417
            img_source: "../../resource/icon/flag/白字_变.png"
        }

        MyFlag {
            id: flag_focus
            x: 60
            y: 417
            img_source: "../../resource/icon/flag/白字_聚.png"
        }

        MyFlag {
            id: flag_power
            x: 112
            y: 417
            img_source: "../../resource/icon/flag/白字_电.png"
        }

        MyFlag {
            id: flag_cloud
            x: 8
            y: 472
            img_source: "../../resource/icon/flag/白字_云.png"
        }

        MyFlag {
            id: flag_point
            x: 60
            y: 365
            img_source: "../../resource/icon/flag/白字_指.png"
        }

        MyFlag {
            id: flag_machine
            x: 112
            y: 365
            img_source: "../../resource/icon/flag/白字_机.png"
        }

        MyFlag {
            id: flag_com
            x: 60
            y: 472
            img_source: "../../resource/icon/flag/白字_串.png"
        }

        MyFlag {
            id: flag_p
            x: 112
            y: 472
            img_source: "../../resource/icon/flag/白字_P.png"
        }


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

    Switch {

        id: switch_deep
        height: 40
        text: qsTr("深度锁定")
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: flag_flow.bottom
        anchors.topMargin: 0
        font.weight: Font.Light
        font.bold: false
        font.family: "Courier"
        font.pointSize: 13
        checked: sendManager.isDeepLock()
        background: Rectangle{
            anchors.fill: parent
            color: "gray"
            radius: 50
        }

        onCheckedChanged: {
            if(checked === true){
                rovControl.doLockDeep();
            }
            else{
                rovControl.doUnlockDeep();
            }
        }

    }
    Switch {
        id: switch_direction
        height: 40
        text: qsTr("方向锁定")
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: switch_deep.bottom
        anchors.topMargin: 5
        font.pointSize: 13
        font.bold: false
        font.weight: Font.Light
        checked: sendManager.isDirectLock()
        font.family: "Courier"
        background: Rectangle {
            color: "#808080"
            radius: 50
            anchors.fill: parent
        }


        onCheckedChanged: {
            if(checked === true){
                rovControl.doLockDirection();
            }
            else{
                rovControl.doUnlockDirection();
            }
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



    Connections {
        target: receiveManager
        onRecvCommandChanged: {
            info_refresh();
            flag_refresh();
        }
    }
    Connections {
        target: sendManager
        onDeepChanged: {
            if(sendManager.isDeepLock()){
                switch_deep.checked = true;
            }
            else{
                switch_deep.checked = false;
            }
        }
        onDirectChanged: {
            if(sendManager.isDirectLock()){
                switch_direction.checked = true;
            }
            else{
                switch_direction.checked = false;
            }
        }
    }






    function info_refresh () {
        deepTxtText = "深度：" + socketManager.getDeepText();
        innerTemTxtText = "内温：" + socketManager.getTemperatureInsideText();
        waterTemTxtText = "外温：" + socketManager.getTemperatureOutsideText();
        toUpTxtText = "俯仰：" + socketManager.getPitchText();
        toLeftRightTxtText = qsTr("横滚：") + socketManager.getRollText();
        speedTxtText = "航速：" + socketManager.getSpeedText();
        elecATxtText = "电流：" + socketManager.getCurrentText();
        elecUTxtText = "电压：" + socketManager.getVoltageText();
        elecPTxtText = "功率：" + socketManager.getPowerText();

        pointAngle = socketManager.getAngle();

    }

    function flag_refresh(){
        flag_machine_refresh();
        flag_cloud_refresh();
        flag_zoom_refresh();
        flag_focus_refresh();
        flag_point_refresh();
        flag_power_refresh();
        flag_com_refresh();
        flag_deep_refresh();
        flag_p_refresh();
    }

    function flag_machine_refresh(){
        if(receiveManager.getRovDeviceStatus(1) === true)
            flag_machine.light_running = true;
        else
            flag_machine.dark_running = true;
    }

    function flag_cloud_refresh(){
        if(receiveManager.getRovDeviceStatus(2) === true)
            flag_cloud.light_running = true;
        else
            flag_cloud.dark_running = true;
    }

    function flag_zoom_refresh(){
        if(receiveManager.getRovDeviceStatus(3) === true)
            flag_zoom.light_running = true;
        else
            flag_zoom.dark_running = true;
    }

    function flag_focus_refresh(){
        if(receiveManager.getRovDeviceStatus(4) === true)
            flag_focus.light_running = true;
        else
            flag_focus.dark_running = true;
    }

    function flag_point_refresh(){
        if(receiveManager.getRovDeviceStatus(5) === true)
            flag_point.light_running = true;
        else
            flag_point.dark_running = true;
    }

    function flag_power_refresh(){
        if(receiveManager.getRovDeviceStatus(6) === true)
            flag_power.light_running = true;
        else
            flag_power.dark_running = true;
    }

    function flag_com_refresh(){
        if(receiveManager.getRovDeviceStatus(7) === true)
            flag_com.light_running = true;
        else
            flag_com.dark_running = true;
    }

    function flag_deep_refresh(){
        if(receiveManager.getRovDeviceStatus(8) === true)
            flag_deep.light_running = true;
        else
            flag_deep.dark_running = true;
    }

    function flag_p_refresh(){
        if(receiveManager.getRovStatus() === true)
            flag_p.light_running = true;
        else
            flag_p.dark_running = true;
    }
}



/*##^##
Designer {
    D{i:15;anchors_x:8;anchors_y:363}D{i:33;anchors_width:144;anchors_x:8;anchors_y:511}
D{i:41;anchors_width:144;anchors_x:11;anchors_y:510}
}
##^##*/
