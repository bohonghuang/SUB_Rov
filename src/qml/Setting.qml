import QtQuick 2.0
import QtQuick.Window 2.3
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Page {
    //width: 0

    property bool isTcp: false

    property alias page_open_running: page_open.running
    property alias page_close_running: page_close.running


    id: settings_rec
    background: Image {
        id: img_back_settings
        fillMode: Image.TileVertically
        source: "../../resource/img/geometry.png"
    }

    visible: true


    width: 400
    height: 600
    focusPolicy: Qt.ClickFocus
    focus: visible

    ScrollView{
        id: scrollView
        anchors.fill: parent
        ColumnLayout{
            id: column
            width: 400
            spacing: 20

            ColumnLayout{
                id: check_out_enable
                Layout.topMargin: 20
                Layout.leftMargin: 20
                RowLayout{
                    Label{
                        text: qsTr("启用检查字")
                        leftPadding: 50
                        topPadding: 10
                        bottomPadding: 10
                        font.pointSize: 20
                    }
                    Switch {
                        text: qsTr("")
                        autoRepeat: false
                        display: AbstractButton.TextBesideIcon
                        checked: settingsMaanger.isEnableCheckout()
                        onCheckedChanged: {
                            settingsMaanger.setEnableCheckout(checked)
                        }
                    }
                }
            }

            ColumnLayout{
                id: pi_enable
                Layout.topMargin: 20
                Layout.leftMargin: 20
                RowLayout{
                    Label{
                        text: qsTr("Pi 启用位")
                        leftPadding: 50
                        topPadding: 10
                        bottomPadding: 10
                        font.pointSize: 20
                    }
                    Switch {
                        text: qsTr("")
                        autoRepeat: false
                        display: AbstractButton.TextBesideIcon

                        onCheckedChanged: {
                            if(checked === true){
                                rovControl.doStartPi()
                            }
                            else{
                                rovControl.doStopPi()
                            }
                        }
                    }
                }
            }

            ColumnLayout{
                id: device_enable
                Layout.topMargin: 20
                Layout.leftMargin: 20
                RowLayout{
                    Label{
                        text: qsTr("设备启动位")
                        leftPadding: 50
                        topPadding: 10
                        bottomPadding: 10
                        font.pointSize: 20
                    }
                    Switch {
                        text: qsTr("")
                        autoRepeat: false
                        display: AbstractButton.TextBesideIcon

                        onCheckedChanged: {
                            if(checked === true){
                                rovControl.doStart()
                            }
                            else{
                                rovControl.doStop()
                            }
                        }
                    }
                }
            }

            ColumnLayout{
                id: server_box
                width: 400
                height: 180
                Layout.topMargin: 20
                Layout.leftMargin: 20
                Label{
                    text: qsTr("通信传输")
                    font.italic: true
                    font.bold: true
                    font.underline: false
                    bottomPadding: 10
                    font.pointSize: 20
                }

                RowLayout{
                    Layout.leftMargin: 20
                    //IP 行
                    spacing: 10
                    Label{
                        text: qsTr("IP：")
                        Layout.leftMargin: 28
                        font.pointSize: 20
                    }
                    TextField{
                        id: input_server_ip
                        width: 250
                        height: 40
                        text: settingsMaanger.getServerUri()
                        font.pointSize: 15
                        selectByMouse: true

                        onTextChanged: {
                            settingsMaanger.setServerUri(text.toString())
                        }

                    }
                }
                RowLayout{
                    Layout.leftMargin: 20
                    //端口 行
                    spacing: 10
                    Label{
                        text: qsTr("Port：")
                        font.pointSize: 20
                    }
                    TextField{
                        id: input_server_port
                        width: 250
                        height: 40
                        text: settingsMaanger.getServerPort()
                        font.pointSize: 15
                        selectByMouse: true

                        onTextChanged: {
                            settingsMaanger.setServerPort(text.toString())
                        }
                    }
                }



            }

            ColumnLayout{
                id: video_box_1
                width: 400
                height: 180
                Layout.topMargin: 20
                Layout.leftMargin: 20
                Label{
                    text: qsTr("视频传输")
                    font.italic: true
                    font.bold: true
                    font.underline: false
                    bottomPadding: 10
                    font.pointSize: 20
                }
                ComboBox{
                    font.pointSize: 15
                    model: ListModel{
                        ListElement{
                            text: qsTr("UDP 265")

                        }
                        ListElement{
                            text: qsTr("UDP 264")

                        }
                        ListElement{
                            text: qsTr("TCP/MPEG2")

                        }
                    }
                    currentIndex: settingsMaanger.getStreamType()
                    onCurrentIndexChanged: {
                        if(currentIndex == 2){
                            video_udp_1.visible = false;
                            video_tcp_1.visible = true;
                        }
                        else{
                            video_udp_1.visible = true;
                            video_tcp_1.visible = false;
                        }

                        settingsMaanger.setStreamType(currentIndex);
                    }
                }
                ColumnLayout{
                    id: video_tcp_1
                    RowLayout{
                        Layout.leftMargin: 20
                        //IP 行
                        spacing: 10
                        Label{
                            text: qsTr("URL：")
                            Layout.leftMargin: 15
                            font.pointSize: 20
                        }
                        TextField{
                            id: input_video_url
                            width: 250
                            height: 40
                            text: settingsMaanger.getVideoUrl()
                            font.pointSize: 15
                            selectByMouse: true
                            onTextChanged: {
                                settingsMaanger.setVideoUrl(text.toString())
                            }
                        }
                    }

                }

                ColumnLayout{
                    id: video_udp_1
                    RowLayout{
                        Layout.leftMargin: 20
                        //端口 行
                        spacing: 10
                        Label{
                            text: qsTr("Port：")
                            font.pointSize: 20
                        }
                        TextField{
                            id: input_video_port
                            width: 250
                            height: 40
                            text: settingsMaanger.getVideoPort()
                            font.pointSize: 15
                            selectByMouse: true

                            onTextChanged: {
                                settingsMaanger.setVideoPort(text.toString())
                            }
                        }
                    }
                }
            }

            ColumnLayout{
                id: video_box_2
                width: 400
                height: 180
                Layout.topMargin: 20
                Layout.leftMargin: 20
                Label{
                    text: qsTr("副视频传输")
                    font.italic: true
                    font.bold: true
                    font.underline: false
                    bottomPadding: 10
                    font.pointSize: 20
                }
                ComboBox{
                    font.pointSize: 15
                    model: ListModel{
                        ListElement{
                            text: qsTr("UDP 265")

                        }
                        ListElement{
                            text: qsTr("UDP 264")

                        }
                        ListElement{
                            text: qsTr("TCP/MPEG2")

                        }
                    }
                    currentIndex: settingsMaanger.getStreamType_2()
                    onCurrentIndexChanged: {
                        if(currentIndex == 2){
                            video_udp_2.visible = false;
                            video_tcp_2.visible = true;
                        }
                        else{
                            video_udp_2.visible = true;
                            video_tcp_2.visible = false;
                        }

                        settingsMaanger.setStreamType_2(currentIndex)
                    }
                }
                ColumnLayout{
                    id: video_tcp_2
                    RowLayout{
                        Layout.leftMargin: 20
                        //IP 行
                        spacing: 10
                        Label{
                            text: qsTr("URL：")
                            Layout.leftMargin: 15
                            font.pointSize: 20
                        }
                        TextField{
                            id: input_video_url_2
                            width: 250
                            height: 40
                            text: settingsMaanger.getThermalVideoUrl()
                            font.pointSize: 15
                            selectByMouse: true
                            onTextChanged: {
                                settingsMaanger.setThermalVideoUrl(text.toString())
                            }
                        }
                    }

                }

                ColumnLayout{
                    id: video_udp_2
                    RowLayout{
                        Layout.leftMargin: 20
                        //端口 行
                        spacing: 10
                        Label{
                            text: qsTr("Port：")
                            font.pointSize: 20
                        }
                        TextField{
                            id: input_video_port_2
                            width: 250
                            height: 40
                            text: settingsMaanger.getThermalVideoPort()
                            font.pointSize: 15
                            selectByMouse: true

                            onTextChanged: {
                                settingsMaanger.setThermalVideoPort(text.toString())
                            }

                        }
                    }

                }




            }



            ColumnLayout{
                id: audio_box
                width: 400
                height: 180
                Layout.topMargin: 20
                Layout.leftMargin: 20
                Label{
                    text: qsTr("声音通信")
                    font.italic: true
                    font.bold: true
                    font.underline: false
                    bottomPadding: 10
                    font.pointSize: 20
                }

                RowLayout{
                    Layout.leftMargin: 20
                    //端口 行
                    spacing: 10
                    Label{
                        text: qsTr("Port：")
                        font.pointSize: 20
                    }
                    TextField{
                        width: 250
                        height: 40
                        text: settingsMaanger.getAudioPort();
                        font.pointSize: 15
                        selectByMouse: true

                        onTextChanged: {
                            settingsMaanger.setAudioPort(text.toString())
                        }

                    }
                }



            }

            ColumnLayout{
                id: test_box
                width: 400
                height: 180
                Layout.bottomMargin: 30
                Layout.topMargin: 20
                Layout.leftMargin: 20
                Label{
                    text: qsTr("无用的测试组")
                    font.italic: true
                    font.bold: true
                    font.underline: false
                    bottomPadding: 10
                    font.pointSize: 20
                }

                RowLayout{
                    Layout.leftMargin: 20
                    //端口 行
                    spacing: 10
                    Label{
                        text: qsTr("Port：")
                        font.pointSize: 20
                    }
                    TextField{
                        width: 250
                        height: 40
                        text: qsTr("123")
                        font.pointSize: 15
                        selectByMouse: true

                    }
                }



            }



        }



    }
    ParallelAnimation{
        id: page_open
        onStarted: {
            settings_rec.x = -500;
            settings_rec.z = 10
            settings_rec.width = 0
            settings_rec.visible = true;
        }
        PropertyAnimation{
            target: settings_rec
            property: "width"
            to: 600
            duration: 200
        }
        PropertyAnimation{
            target: settings_rec
            property: "x"
            to: 0
            duration: 200
        }
        PropertyAnimation{
            target: settings_rec
            property: "opacity"
            to: 1
            duration: 200
        }
    }
    ParallelAnimation{
        id: page_close
        onStopped: {
            settings_rec.x = -500
            settings_rec.z = -10
            settings_rec.visible = false;
            settings_rec.enabled
        }
        PropertyAnimation{
            target: settings_rec
            property: "width"
            to: 0
            duration: 200
        }
        PropertyAnimation{
            target: settings_rec
            property: "x"
            to: -500
            duration: 200
        }
        PropertyAnimation{
            target: settings_rec
            property: "opacity"
            to: 0
            duration: 200
        }
    }


}









