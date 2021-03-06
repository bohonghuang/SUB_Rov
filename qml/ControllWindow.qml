import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: controller_window
    width: 600
    height: 800
    visible: true


    Column {
    anchors.fill: parent

    // 左右

    Column{
        id: row
        anchors.horizontalCenter: parent.horizontalCenter
        Row{
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                text: qsTr("左")
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 16

            }
            Slider {
                from: 0
                to: 255
                value: pressed ? value : 127
                width: 400
                height: 60

                onValueChanged: {
                    // 重置时依然可以触发

                }
            }
            Text {
                text: qsTr("右")
                font.pointSize: 16
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Row{
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                text: qsTr("左旋")
                font.pointSize: 16
                anchors.verticalCenter: parent.verticalCenter

            }
            Slider {
                from: 0
                to: 255
                value: pressed ? value : 127
                width: 400
                height: 60

                onValueChanged: {
                    // 重置时依然可以触发

                }
            }
            Text {
                text: qsTr("右旋")
                font.pointSize: 16
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }


    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        Column {
            spacing: 10
            Text {
                text: qsTr("前")
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 16
            }
            Slider {
                from: 0
                to: 255
                value: pressed ? value : 127
                width: 60
                height: 200

                orientation: Qt.Vertical
                anchors.horizontalCenter: parent.horizontalCenter

                onValueChanged: {
                    // 重置时依然可以触发

                }
            }
            Text {
                text: qsTr("后")
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 16
            }
        }

        Column{
            spacing: 10
            Text {
                text: qsTr("上")
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 16
            }
            Slider {
                from: 0
                to: 255
                value: pressed ? value : 127
                width: 60
                height: 200

                orientation: Qt.Vertical
                anchors.horizontalCenter: parent.horizontalCenter

                onValueChanged: {
                    // 重置时依然可以触发

                }
            }
            Text {
                text: qsTr("下")
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 16
            }
        }


    }

    Row {
        id: row1
        spacing: 10
        padding: 20
        anchors.horizontalCenter: parent.horizontalCenter


    Rectangle {
        width: 150
        height:150
        border.color: "black"
        border.width: 2


        Button {
            x: 40
            y: 0
            width: 70
            height: 37

            text: qsTr("↑")
        }

        Button {
            x: 0
            y: 40
            width: 37
            height: 70

            text: qsTr("←")
        }
        Button {
            x: 113
            y: 40
            width: 37
            height: 70

            text: qsTr("→")
        }

        Button {
            x: 40
            y: 113
            width: 70
            height: 37

            text: qsTr("↓")
        }
    }

    Rectangle {
        width: 150
        height:150
        border.color: "black"
        border.width: 2
        anchors.leftMargin: 10


        Button {
            x: 40
            y: 0
            width: 70
            height: 37

            text: qsTr("Y")
            background: Rectangle{
                anchors.fill: parent
                color: "orange"
            }

        }

        Button {
            x: 0
            y: 40
            width: 37
            height: 70

            text: qsTr("X")
            background: Rectangle{
                anchors.fill: parent
                color: "blue"
            }
        }
        Button {
            x: 113
            y: 40
            width: 37
            height: 70

            text: qsTr("B")
            background: Rectangle{
                anchors.fill: parent
                color: "red"
            }
        }

        Button {
            x: 40
            y: 113
            width: 70
            height: 37

            text: qsTr("A")
            background: Rectangle{
                anchors.fill: parent
                color: "green"
            }
        }
    }
    }
    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    Rectangle {
        width: 200
        height:150
        border.color: "black"
        border.width: 2


        Button {
            x: 25
            y: 0
            width: 70
            height: 50

            text: qsTr("LB")

        }

        Button {
            x: 25
            y: 100
            width: 70
            height: 50

            text: qsTr("LT")
        }

        Button {
            x: 105
            y: 0
            width: 70
            height: 50

            text: qsTr("RB")

        }

        Button {
            x: 105
            y: 100
            width: 70
            height: 50

            text: qsTr("RT")
        }
    }
    }

}

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
