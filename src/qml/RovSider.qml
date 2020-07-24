import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3


Item {
    property bool btnSettingsClicked: false
    property bool btnSocketSuccess: false
    property bool btnRecordingSuccess: false

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
                btnstr: qsTr("数据连接")
                visible: btnSocketSuccess ? false:true
                btnimgSource: "../../resource/icon/connect.png"
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: connectSocket();
                }
            }

            MyButton{
                id: btn_socket_stop
                visible: btnSocketSuccess ? true:false
                btnstr: qsTr("中断连接")
                btnimgSource:"../../resource/icon/close.png"
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: disConnect()
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

            MyButton{
                id: btn_recording_content
                btnstr:  qsTr("开始录像")  //
                btnimgSource: "../../resource/icon/video_on.png" //
                visible: btnRecordingSuccess ? false : true

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: startRecording()
                }

            }

            MyButton{
                id: btn_recording_stop
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
                btnstr: qsTr("停止录制")
                btnimgSource:"../../resource/icon/video_off.png"

                visible: btnRecordingSuccess ? true:false
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: stopRecording()
                }
            }

        }
    }


    function reStartVideos(){
        videoManager.restartVideos();
    }

    function openSettingsPage(){
        btnSettingsClicked = !btnSettingsClicked;


    }

    function connectSocket(){
        socketManager.connectServer();
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
