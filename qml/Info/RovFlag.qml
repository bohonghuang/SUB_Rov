import QtQuick 2.0

Item {
    height: 40
    width: 40

    property alias imgSource: flag_img.source
    signal lighting
    signal darking

    onLighting: {
        flag_light.start()

    }
    onDarking: {
        flag_dark.start()
    }

    Image {
        id: flag_img
        opacity: 0.3
        source: ""
        anchors.fill: parent
    }

    ParallelAnimation {
        id: flag_light
        PropertyAnimation {
            target: flag_img
            property: "opacity"
            to: 1
            duration: 150
        }
        onStopped: {
            flag_img.opacity = 1
        }
    }
    ParallelAnimation {
        id: flag_dark
        PropertyAnimation {
            target: flag_img
            property: "opacity"
            to: 0.3
            duration: 150
        }
        onStopped: {
            flag_img.opacity = 0.3
        }
    }

}
