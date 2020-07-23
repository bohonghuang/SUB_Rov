import QtQuick 2.0
import QtGamepad 1.12
import Rov.JoyManager 1.0

Item{
    id:root
    Gamepad {
        id: gamepad
        deviceId: GamepadManager.connectedGamepads.length >0 ?
                      GamepadManager.connectedGamepads[0] : -1
    }
}

