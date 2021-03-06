import QtQuick 2.0

Rectangle {
    id: body_dir_item
    width: 160
    height: 55
    color: "#00000000"
    property bool isUp: false

        Repeater {
            id: body_dir_repeater
            model: 11

            Image {
                x: rovControl.getRovStateX(index)
                y: rovControl.getRovStateY(index)
                source: rovControl.getRovStateSource(index)
            }
        }
        Connections {
            target: rovControl
            function onOnUp() {
//                console.log("UP");
                body_dir_repeater.itemAt(5).source = rovControl.getRovStateLightSource(5);
            }
            function onOnDown() {
                body_dir_repeater.itemAt(8).source = rovControl.getRovStateLightSource(8);
            }
            function onOnLeft() {
                body_dir_repeater.itemAt(6).source = rovControl.getRovStateLightSource(6);
            }
            function onOnRight() {
                body_dir_repeater.itemAt(7).source = rovControl.getRovStateLightSource(7);
            }
            function onOnForward() {
                body_dir_repeater.itemAt(9).source = rovControl.getRovStateLightSource(9);
            }
            function onOnBack() {
                body_dir_repeater.itemAt(10).source = rovControl.getRovStateLightSource(10);
            }
            function onOnLSpin() {
                body_dir_repeater.itemAt(1).source = rovControl.getRovStateLightSource(1);
            }
            function onOnRSpin() {
                body_dir_repeater.itemAt(2).source = rovControl.getRovStateLightSource(2);
            }
            function onOnUDN() {
                body_dir_repeater.itemAt(5).source = rovControl.getRovStateSource(5);
                body_dir_repeater.itemAt(8).source = rovControl.getRovStateSource(8);
            }
            function onOnLRN() {
                body_dir_repeater.itemAt(6).source = rovControl.getRovStateSource(6);
                body_dir_repeater.itemAt(7).source = rovControl.getRovStateSource(7);
            }
            function onOnSN() {
                body_dir_repeater.itemAt(1).source = rovControl.getRovStateSource(1);
                body_dir_repeater.itemAt(2).source = rovControl.getRovStateSource(2);
            }
            function onOnFBN() {
                body_dir_repeater.itemAt(9).source = rovControl.getRovStateSource(9);
                body_dir_repeater.itemAt(10).source = rovControl.getRovStateSource(10);

            }

        }

}
