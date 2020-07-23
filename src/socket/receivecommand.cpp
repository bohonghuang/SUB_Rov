#include "ReceiveCommand.h"

ReceiveCommand::ReceiveCommand(){

    electric_1 = 0x00;
    electric_2 = 0x00;
    temperatureInside_1 = 0x00;
    temperatureInside_2 = 0x00;
    temperatureOutside_1 = 0x00;
    temperatureOutside_2 = 0x00;
    deep_1 = 0x00;
    deep_2 = 0x00;
    deep_3 = 0x00;
    yaw_1 = 0x00;
    yaw_2 = 0x00;
    roll_1 = 0x00;
    roll_2 = 0x00;
    pitch_1 = 0x00;
    pitch_2 = 0x00;

    speed = 0x00;
    deviceStatusTag = 0x00;

    current_1 = 0x00;
    current_2 = 0x00;

    status = 0x00;

    keep_1 = 0x00;
    keep_2 = 0x00;
}
