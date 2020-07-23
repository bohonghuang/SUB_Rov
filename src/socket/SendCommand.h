#ifndef SENDCOMMAND_H
#define SENDCOMMAND_H

#include <QByteArray>

class SendCommand
{
    //很多的成员
    //byte = quint8 8个字节
public:
    //第1、2字节：包头位
    quint8 head_1;
    quint8 head_2;
    //第3字节：数据长度位（不包括包头、自身的数据长度位和校验位，即为16）
    quint8 head_length;
    //第4字节：0x01表示深度锁定，0x02表示人工控制
    quint8 deeplock;
    //第5字节：0x01表示方向锁定，0x02表示随水动（可指定默认值）
    quint8 directionlock;
    //第6字节：摇杆模拟量 前后状态（0~255）即摇杆居中时为128（即停止）
    quint8 forward_backward;
    //第7字节：摇杆模拟量 左右状态（0~255）即摇杆居中时为128（即停止）
    quint8 left_right;
    //第8字节：机器人垂直运动：0x01表示向上，0x02表示向下，0x00表示不动作（默认）
    quint8 up_down;
    //第9字节：机器人旋转：0x01表示左旋，0x02表示右旋，0X00表示不动作（默认）
    quint8 spin;
    //第10字节：0x00~0xff (0~255) 表示的油门大小：4档位可调，LB加档，LT减档，可分别设置4个档位油门大小 【不用】
    quint8 oil;
    //第11字节：灯的亮度控制，0x01表示变亮，0x02表示变暗，0x00表示不动作（默认）
    quint8 light;
    //第12字节：摄像头焦距控制，0x01表示聚焦，0x02表示变放焦， 0x11表示放大，0x12表示缩小，0x00表示不动作（默认）
    quint8 camera;
    //第13字节：云台转动，0x01表示向上，0x02表示向下，0x03表示归中，0x00表示不动作（默认）
    quint8 cloud;
    //第14字节：机械手动作，0x01表示张开，0x02表示关闭，0x00表示不动作（默认）
    quint8 machine;
    //第15字节：树莓派开启位，若开机发送0x01给MCU，0x00为默认（树莓派server.py中自动发送）
    quint8 startPi;
    //第16字节：吸取器动作，0x01表示吸取，0x02表示关闭，0x00表示不动作（默认）
    quint8 draw;
    //第17、18字节：保留
    quint8 keep_1;
    quint8 keep_2;
    //第19字节：0x00 默认 0x01表示启动， 0x02表示停止
    quint8 status;
    quint8 check;

public:
    SendCommand();
};

#endif // SENDCOMMAND_H
