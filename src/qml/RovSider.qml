import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3


Item {
    property bool btnSettingsClicked: false
    property bool btnSocketSuccess: false
    property bool btnRecordingSuccess: false

    property bool socketSuccess: false
    property bool recordSucess: false
    property bool rovStatus_start_stop: false
    ToolBar{
        id: toolBar
        width: parent.width
        Rectangle{
            width: parent.width
            height: 66
            color: "#434343"
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
        RowLayout{
            MyButton{
                id: btn_settings
                btnstr: qsTr("设置")
                btnimgSource: btnSettingsClicked ? "../../resource/icon/main.png" : "../../resource/icon/setting.png"
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: openSettingsPage();
                }
            }

            MyButton{
                id: btn_socket_start
                btnstr: socketSuccess ? qsTr("数据断开") : qsTr("数据连接")
                //visible: btnSocketSuccess ? false:true
                btnimgSource: socketSuccess ? "../../resource/icon/close.png" : "../../resource/icon/connect.png"
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: socketSuccess ? disConnect() : connectSocket();
                }
            }

            MyButton{
                id: btn_restart_video
                btnstr: qsTr("重置视频流");
                btnimgSource: "../../resource/icon/round.png";
                MouseArea{
                    anchors.fill: parent;
                    cursorShape: Qt.PointingHandCursor
                    onClicked: reStartVideos();
                }
            }

//            MyButton {
//                id: btn_status_control
//                btnstr: socketSuccess ? qsTr("停止") : qsTr( "启动")
//                btnimgSource: socketSuccess ? "../../resource/icon/白字_止.png" : "../../resource/icon/白字_起.png"
//                visible: socketSuccess
//                MouseArea {
//                    anchors.fill: parent
//                    cursorShape: Qt.PointingHandCursor
//                    onClicked: socketSuccess ? rovControl.doStop() : rovControl.doStart()
//                }
//            }

            MyButton{
                id: btn_recording_content
                btnstr: recordSucess ? qsTr("结束录像") : qsTr("开始录像")  //
                btnimgSource: recordSucess ? "../../resource/icon/video_off.png" : "../../resource/icon/video_on.png" //


                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: recordSucess ? stopRecording() : startRecording()
                }

            }

        }
    }

    Connections{
        target: socketManager
        onEnableChanged: {
            socketSuccess = socketManager.isEnable();
            console.log(socketSuccess);
        }
    }

    Connections{
        target: videoManager
        onRecordingChanged: {
            recordSucess = videoManager.isRecording()
        }
    }


    function reStartVideos(){
        videoManager.restartVideos();
    }

    function openSettingsPage(){
        btnSettingsClicked = !btnSettingsClicked;


    }

    function connectSocket(){
        socketManager.enableSocket(true)
        socketManager.connectServer()

    }

    function disConnect(){
        socketManager.disConnectServer();

    }

    function startRecording(){
        videoManager.startRecording();
    }

    function stopRecording(){
        videoManager.stopRecording();
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
