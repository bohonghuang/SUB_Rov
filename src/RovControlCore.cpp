#include "RovControlCore.h"
#include "RovApplication.h"
#include <SocketManager.h>
#include <SendManager.h>

RovControlCore::RovControlCore(QObject *parent) : QObject(parent)
{

}

void RovControlCore::doTurnUp()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->ToUp();
}

void RovControlCore::doTurnDown()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->ToDown() ;
}

void RovControlCore::doStopUpDown()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->ToUpDownNormal();
}

void RovControlCore::do_Forward_Back_Change(double axist)
{
    int t = axist * 127 + 128;

    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->SetForwardOrBack(t);
}

void RovControlCore::do_Left_Right_Change(double axist)
{
    int t = axist * 127 + 128;

    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->SetLeftOrRight(t);
}


void RovControlCore::doSpinLeft()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->ToLeftSpin();
}

void RovControlCore::doSpinRight()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->ToRightSpin();
}

void RovControlCore::doStopSpin()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->ToSpinNormal();
}

void RovControlCore::doLockDeep()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnDeepLock();
}

void RovControlCore::doLockDirection()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnDirectionLock();
}



void RovControlCore::doTurnLight()
{

}

void RovControlCore::doTurnLightUp()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->TurnLightUp();
}

void RovControlCore::doTurnLightDown()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->TurnLightDown();
}

void RovControlCore::doTurnLightNormal()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->TurnNormalLight();
}

void RovControlCore::doCamputure()
{

}

void RovControlCore::doKeep5()
{
}

void RovControlCore::doRecord()
{
    if(rovApp()->getToolbox()
            ->getVideoManager()
            ->recording)
    {
        rovApp()->getToolbox()
            ->getVideoManager()
            ->startRecording();
    }
    else{
        rovApp()->getToolbox()
            ->getVideoManager()
            ->stopRecording();
    }
}

void RovControlCore::doCameraFocusing(double axit)
{
    if(axit > 0){
        doCameraFocusingToLarge();
    }
    else{
        doCameraFocusingToSmall();
    }
}

void RovControlCore::doCameraZooming(double axit)
{
    if(axit > 0){
        doCameraZoomingToLarge();
    }
    else{
        doCameraZoomingToSmall();
    }
}

void RovControlCore::doCameraFocusingToLarge()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnCameraFocusingToLarge();
}

void RovControlCore::doCameraFocusingToSmall()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnCameraFocusingToSmall();
}

void RovControlCore::doCameraZoomingToLarge()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnCameraZoomToLarge();
}

void RovControlCore::doCameraZoomingToSmall()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnCameraZoomToSmall();
}

void RovControlCore::doCameraNormal()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnCameraNormal();
}

void RovControlCore::doAddOil()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->AddOil();
}

void RovControlCore::doSubOil()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->SubOil();
}

void RovControlCore::doTurnCloud()
{

}

void RovControlCore::doTurnCloudUp()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->TurnCloudUp();
}

void RovControlCore::doTurnCloudDown()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->TurnCloudDown();
}

void RovControlCore::doTurnCloudCentral()
{
    rovApp()->getToolbox()->getSocketManager()->getSendManager()->TurnCloudCentral();
}

void RovControlCore::doTurnCloudNormal()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnCloudNormal();
}

void RovControlCore::doTurnMachineOpen()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnMachineOpen();
}

void RovControlCore::doTurnMachineClose()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnMachineClose();
}

void RovControlCore::doTurnMachineNormal()
{
    rovApp()->getToolbox()
            ->getSocketManager()
            ->getSendManager()
            ->TurnMachineNormal();
}







