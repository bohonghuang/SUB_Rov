import QtQuick 2.0

Item {
    width: 480
    height: width * 9 / 16

    signal doubleClick

    property bool smalled: true
    property alias imgSource: subVideo.source

    Rectangle{
        color: "#dbf5f5"
        gradient: Gradient {
            GradientStop {
                position: 0.00;
                color: "#dbf5f5";
            }
            GradientStop {
                position: 1.00;
                color: "#ffffff";
            }
        }
        border.color: "#4f40af"
        anchors.fill: parent

        Image {
            id: imgLogo
            source: "qrc:/res/img/Logo.png"
            width: parent.width/2
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }

        MouseArea {
            id: sub_area
            anchors.fill: parent
            enabled: smalled
            hoverEnabled: true
            drag.target: parent.parent
            drag.minimumX: 0
            drag.minimumY: 66
            drag.maximumX: parent.parent.parent.width  - parent.parent.width
            drag.maximumY: parent.parent.parent.height - parent.parent.height
            onDoubleClicked: {
//                smalled = ! smalled
                doubleClick()
            }
        }
    }

    Image{
        id: subVideo
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        source: ""
        cache: false
    }
}
