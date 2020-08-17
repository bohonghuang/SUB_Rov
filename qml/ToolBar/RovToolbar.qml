import QtQuick 2.0

Item {
    width: 900
    height: 66

    signal about
    signal settings
    signal socket

    onSettings: {
        if(btn_settings.btnText === "设置"){
            btn_settings.btnImage = "qrc:/res/icon/main.png"
            btn_settings.btnText = "主页"
        }
        else{
            btn_settings.btnImage = "qrc:/res/icon/setting.png"
            btn_settings.btnText = "设置"
        }
    }

    Rectangle {
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#1d1d1d"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }
        anchors.fill: parent

    }

    Image {
        id: imgAbout
        fillMode: Image.PreserveAspectFit
        source: "qrc:/res/img/Logo.png"
        height: parent.height

        anchors.right: parent.right
        anchors.top: parent.top
        MouseArea{
            anchors.fill: parent
            cursorShape: "PointingHandCursor"
            onClicked: about()
        }
    }
    Connections {
        target: socketManager
        onEnableChanged: {
            btn_connect.btnImage = socketManager.isEnable() ? "qrc:/res/icon/close.png" : "qrc:/res/icon/connect.png";
            btn_connect.btnText = socketManager.isEnable() ? qsTr("断开连接") : qsTr("连接");
        }
    }
    Connections{
        target: videoManager

        onWriter1Changed: {
            btn_record.btnImage = videoManager.isRecording()? "qrc:/res/icon/video_off.png" : "qrc:/res/icon/video_on.png"
            btn_record.btnText = videoManager.isRecording()? qsTr("停止录制") : qsTr("录制")
        }

        onWriter2Changed: {
            btn_record.btnImage = videoManager.isRecording()? "qrc:/res/icon/video_off.png" : "qrc:/res/icon/video_on.png"
            btn_record.btnText = videoManager.isRecording()? qsTr("停止录制") : qsTr("录制")
        }
    }

    Row{
        spacing: 5
        RovToolButton {
            id: btn_settings
            btnImage: "qrc:/res/icon/setting.png"
            btnText: qsTr("设置")
            onClick: { settings()}
        }
        RovToolButton {
            id: btn_connect
            btnImage: "qrc:/res/icon/connect.png"
            btnText: qsTr("连接")
            onClick: {
                if(socketManager.isEnable())
                    socketManager.disconnectServer()
                else
                    socketManager.connectServer()
            }
        }
        RovToolButton {
            btnImage: "qrc:/res/icon/round.png"
            btnText: qsTr("视频流重置")
            onClick: { videoManager.restartVideo()}
        }
        RovToolButton {
            id: btn_record
            btnImage: "qrc:/res/icon/video_on.png"
            btnText: qsTr("录制")
            onClick: {
                if( videoManager.isRecording() )
                    rovControl.stopRecording()
                else
                    rovControl.startRecording()
            }
        }
        RovToolButton {
            btnImage: "qrc:/res/icon/image.png"
            btnText: qsTr("拍照")
            onClick: { rovControl.grabImage()}
        }

    }
}
