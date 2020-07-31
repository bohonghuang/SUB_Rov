import QtQuick 2.11
import QtQuick.Window 2.3
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGamepad 1.12

import Rov.VideoManager 1.0
import Rov.SocketManager 1.0
import Rov.ReceiveManager 1.0
import Rov.SendManager 1.0
import Rov.Controler 1.0

import './src/qml'

Window {
    id: root
    visible: true
    width: 1600
    height: 900 + 66
    title: qsTr("Rov Controller")


    RovSider{
        id: rov_sider
        x: 0
        y: 0
        z: 100
        width: parent.width
        height: 66

        onBtnSettingsClickedChanged: {
            if(rov_sider.btnSettingsClicked == true){
                page_open.running = true;
                settingsPage.focus = true;
            }
            else{
                page_close.running = true;
                mainPage.focus = true;

                settingsMaanger.udpSettings();
            }
        }

        Image {
            id: image
            x: 1420
            width: 180
            height: 66
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            source: "resource/img/Logo.png"
            fillMode: Image.PreserveAspectFit

            MouseArea{
                anchors.fill: parent
                cursorShape: "PointingHandCursor"
                onClicked: {
                    about_page.visible = true
                }
            }
        }
    }

    AboutPage{
        id: about_page
        visible: false

    }


    Page{
        id: mainPage
        font.family: "Tahoma"
        anchors.topMargin: 66
        anchors.fill: parent
        visible: true
        //visible: mainPageView()

        property bool isClicked : false;
        property var _videoReceiver: videoManager.videoReceiver
        Rectangle{
            color: "#e8f0f0"
            anchors.fill: parent
            BorderImage {
                id: borderImage
                width: 800
                height: width/2.4
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                source: "../../resource/img/Logo.png"
            }
            VideoBackground{
                id: videoContent
                width: 400
                height: 225
                objectName: "videoContent";
                anchors.fill: parent
                anchors.centerIn: parent
            }

            MouseArea{
                anchors.fill: parent
            }
        }
    }
    Setting {
        id: settingsPage
        anchors.top: rov_sider.bottom
        width: 0;
        visible: false

        ParallelAnimation{
            id: page_open
            onStarted: {
                settingsPage.x = -500;
                settingsPage.visible = true;
                settingsPage.z = 10
            }
            PropertyAnimation{
                target: settingsPage
                property: "width"
                to: 600
                duration: 200
            }
            PropertyAnimation{
                target: settingsPage
                property: "x"
                to: 0
                duration: 200
            }
            PropertyAnimation{
                target: settingsPage
                property: "opacity"
                to: 1
                duration: 200
            }
        }
        ParallelAnimation{
            id: page_close
            onStopped: {
                settingsPage.x = -500
                settingsPage.z = -10
                settingsPage.visible = false;
                settingsPage.enabled
            }
            PropertyAnimation{
                target: settingsPage
                property: "width"
                to: 0
                duration: 200
            }
            PropertyAnimation{
                target: settingsPage
                property: "x"
                to: -500
                duration: 200
            }
            PropertyAnimation{
                target: settingsPage
                property: "opacity"
                to: 0
                duration: 200
            }
        }
    }


    //信息info区域
    RovInfo{
        id: rovinfo
        x: root.width - 160 - 5
        y: 80
        z: 5
        width: 160
        height: 520
        Drag.active: true

        MouseArea{
            id: rovinfo_mouse
            property int nowX: 0
            property int nowY: 0
            anchors.fill: parent
            hoverEnabled: true;
            drag.target: rovinfo
            drag.minimumX: 0
            drag.minimumY: 66
            drag.maximumX: root.width - rovinfo.width
            drag.maximumY: root.height - rovinfo.height
        }
    }
    //info的收缩按钮
    ButtonInfo{
        id: btn_info_updown
        x: 1550
        anchors.top: parent.top
        anchors.topMargin: 75
        anchors.right: parent.right
        anchors.rightMargin: 10
        z: 99

        MouseArea{
            anchors.fill: parent
            onClicked: rovInfoView();
            cursorShape: Qt.PointingHandCursor
        }
    }

    Rectangle{
        id: toolbar_second
        width: 330
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter


        Rectangle{
            id: toolbar_second_body
            width: parent.width
            height: 66
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top

            RowLayout {
                id: rowTool
                anchors.centerIn: parent

                MyButton {
                    id: btn_deep
                    btnimgSource: "../../resource/icon/deep.png"
                    btnstr: "Deep"

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            rovControl.doLockDeep();
                        }
                    }
                }

                MyButton {
                    id: btn_direction
                    btnimgSource: "../../resource/icon/direc.png"
                    btnstr: "Direction"
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            rovControl.doLockDirection();
                        }
                    }
                }

                MyButton {
                    id: btn_image
                    btnimgSource: "../../resource/icon/image.png"
                    btnstr: "Grap"
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: grabImage();
                    }
                }
            }

        }
        ButtonSecondToolbar{
            id: toolbar_second_btn
            anchors.top: parent.top
            anchors.topMargin: 66
            anchors.horizontalCenter: parent.horizontalCenter
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    btnSecondToolClicked()
                }
            }
        }
        ParallelAnimation{
            id: btn_second_clicked_1
            PropertyAnimation{
                target: toolbar_second
                property: "anchors.topMargin"
                to: 66
                duration: 200
            }
            onStarted: {
                toolbar_second_btn.imgSource = "../../resource/icon/let_up.png"
            }
        }
        ParallelAnimation{
            id: btn_second_clicked_2
            PropertyAnimation{
                target: toolbar_second
                property: "anchors.topMargin"
                to: 0
                duration: 200
            }
            onStarted: {
                toolbar_second_btn.imgSource = "../../resource/icon/let_down.png"
            }

        }
    }

    MyGamePad{
        id: mygame

    }

    Item{
        anchors.fill: parent;
        focus: true;
        Keys.enabled: true;
        Keys.onPressed: {
            keyManager.doThings(event.key);
        }

        Keys.onReleased: {
            keyManager.doRelease(event.key);
        }

    }

    Timer{
        id: timer_refresh
        repeat: true
        interval: 200
        running: true;
        onTriggered: refresh();
    }

    Connections{
        target: settingsMaanger
        onServerUriChanged: {
            console.log("server uri is changed");
        }
        onServerPortChanged:{
            console.log("server port is changed");
        }
        onVideoUriChanged: {
            console.log("video uri is changed");
            videoManager.restartVideos();
        }
        onVideoPortChanged: {
            console.log("video port is changed");
            videoManager.restartVideos();
        }

    }

    function settingsPageView() {
        return rov_sider.btnSettingsClicked;
    }

    function mainPageView(){
        return !rov_sider.btnSettingsClicked;
    }

    function rovInfoView(){
        if(rovinfo.visible === true){
            rovinfo.rovinfo_animation_hidden = true;
            btn_info_updown.btn_animation_toDown = true;
        }
        else{
            rovinfo.rovinfo_animation_show = true;
            btn_info_updown.btn_animation_toUp = true;
        }
    }

    function grabImage(){
        mainPage.grabToImage(function(result) {
            result.saveToFile( settingsMaanger.getImagePath() );
        });
    }

    function btnSecondToolClicked(){
        if(toolbar_second_btn.isClicked === false){
            btn_second_clicked_1.running = true;
        }
        else{
            btn_second_clicked_2.running = true;
        }
        toolbar_second_btn.isClicked = !toolbar_second_btn.isClicked ;
    }

    function refresh(){


    }


}




