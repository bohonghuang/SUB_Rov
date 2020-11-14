import QtQuick 2.0
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtGamepad 1.12

import "../Video"
import "../ToolBar"
import "../Info"
import "../"

Window {
    id: window
    width: 1600
    height: 900+66
    title: "Sub Rov v0.20"

    visible: false

    Label{
        text: gamepad.gamepadConnected ? qsTr("Connected gamepad: ")+gamepad.gamepadID : qsTr("Don't connected gamepad")
        y: 100
    }
    AboutView{
        id: aboutView
        visible: false
    }
    RovGamepad{
        id: gamepad
    }

    Item {
        focus: true
        id: keyhandler
        Keys.enabled: true
        Keys.onPressed: {
            keyManager.doThings(event.key)
        }
        Keys.onReleased: {
            keyManager.doRelease(event.key)
        }
    }
    VideoView{
        id: video_view
        x: smalled ? 100 : 0
        y: smalled ? parent.height - 100 - height : toolbar.height
        width: smalled ? 480 : parent.width
        Keys.forwardTo: keyhandler

        z: smalled ? 0 : -1
        onDoubleClick: {
            video_view.smalled = !video_view.smalled
            sub_View.smalled = !sub_View.smalled
        }

        Connections{
            target: videoManager
            function onFrame1Changed() {
                video_view.imgSource = "";
                video_view.imgSource = "image://provider"
            }
            function onFrame2Changed() {
                sub_View.imgSource = "";
                sub_View.imgSource = "image://thermalProvider"
            }


        }
    }

    SubView {
        id: sub_View
        Keys.forwardTo: keyhandler
        x: smalled ? 100 : 0
        y: smalled ? parent.height - 100 - height : toolbar.height
        width: smalled ? 480 : parent.width

        z: smalled ? 0 : -1
        visible: settingsManager.isEnableThermal()

        onDoubleClick: {
            video_view.smalled = !video_view.smalled
            sub_View.smalled = !sub_View.smalled
        }
        onWidthChanged: {
            settingsManager.setThermalWidth(width);
        }
        onHeightChanged: {
            settingsManager.setThermalHeight(height);
        }
    }

    SettingsView{
        id: settingsView
        x: parent.x - width
        anchors.top: toolbar.bottom
        Keys.forwardTo: keyhandler

        onSubview: {
            sub_View.visible = show
        }
    }

    RovToolbar {
        id: toolbar
        width: parent.width
        Keys.forwardTo: keyhandler

        onSettings: {
            if( settingsView.x === 0){
                settingsView.x = parent.x - settingsView.width
                toolbar.focus = true
            }
            else{
                settingsView.x = 0
                settingsView.focus = true
            }
        }
        onAbout: {
            aboutView.visible = true;
        }
    }
    RovInfo{
        id: info
        x: parent.width - width
        y: toolbar.height
        Keys.forwardTo: keyhandler

    }
    RovInfoSwitch{
        Keys.forwardTo: keyhandler
        anchors.top: toolbar.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        onClose: {
            info.closing()
        }
        onOpen: {
            info.opening()
        }
    }

}
