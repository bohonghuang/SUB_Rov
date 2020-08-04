import QtQuick 2.0

Item {
    id: splash
    anchors.fill: parent

    property int timeoutInterval: 2000
    signal timeout

    Image {
        id: splashImage
        source: "../../resource/img/Logo.png"
        anchors.fill: parent
    }

    Timer{
        interval: timeoutInterval; repeat: false; running: true;
        onTriggered: {
            visible = false;
            splash.timeout()
        }
    }
}
