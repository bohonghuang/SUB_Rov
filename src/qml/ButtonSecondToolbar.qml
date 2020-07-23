import QtQuick 2.0

Item {
    width: 120
    height: 50

    property alias imgSource: image.source
    property bool isClicked: false

    Image {
        id: image
        width: parent.width
        height: parent.height
        source: "../../resource/icon/let_down.png"
        fillMode: Image.PreserveAspectFit

    }
}
