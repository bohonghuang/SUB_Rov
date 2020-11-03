import QtQuick 2.0
import QtGamepad 1.12

Item {
//    id: padroot
        Gamepad {
//            id: gamepad
//            deviceId: GamepadManager.connectedGamepads.length >0 ?
//                          GamepadManager.connectedGamepads[0] : -1


            //=====================灯控=========================//
            onButtonAChanged: {
                if(buttonA){
                    console.log("A pressed")
                    rovControl.downLight()
                }
                else
                    rovControl.normalLight()
            }
            onButtonYChanged:  {
                if(buttonY){
                    console.log("Y pressed")
                    rovControl.upLight()
                }
                else
                    rovControl.normalLight()
            }

            //===================机器手控制======================//
            onButtonXChanged: {
                if( buttonX ){
                    rovControl.closeManipulator()
                }
                else {
                    rovControl.normalManipulator()
                }
            }
            onButtonBChanged: {
                if( buttonB )
                    rovControl.openManipulator()
                else{
                    rovControl.normalManipulator()
                }
            }

            //=====================油控=========================//
            onButtonUpChanged: {
                if(buttonUp)
                    rovControl.addOil()
            }
            onButtonDownChanged: {
                if(buttonDown)
                    rovControl.subOil()
            }

            //====================云台控制========================//
            onButtonLeftChanged: {
                if(buttonLeft)
                    rovControl.downCloud()
                else{
                    rovControl.normalCloud()
                }
            }
            onButtonRightChanged: {
                if(buttonRight)
                    rovControl.upCloud()
                else{
                    rovControl.normalCloud()
                }
            }


            onButtonCenterChanged: {
                if(buttonCenter){
                    console.log("Button ceter press")
                }
            }

            //===================深度控制锁定控制=======================//
            onButtonStartChanged: {
                if( buttonStart ){
                    rovControl.lockDeep()
                }

            }

            onButtonSelectChanged: {
                console.log("Seleted button")
                if( buttonStart ){
                    rovControl.lockDirection()
                }
            }


            //=====================水平旋转控制=========================//
            onButtonL1Changed: {
                if(buttonL1){
                    rovControl.spinLeft()
                }
                else{
                    rovControl.stopSpin()
                }
            }

            onButtonR1Changed: {
                if(buttonL1){
                    rovControl.spinRight()
                }
                else{
                    rovControl.stopSpin()
                }
            }

            //=====================升降控制=========================//
            onButtonL2Changed: {
                if(buttonL2){
                    rovControl.down()
                }
                else{
                    rovControl.stopUpDown()
                }
            }

            onButtonR2Changed: {
                if(buttonL2){
                    rovControl.up()
                }
                else{
                    rovControl.stopUpDown()
                }
            }

            //==============================================//
            //center
            onButtonL3Changed: {
                if(buttonL3) {
                    videoManager.restartVideo()
                }
            }

            //center
            onButtonR3Changed: {
                if(buttonR3)
                    rovControl.grabImage()
            }

            onAxisLeftXChanged: {
                rovControl.leftRight(axisLeftX)
            }
            onAxisLeftYChanged: {
                rovControl.forwardBack(axisLeftY)
            }
            onAxisRightXChanged: {
                if( axisRightX > 0 ){
                    rovControl.enlargeFocus()
                }
                else if( axisRightX < 0 ){
                    rovControl.reduceFocus()
                }
                else {
                    rovControl.normalCamera()
                }
            }
            onAxisRightYChanged: {
                if( axisRightY > 0 ){
                    rovControl.enlargeZoom()
                }
                else if( axisRightY < 0 ){
                    rovControl.reduceZoom()
                }
                else {
                    rovControl.normalCamera()
                }
            }

        }
}
