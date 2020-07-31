import QtQuick 2.0

Item {
    width: 40
    height: 40


    property alias img_source: img_flag.source
    property alias light_running: img_flag_animation_light.running
    property alias dark_running: img_flag_animation_dark.running

    Image {
        id: img_flag
        opacity: 0.5
        width: parent.width
        height: parent.height
        source: "../../resource/icon/flag/白字_P.png"

    }

    ParallelAnimation{
        id: img_flag_animation_light

        PropertyAnimation{
            target: img_flag
            property: "opacity"
            to: 1
            duration: 150
        }

        onStopped: {
            img_flag.opacity = 1
        }
    }
    ParallelAnimation{
        id: img_flag_animation_dark

        PropertyAnimation{
            target: img_flag
            property: "opacity"
            to: 0.5
            duration: 150
        }

        onStopped: {
            img_flag.opacity = 0.5
        }
    }

}
