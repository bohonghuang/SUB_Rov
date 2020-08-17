import QtQuick 2.0
import QtQuick.Window 2.3

Window {
    id: splash
    color: "transparent"
    title: "Splash Window"
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen | Qt.WindowStaysOnTopHint

    x: (Screen.width - splashImage.width) / 2
    y: (Screen.height - splashImage.height) / 2
    width: splashImage.width
    height: splashImage.height

//    Keys.enabled: true
//    Keys.forwardTo: keyhandler
    Item {
        focus: true
        id: keyhandler
        Keys.enabled: true
        Keys.onPressed: {
            console.log(event.key)
        }
    }


    property bool timeout: false

    Image {
        id: splashImage
        fillMode: Image.PreserveAspectFit
        source: "qrc:/res/load.png"
        width: 600
    }

//    Text {
//        id: textCtrl
//        text: qsTr("text")
//    }

    function delay(){
        visible = false;
    }

    Component.onCompleted: visible = true

}
