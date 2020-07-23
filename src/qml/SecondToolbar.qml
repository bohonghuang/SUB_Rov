import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    width: 330
    height: 78

    Rectangle{
        id: tool
        color: "black"
        radius: 5
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        width: 322
        height: 78
        //height: 0
        RowLayout {
            id: rowTool
            anchors.centerIn: parent

            MyButton {
                id: btn_deep
                btnimgSource: "icon/deep.png"
                btnstr: "Deep"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("deep Cliked");
                        rovControl.doLockDeep();
                    }
                }
            }

            MyButton {
                id: btn_direction
                btnimgSource: "icon/direc.png"
                btnstr: "Direction"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("deep Cliked");
                        rovControl.doLockDirection();
                    }
                }
            }

            MyButton {
                id: btn_image
                btnimgSource: "icon/image.png"
                btnstr: "Grap"
                MouseArea {
                    anchors.fill: parent
                    onClicked: grabImage();
                }
            }
        }
    }
    ButtonSecondToolbar{
        id: btn_tool
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        z: 99

        MouseArea{
            anchors.fill: parent
            onClicked: {
                btnSecondToolClicked();
            }
        }
    }
}
