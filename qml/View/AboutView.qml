import QtQuick 2.0
import QtQuick.Window 2.3

Window {
    height: 200
    width: 400
    visible: true


    Column{
        id: column
        spacing: 10
        Text {
            id: head
            text: qsTr("JMU SUB ROV")
            font.bold: true
            font.pointSize: 40
        }
        Text {
            id: body
            text: qsTr("version -- 0.21")
            anchors.left: parent.left
            anchors.leftMargin: 20
            font.pointSize: 20
        }
    }
}
