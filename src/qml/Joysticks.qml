import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 600
    property int currentJoystick: 0
    property var maxCurrent: getMaxCurrent()

    ColumnLayout{
            spacing: 5
            anchors.margins: 10
            anchors.fill: parent

            ComboBox{
                id: joysticks
                Layout.fillWidth: true
                model: QJoysticks.deviceNames
                currentIndex: maxCurrent
                onCurrentIndexChanged: generateJoystickWidgets( currentIndex )
            }

            GroupBox{
                ColumnLayout{
                    Repeater{
                        id: axes
                        delegate: ProgressBar{
                            id: progressBar
                            from: -100
                            to: 100
                            Layout.fillWidth: true

                            value: 0
                            Behavior on value {NumberAnimation{}}

                            Connections {
                                target: QJoysticks
                                onAxisChanged:{
                                    if( currentJoystick === maxCurrent &&index === axis){
                                        //progressBar.value = QJoysticks.getAxis(js, index) * 100
                                        joyManager.handle_joystick_aciton_axis(index, QJoysticks.getAxis(maxCurrent, index))

                                    }

                                }
                            }
                        }
                    }
                }
            }

            GroupBox{
                title: qsTr("Buttons")
                Layout.fillWidth: true
                Layout.fillHeight: true

                GridLayout {
                    rows: 6
                    rowSpacing: 5
                    columnSpacing: 5
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    flow: GridLayout.TopToBottom

                    Repeater {
                        id: buttons
                        delegate: CheckBox{
                            enabled: false
                            Layout.fillWidth: true
                            text: qsTr("Button %1").arg(index)

                            Connections{
                                target: QJoysticks
                                onButtonChanged:{
                                    if( currentJoystick === js && button === index){
                                        //checked = QJoysticks.getButton(js, index)

                                        joyManager.handle_joystick_aciton_button(index, QJoysticks.getButton(maxCurrent, index))
                                    }
                                }
                            }
                        }
                    }
                }
            }

            GroupBox {
                title: qsTr ("POVs")
                Layout.fillWidth: true
                Layout.fillHeight: true

                ColumnLayout {
                    spacing: 5
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    //
                    // Generate a spinbox for each joystick POV
                    //
                    Repeater {
                        id: povs
                        delegate: SpinBox {
                            enabled: false
                            from: -1
                            to: 360
                            value: -1
                            Layout.fillWidth: true

                            //
                            // React to QJoystick signals
                            //
                            Connections {
                                target: QJoysticks
                                onPovChanged: {
                                    if (currentJoystick === js && pov === index)
                                        value = QJoysticks.getPOV (js, index)

                                    joyManager.handle_joystick_aciton_povs(QJoysticks.getPOV (js, index))
                                }
                            }
                        }
                    }
                }
            }


    }

    function generateJoystickWidgets(id){
        /* Clear the joystick indicators */
        axes.model = 0
        povs.model = 0
        buttons.model = 0

        /* Change the current joystick id */
        currentJoystick = id

        /* Get current joystick information & generate indicators */
        if (QJoysticks.joystickExists (id)) {
            axes.model = QJoysticks.getNumAxes (id)
            povs.model = QJoysticks.getNumPOVs (id)
            buttons.model = QJoysticks.getNumButtons (id)
        }

        /* Resize window to minimum size */
        width = minimumWidth
        height = minimumHeight
    }

    function getMaxCurrent(){
        var count = 0;
        var names = QJoysticks.deviceNames;

        for( var p of names ){
            count ++;
        }

        return count - 1;
    }


}


