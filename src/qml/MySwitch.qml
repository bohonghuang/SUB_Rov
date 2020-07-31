import QtQuick 2.0
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4

Switch {
    style: SwitchStyle {
        groove: Rectangle {
                implicitWidth: 100
                implicitHeight: 20
                radius: 9
                border.color: control.activeFocus ? "darkblue" : "gray"
                border.width: 1
        }
    }

}
