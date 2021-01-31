import QtQuick 2.0
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml.Models 2.3
import Qt.labs.platform 1.1




Item {
    width: 600
    height: parent.height - 66
    focus: visible

    signal subview(bool show)

    Behavior on x { PropertyAnimation {duration: 100}}

    Rectangle{
        color: "#434343"
        anchors.fill: parent
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
    }

    ScrollView {
        anchors.fill: parent

        ColumnLayout{
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
                        color: "white"
                    }
                    Switch {
                        text: qsTr("")
                        autoRepeat: false
                        display: AbstractButton.TextBesideIcon
                        checked: settingsManager.isEnableCheckout()
                        onCheckedChanged: {
                            settingsManager.setEnableCheckout(checked)
                        }
                    }
                }
            }

            ColumnLayout{
                id: black_color_switch
                Layout.topMargin: 20
                Layout.leftMargin: 20
                RowLayout{
                    Label{
                        text: qsTr("彩色模式")
                        leftPadding: 50
                        topPadding: 10
                        bottomPadding: 10
                        font.pointSize: 20
                        color: "white"
                    }
                    Switch {
                        text: qsTr("")
                        autoRepeat: false
                        display: AbstractButton.TextBesideIcon
                        checked: settingsManager.getEnableBlack()
                        onCheckedChanged: {
                            settingsManager.isEnableBlack(checked)
                        }
                    }
                    Label{
                        text: qsTr("黑白模式")
                        leftPadding: 50
                        topPadding: 10
                        bottomPadding: 10
                        font.pointSize: 20
                        color: "white"
                    }
                }
            }
            ColumnLayout{
                id: frame_area_switch
                Layout.topMargin: 20
                Layout.leftMargin: 20
                RowLayout{
                    Label{
                        text: qsTr("全部帧区域")
                        leftPadding: 50
                        topPadding: 10
                        bottomPadding: 10
                        font.pointSize: 20
                        color: "white"
                    }
                    Switch {
                        text: qsTr("")
                        autoRepeat: false
                        display: AbstractButton.TextBesideIcon
                        checked: settingsManager.getFrameArea()
                        onCheckedChanged: {
                            settingsManager.setFrameArea(checked == true ? 1 : 0)
                        }
                    }
                    Label{
                        text: qsTr("部分帧区域")
                        leftPadding: 50
                        topPadding: 10
                        bottomPadding: 10
                        font.pointSize: 20
                        color: "white"
                    }
                }
            }

            ColumnLayout{
                id: file_dialog_choose
                Layout.topMargin: 20
                Layout.leftMargin: 20
                RowLayout{
                    TextField {
                            id: inputBoxInput
                            text:folderDialog.folder
                            color: "#707070"
                            font.pointSize: 16
//                            selectByMouse: true //是否可以选择文本
//                            selectedTextColor: "white" //设置选择文本的字体颜色
//                            selectionColor: "#4A6DBC" //设置选择框的颜色
                            width: 100
                            height: 30

                            onTextChanged: {
                                settingsManager.setVideoSavePath(text);
                            }

                    }

                Button{
                    text: qsTr("选择路径")
                    height: 40
                    width: 120

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            folderDialog.open()
                        }
                    }
                }
                FolderDialog  {
                    id: folderDialog

                    folder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0] //默认打开Pictures文件夹

                }
                }



            }

            ColumnLayout{
                id: file_dialog_choose_img
                Layout.topMargin: 20
                Layout.leftMargin: 20
                RowLayout{
                    TextField {
                            id: inputBoxInput2
                            text:folderDialog.folder
                            color: "#707070"
                            font.pointSize: 16
//                            selectByMouse: true //是否可以选择文本
//                            selectedTextColor: "white" //设置选择文本的字体颜色
//                            selectionColor: "#4A6DBC" //设置选择框的颜色
                            width: 100
                            height: 30

                            onTextChanged: {
                                settingsManager.setImagePath(text);
                            }

                    }

                Button{
                    text: qsTr("选择图片路径")
                    height: 40
                    width: 120

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            folderDialog2.open()
                        }
                    }
                }
                FolderDialog  {
                    id: folderDialog2

                    folder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0] //默认打开Pictures文件夹

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
                        color: "white"
                    }
                    Switch {
                        text: qsTr("")
                        autoRepeat: false
                        display: AbstractButton.TextBesideIcon

                        onCheckedChanged: {
                            if(checked === true){
                                rovControl.startPi()
                            }
                            else{
                                rovControl.stopPi()
                            }
                        }
                    }
                }
            }

            Label{
                text: qsTr("在启用视频之前，请务必\n确认端口的正确性");
                font.underline: true
                font.italic: true
                font.pointSize: 15
                color: "#f9a0a0"
                Layout.leftMargin: 50
                Layout.topMargin: 10
            }
            ColumnLayout{
                id: mainVideo_enable
                Layout.topMargin: 0
                Layout.leftMargin: 20
                RowLayout{
                    Label{
                        text: qsTr("主播放器启用位")
                        leftPadding: 50
                        topPadding: 10
                        bottomPadding: 10
                        font.pointSize: 20
                        color: "white"
                    }
                    Switch {
                        id: mainVideo_enable_switch
                        text: qsTr("")
                        autoRepeat: false
                        checked: settingsManager.isEnableMainVideo()
                        display: AbstractButton.TextBesideIcon

                        onCheckedChanged: {
                            settingsManager.setEnableMainVideo(checked)
                        }
                    }
                }
            }
            ColumnLayout{
                id: thermalVideo_enable
                Layout.topMargin: 20
                Layout.leftMargin: 20
                RowLayout{
                    Label{
                        text: qsTr("副播放器启动位")
                        leftPadding: 50
                        topPadding: 10
                        bottomPadding: 10
                        font.pointSize: 20
                        color: "white"
                    }
                    Switch {
                        id: thermalVideo_enable_switch
                        text: qsTr("")
                        autoRepeat: false
                        display: AbstractButton.TextBesideIcon
                        checked: settingsManager.isEnableThermal()
                        onCheckedChanged: {
                            subview(checked)
                            settingsManager.setEnableThermal(checked)
                        }
                    }
                }
            }
            Connections {
                target: settingsManager
                function onEnableMainChanged() {
                    mainVideo_enable_switch.checked = settingsManager.isEnableMainVideo()
                }
                function onEnableThermalChanged() {
                    thermalVideo_enable_switch.checked = settingsManager.isEnableThermal()
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
                        color: "white"
                    }
                    Switch {
                        text: qsTr("")
                        autoRepeat: false
                        display: AbstractButton.TextBesideIcon

                        onCheckedChanged: {
                            if(checked === true){
                                rovControl.startDevice()
                            }
                            else{
                                rovControl.stopDevice()
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
                    color: "white"
                }

                RowLayout{
                    Layout.leftMargin: 20
                    //IP 行
                    spacing: 10
                    Label{
                        text: qsTr("IP：")
                        Layout.leftMargin: 28
                        font.pointSize: 20
                        color: "white"
                    }
                    TextField{
                        id: input_server_ip
                        width: 250
                        height: 40
                        text: settingsManager.getServerUri()
                        font.pointSize: 15
                        selectByMouse: true

                        onTextChanged: {
                            settingsManager.setServerUri(text.toString())
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
                        color: "white"
                    }
                    TextField{
                        id: input_server_port
                        width: 250
                        height: 40
                        text: settingsManager.getServerPort()
                        font.pointSize: 15
                        selectByMouse: true

                        onTextChanged: {
                            settingsManager.setServerPort(text.toString())
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
                    color: "white"
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
                    currentIndex: settingsManager.getStreamType()
                    onCurrentIndexChanged: {
                        if(currentIndex == 2){
                            video_udp_1.visible = false;
                            video_tcp_1.visible = true;
                        }
                        else{
                            video_udp_1.visible = true;
                            video_tcp_1.visible = false;
                        }

                        settingsManager.setStreamType(currentIndex);
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
                            color: "white"
                        }
                        TextField{
                            id: input_video_url
                            width: 250
                            height: 40
                            text: settingsManager.getVideoUrl()
                            font.pointSize: 15
                            selectByMouse: true
                            onTextChanged: {
                                settingsManager.setVideoUrl(text.toString())
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
                            color: "white"
                        }
                        TextField{
                            id: input_video_port
                            width: 250
                            height: 40
                            text: settingsManager.getVideoPort()
                            font.pointSize: 15
                            selectByMouse: true

                            onTextChanged: {
                                settingsManager.setVideoPort(text.toString())
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
                    color: "white"
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
                    currentIndex: settingsManager.getStreamType_2()
                    onCurrentIndexChanged: {
                        if(currentIndex == 2){
                            video_udp_2.visible = false;
                            video_tcp_2.visible = true;
                        }
                        else{
                            video_udp_2.visible = true;
                            video_tcp_2.visible = false;
                        }

                        settingsManager.setStreamType_2(currentIndex)
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
                            color: "white"
                        }
                        TextField{
                            id: input_video_url_2
                            width: 250
                            height: 40
                            text: settingsManager.getThermalVideoUrl()
                            font.pointSize: 15
                            selectByMouse: true
                            onTextChanged: {
                                settingsManager.setThermalVideoUrl(text.toString())
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
                            color: "white"
                        }
                        TextField{
                            id: input_video_port_2
                            width: 250
                            height: 40
                            text: settingsManager.getThermalVideoPort()
                            font.pointSize: 15
                            selectByMouse: true

                            onTextChanged: {
                                settingsManager.setThermalVideoPort(text.toString())
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
                    color: "white"
                }

                RowLayout{
                    Layout.leftMargin: 20
                    //端口 行
                    spacing: 10
                    Label{
                        text: qsTr("Port：")
                        font.pointSize: 20
                        color: "white"
                    }
                    TextField{
                        width: 250
                        height: 40
                        text: settingsManager.getAudioPort();
                        font.pointSize: 15
                        selectByMouse: true

                        onTextChanged: {
                            settingsManager.setAudioPort(text.toString())
                        }

                    }
                }



            }


        }

    }
}
