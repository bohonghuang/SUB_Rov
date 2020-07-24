import QtQuick 2.0
import QtGamepad 1.12

Item{
    id: padroot
    Gamepad {
        id: gamepad
        deviceId: GamepadManager.connectedGamepads.length >0 ?
                      GamepadManager.connectedGamepads[0] : -1


        //=====================灯控=========================//
        onButtonAChanged: {
            if(buttonA){
                console.log("A pressed")
                rovControl.doTurnLightDown()
            }
            else
                rovControl.doTurnLightNormal()
        }
        onButtonYChanged:  {
            if(buttonY){
                console.log("Y pressed")
                rovControl.doTurnLightUp()
            }
            else
                rovControl.doTurnLightNormal()
        }

        //===================机器手控制======================//
        onButtonXChanged: {
            if( buttonX ){
                rovControl.doTurnMachineClose()
            }
            else {
                rovControl.doTurnMachineNormal()
            }
        }
        onButtonBChanged: {
            if( buttonB )
                rovControl.doTurnMachineOpen()
            else{
                rovControl.doTurnMachineNormal()
            }
        }

        //=====================油控=========================//
        onButtonUpChanged: {
            if(buttonUp)
                rovControl.doAddOil()
        }
        onButtonDownChanged: {
            if(buttonDown)
                rovControl.doSubOil()
        }

        //====================云台控制========================//
        onButtonLeftChanged: {
            if(buttonLeft)
                rovControl.doTurnCloudDown()
            else{
                rovControl.doTurnCloudNormal()
            }
        }
        onButtonRightChanged: {
            if(buttonRight)
                rovControl.doTurnCloudUp()
            else{
                rovControl.doTurnCloudNormal()
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
                rovControl.doLockDeep()
            }

        }

        onButtonSelectChanged: {
            if( buttonStart ){
                rovControl.doLockDirection()
            }
        }


        //=====================水平旋转控制=========================//
        onButtonL1Changed: {
            if(buttonL1){
                rovControl.doSpinLeft()
            }
            else{
                rovControl.doStopSpin()
            }
        }

        onButtonR1Changed: {
            if(buttonL1){
                rovControl.doSpinRight()
            }
            else{
                rovControl.doStopSpin()
            }
        }

        //=====================升降控制=========================//
        onButtonL2Changed: {
            if(buttonL2){
                rovControl.doTurnDown()
            }
            else{
                rovControl.doStopUpDown()
            }
        }

        onButtonR2Changed: {
            if(buttonL2){
                rovControl.doTurnUp()
            }
            else{
                rovControl.doStopUpDown()
            }
        }

        //==============================================//
        //center
        onButtonL3Changed: {
            if(buttonL3) {
                videoManager.restartVideos();
            }
        }

        //center
        onButtonR3Changed: {
            if(buttonR3)
                grabImage();
        }

        onAxisLeftXChanged: {
            rovControl.do_Left_Right_Change(axisLeftX)
        }
        onAxisLeftYChanged: {
            rovControl.do_Forward_Back_Change(axisLeftY)
        }
        onAxisRightXChanged: {
            rovControl.doCameraFocusing(axisRightX)
        }
        onAxisRightYChanged: {
            rovControl.doCameraZooming(axisRightY)
        }

    }
}

