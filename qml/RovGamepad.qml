import QtQuick 2.0
import QtGamepad 1.12

Item {
//    id: padroot
    property bool gamepadConnected: tgamepad.connected
    property var gamepadID: tgamepad.deviceId
        Gamepad {
            id: tgamepad
//            deviceId: GamepadManager.connectedGamepads.length >0 ?
//                          GamepadManager.connectedGamepads[0] : -1

            onButtonStartChanged: {
                if( buttonStart ){
                    rovControl.turnDeivce()
                }
            }

            //===================== Oil =========================//
            onButtonAChanged: {
                if(buttonA){
                    console.log("A pressed")
                    rovControl.subOil()
                }
            }
            onButtonYChanged:  {
                if(buttonY){
                    console.log("Y pressed")
                    rovControl.addOil()
                }
            }

            //=================== Light ======================//
            onButtonXChanged: {
                if( buttonX ){
                    rovControl.downLight()
                }
                else {
                    rovControl.normalLight()
                }
            }
            onButtonBChanged: {
                if( buttonB )
                    rovControl.upLight()
                else{
                    rovControl.normalLight()
                }
            }

            //===================== Focus =========================//
            onButtonUpChanged: {
                if(buttonUp)
                    rovControl.enlargeFocus()
                else
                    rovControl.normalCamera()
            }
            onButtonDownChanged: {
                if(buttonDown)
                    rovControl.reduceFocus()
                else
                    rovControl.normalCamera()
            }

            //==================== Zoom ========================//
            onButtonLeftChanged: {
                if(buttonLeft)
                    rovControl.enlargeZoom()
                else{
                    rovControl.normalCamera()
                }
            }
            onButtonRightChanged: {
                if(buttonRight)
                    rovControl.reduceZoom()
                else{
                    rovControl.normalCamera()
                }
            }


            onButtonCenterChanged: {
                if(buttonCenter){
                    console.log("Button ceter press")
                }
            }

            //=================== lock/unlock =======================//
            onButtonL3Changed: {
                console.log("Button L3");
                if( buttonL3 ) {
                    rovControl.lockDirection()
                }
            }

            onButtonR3Changed:  {
                console.log("Button R3")
                if( buttonR3  ){
                    rovControl.lockDeep()
                }
            }


            //===================== Cloud =========================//
            onButtonL1Changed: {
                if(buttonL1){
                    rovControl.upCloud()
                }
                else{
                    rovControl.normalCloud()
                }
            }

            onButtonL2Changed: {
                if(buttonL2){
                    rovControl.downCloud()
                }
                else{
                    rovControl.normalCloud()
                }
            }

            //===================== Manipulator =========================//
            onButtonR1Changed: {
                if(buttonR1){
                    rovControl.openManipulator()
                }
                else{
                    rovControl.normalManipulator()
                }
            }

            onButtonR2Changed: {
                if(buttonR2){
                    rovControl.closeManipulator()
                }
                else{
                    rovControl.normalManipulator()
                }
            }

            //==============================================//

            onAxisLeftXChanged: {
                rovControl.leftRight(axisLeftX)
            }
            onAxisLeftYChanged: {
                rovControl.forwardBack(axisLeftY)
            }
            // 0 - 255
            onAxisRightXChanged: {
                if( axisRightX > 0 ){
                    rovControl.spinRight()
                }
                else if( axisRightX < 0 ){
                    rovControl.spinLeft()
                }
                else {
                    rovControl.stopSpin()
                }
            }
            onAxisRightYChanged: {
                if( axisRightY > 0 ){
                    rovControl.up()
                }
                else if( axisRightY < 0 ){
                    rovControl.down()
                }
                else {
                    rovControl.stopUpDown()
                }
            }

        }
}
