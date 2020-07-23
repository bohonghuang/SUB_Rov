#include "SendCommand.h"

SendCommand::SendCommand()
{
    head_1 = 0xAA;
    head_2 = 0x55;
    head_length = 16;

    deeplock = 0x01;
    directionlock =0x01;
    forward_backward =0x80;
    left_right =0x80;
    up_down =0x80;
    spin =0x80;

    oil =0x00;
    light =0x00;    
    camera =0x00;
    cloud =0x00;
    machine =0x00;

    startPi =0x00;
    draw = 0x00;

    keep_1 =0x00;
    keep_2 =0x00;
    status =0x00;
    check =0x00;


}
