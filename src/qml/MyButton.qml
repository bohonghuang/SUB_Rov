import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: btn_root
    height: 66
    color: "#00000000"
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
    width:  100

    property alias btnimgSource: btnimg.source

    ParallelAnimation{
        id: mouse_enter
        onStarted: {
            btn_text.x = (btn_root.width - btn_text.width) / 2;
            btn_text.y = 33
            btn_text.visible = true;
        }

        PropertyAnimation{
            target: btnimg
            property: "x"
            to: 39
            duration: 150
        }
        PropertyAnimation{
            target: btnimg
            property: "y"
            to: 15
            duration: 150
        }
        PropertyAnimation{
            target: btnimg
            properties: "width, height"
            to: 22
            duration: 150
        }
        PropertyAnimation{
            target: btn_text
            property: "y"
            to: 40
            duration: 150
        }
        PropertyAnimation{
            target: btn_text
            property: "opacity"
            to: 1
            duration: 150
        }

        ColorAnimation {
            from: "black"
            to: "gray"
            duration: 100
        }
    }
    ParallelAnimation{
        id: mouse_exit
        onStopped: {
            btn_text.visible = false;
        }

        PropertyAnimation{
            target: btnimg
            property: "x"
            to: 28
            duration: 150
        }
        PropertyAnimation{
            target: btnimg
            property: "y"
            to: 11
            duration: 150
        }
        PropertyAnimation{
            target: btnimg
            properties: "width, height"
            to: 44
            duration: 150
        }
        PropertyAnimation{
            target: btn_text
            property: "y"
            to: 33
            duration: 150
        }
        PropertyAnimation{
            target: btn_text
            property: "opacity"
            to: 0
            duration: 150
        }


        ColorAnimation {
            from: "gray"
            to: "black"
            duration: 100
        }
    }

    MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: mouseEntering()
            onExited: mouseExiting()
            onPressed: {
                parent.color = "darkgray"
            }
            onReleased: {
                parent.color = "gray"
            }
        }


    property string btnstr: qsTr("")
    Text {
        //anchors.centerIn: parent
        visible: false
        y: 30
        id: btn_text
        color: "white"
        text: qsTr(btnstr)
        font.pixelSize: 14

    }

    Image {
        id: btnimg
        source: "file"

        width: 44
        height: 44
        x: 28
        y: 11
    }

    function mouseEntering(){
        mouse_enter.running = true;
    }
    function mouseExiting(){
        mouse_exit.running = true;
    }

}
