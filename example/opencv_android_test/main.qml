import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

import Rov.VideoManager 1.0

Window {
    width: 640
    height: 480
    visible: true
//    title: qsTr("Hello World")
    Button {
        id : btn
        text: qsTr("Click");
        onClicked: {
            videomanager.startvideo()
            console.log("clicked")
        }
    }

    Rectangle{

        Image {
            id: img
            source: ""
            anchors.centerIn: parent
            cache: true
        }

        Connections {
            target: videomanager
            onFrameChanged:  {
                img.source = "image://provider"
            }
        }
    }

}
