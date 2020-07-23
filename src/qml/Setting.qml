import QtQuick 2.0
import QtQuick.Window 2.3
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Rectangle {
    //width: 0

    property bool isTcp: false

    id: settings_rec
    color: "#e5efef"

    width: 400
    height: 800


        GroupBox {
            id: serverbox
            width: 400
            height: 180
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 30
            enabled: true
            font.family: "Tahoma"
            font.pointSize: 15
            title: qsTr("Send & Receive")
            Layout.fillHeight: true
            Layout.topMargin: 20
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            visible: settings_rec.visible

            Label {
                id: lblServerIP
                text: qsTr("IP:")
                anchors.left: parent.left
                anchors.leftMargin: 30
                font.pointSize: 20
                anchors.top: parent.top
                anchors.topMargin: 30
                font.family: "Tahoma"
            }

            TextField {
                id: txtServerIP
                x: 83
                width: 250
                height: 40
                text: settingsMaanger.getServerUri()
                font.weight: Font.Light
                font.pixelSize: 18
                anchors.verticalCenter: lblServerIP.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 30
                placeholderText: qsTr("Server IP")

                onTextChanged: {
                    settingsMaanger.setServerUri(text.toString());
                }
            }

            Label {
                id: lblServerPort
                text: qsTr("Port:")
                anchors.left: parent.left
                anchors.leftMargin: 6
                font.pointSize: 20
                anchors.top: lblServerIP.bottom
                anchors.topMargin: 24
                font.family: "Tahoma"
            }


            TextField {
                id: txtServerPort
                x: 96
                width: 250
                height: 40
                text: settingsMaanger.getServerPort()
                anchors.verticalCenterOffset: 0
                anchors.right: parent.right
                anchors.rightMargin: 30
                font.pixelSize: 18
                font.weight: Font.Light
                anchors.verticalCenter: lblServerPort.verticalCenter
                placeholderText: qsTr("Server Port")

                onTextChanged: {
                    settingsMaanger.setServerPort(text.toString());
                }
            }
        }

        GroupBox {
            id: videobox
            width: 400
            height: 180
            anchors.top: serverbox.bottom
            anchors.topMargin: 30
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            font.family: "Tahoma"
            font.pointSize: 15
            title: qsTr("Video Strem")
            visible: settings_rec.visible;
            ComboBox {
                id: cmbVideo
                Layout.fillWidth: true
                height: 30
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                model: ListModel{
                    id: videoItems
                    ListElement {
                        text: qsTr("UDP 265");
                    }
                    ListElement{
                        text: qsTr("UDP 264");
                    }
                    ListElement {
                        text: qsTr("TCP");
                    }
                }
                currentIndex: settingsMaanger.getStreamType()
                onCurrentIndexChanged: {
                    if(currentIndex === 2){
                        frameTcp.visible = true;
                        frameUdp.visible = false;
                    }
                    else{
                        frameTcp.visible = false;
                        frameUdp.visible = true;
                    }

                    settingsMaanger.setStreamType(currentIndex);

                }
            }

            Frame {
                id: frameUdp
                height: 80
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: cmbVideo.bottom
                anchors.topMargin: 0
                font.family: "Tahoma"

                Label {
                    id: lblvideoPort
                    height: 33
                    text: qsTr("接收端口：")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 219
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    font.family: "Tahoma"
                    font.pointSize: 20
                }
                TextField{
                    id: txtvideoPort
                    y: 12
                    height: 40
                    text: settingsMaanger.getVideoPort()
                    anchors.verticalCenter: lblvideoPort.verticalCenter
                    anchors.left: lblvideoPort.right
                    anchors.leftMargin: 0
                    leftPadding: 6
                    padding: 6
                    font.weight: Font.Light
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    placeholderText: "Video Stream Port"
                    font.family: "Tahoma"
                    font.letterSpacing: 0
                    font.pixelSize: 18

                    onTextChanged: {
                        settingsMaanger.setVideoPort(text.toString());
                    }
                }


            }

            Frame {
                id: frameTcp
                width: 200
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: cmbVideo.bottom
                anchors.topMargin: 0
                visible: false

                Label {
                    id: lblvideoUri
                    text: qsTr("接收Uri：")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    font.pointSize: 20
                }

                TextField{
                    id: txtvideoUri
                    y: 73
                    height: 40
                    text: settingsMaanger.getVideoUrl()
                    anchors.left: lblvideoUri.right
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    placeholderText: qsTr("Video Stream Url")
                    anchors.verticalCenter: lblvideoUri.verticalCenter
                    font.pixelSize: 20
                    onTextChanged: {
                        settingsMaanger.setVideoUrl(text.toString());
                    }
                }
            }
        }

        GroupBox {
            id: videobox_2
            width: 400
            height: 180
            anchors.top: videobox.bottom
            anchors.topMargin: 30
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            font.family: "Tahoma"
            font.pointSize: 15
            title: qsTr("Video Strem 2")
            visible: settings_rec.visible;
            ComboBox {
                id: cmbVideo_2
                Layout.fillWidth: true
                height: 30
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                model: ListModel{
                    id: videoItems_2
                    ListElement {
                        text: qsTr("UDP 265");
                    }
                    ListElement{
                        text: qsTr("UDP 264");
                    }
                    ListElement {
                        text: qsTr("TCP");
                    }
                }
                currentIndex: settingsMaanger.getStreamType_2()
                onCurrentIndexChanged: {
                    if(currentIndex === 2){
                        frameTcp_2.visible = true;
                        frameUdp_2.visible = false;
                    }
                    else{
                        frameTcp_2.visible = false;
                        frameUdp_2.visible = true;
                    }

                    settingsMaanger.setStreamType_2(currentIndex);

                }
            }

            Frame {
                id: frameUdp_2
                height: 80
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: cmbVideo_2.bottom
                anchors.topMargin: 0
                font.family: "Tahoma"

                Label {
                    id: lblvideoPort_2
                    height: 33
                    text: qsTr("接收端口：")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 219
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    font.family: "Tahoma"
                    font.pointSize: 20
                }
                TextField{
                    id: txtvideoPort_2
                    y: 12
                    height: 40
                    text: settingsMaanger.getThermalVideoPort()
                    anchors.verticalCenter: lblvideoPort_2.verticalCenter
                    anchors.left: lblvideoPort_2.right
                    anchors.leftMargin: 0
                    leftPadding: 6
                    padding: 6
                    font.weight: Font.Light
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    placeholderText: "Video Stream Port"
                    font.family: "Tahoma"
                    font.letterSpacing: 0
                    font.pixelSize: 18

                    onTextChanged: {
                        settingsMaanger.setThermalVideoPort(text.toString());
                    }
                }


            }

            Frame {
                id: frameTcp_2
                width: 200
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: cmbVideo_2.bottom
                anchors.topMargin: 0
                visible: false

                Label {
                    id: lblvideoUri_2
                    text: qsTr("接收Uri：")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    font.pointSize: 20
                }

                TextField{
                    id: txtvideoUri_2
                    y: 73
                    height: 40
                    text: settingsMaanger.getVideoUrl()
                    anchors.left: lblvideoUri_2.right
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    placeholderText: qsTr("Video Stream Url")
                    anchors.verticalCenter: lblvideoUri_2.verticalCenter
                    font.pixelSize: 20
                    onTextChanged: {
                        settingsMaanger.setThermalVideoUrl(text.toString())
                    }
                }
            }
        }


        GroupBox {
                id: audiobox
                width: 400
                height: 150
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.family: "Tahoma"
                title: qsTr("Audio Stream")
                font.pointSize: 15
                anchors.top: videobox_2.bottom
                anchors.topMargin: 30
                visible: settings_rec.visible
                Frame {
                    id: frameAudio
                    anchors.fill: parent
                    font.family: "Tahoma"
                    Label {
                        id: lblAudioPort
                        y: 12
                        text: qsTr("接收端口：")
                        anchors.leftMargin: 0
                        font.family: "Tahoma"
                        font.pointSize: 20
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    TextField {
                        id: txtAudioPort
                        y: 17
                        height: 40
                        text: settingsMaanger.getAudioPort()
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        placeholderText: qsTr("Audio Stream Port")
                        anchors.leftMargin: 0
                        font.family: "Tahoma"
                        font.pixelSize: 18
                        anchors.left: lblAudioPort.right
                        font.letterSpacing: 0
                        anchors.verticalCenter: lblAudioPort.verticalCenter
                        onTextChanged: {
                            settingsMaanger.setAudioPort(text.toString());
                        }
                    }

                }

                Frame {
                    id: frameAudioTcp
                    visible: false
                    anchors.fill: parent

                    Label {
                        id: lblAudioUri
                        text: qsTr("接收Uri：")
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 0
                        font.pointSize: 20
                        anchors.left: parent.left
                    }

                    TextField {
                        id: txtAudioUri
                        y: 73
                        height: 40
                        text: settingsMaanger.getAudioUrl()
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        placeholderText: qsTr("Audio Stream Url")
                        anchors.leftMargin: 0
                        font.pixelSize: 20
                        anchors.left: lblAudioUri.right
                        anchors.verticalCenter: lblAudioUri.verticalCenter

                        onTextChanged: {
                            settingsMaanger.setAudioUrl(text.toString())
                        }
                    }
                }

        }


}






/*##^##
Designer {
    D{i:17;anchors_width:186}D{i:26;anchors_width:186}
}
##^##*/
