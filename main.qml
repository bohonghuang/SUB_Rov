import QtQuick 2.12
import QtQuick.Window 2.12

import "qml"
import "qml/View"
Item {
    id: root


    Splash{
        id: splashScreen
    }
    Loader {
        id: loader
        asynchronous: true
        source: "qrc:/qml/View/MainView.qml"
        active: false
        onLoaded: {
            timer.start()
        }
    }
    Connections {
        target: loader.item
    }

    Timer{
        id: timer
        interval: 500; running: false; repeat: false;
        onTriggered: {
            splashScreen.visible = false;
            loader.item.visible = true;
        }
    }

    Component.onCompleted: {
        //timer.start()
        loader.active = true
    }
}
//MainView{

//}

//Window {
//    visible:  true;
//}
