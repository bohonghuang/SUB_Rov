#ifndef RECEIVECOMMAND_H
#define RECEIVECOMMAND_H

#include <QObject>

class ReceiveCommand{
    public:
    //第1、2字节：电压 第一字节表示整数部分，第二字节小数部分（两位小数）
    quint8 electric_1;
    quint8 electric_2;
    //第3、4字节：舱外水温度 第一字节表示整数部分，第二字节小数部分
    quint8 temperatureOutside_1;
    quint8 temperatureOutside_2;
    //第5、6字节：舱内CPU内核温度 第一字节表示整数部分，第二字节小数部分
    quint8 temperatureInside_1;
    quint8 temperatureInside_2;
    //第 7、8、9字节：深度值高8位 中8位 低8位（0~16777215cm）精确到厘米
    quint8 deep_1;
    quint8 deep_2;
    quint8 deep_3;
    //第 10、11 字节： 航向角（Yaw）  【高8位】记为YawH 【低8位】记为YawL
    quint8 yaw_1;
    quint8 yaw_2;
    //第 12、13 字节：俯仰角（Pitch）【高8位】记为PitchH 【低8位】记为PitchL
    quint8 pitch_1;
    quint8 pitch_2;
    //第 14、15 字节：横滚角（Roll）【高8位】记为RollH 【低8位】记为RollL
    quint8 roll_1;
    quint8 roll_2;
    //第 16 字节：航行速度（0~255）单位dm/s (0.1~25.5m/s)
    quint8 speed;
    /// 第 17 字节：设备状态标志，1代表正常，0代表故障
    /// 1、深度传感器故障/正常。2、串口设备。3、电源监测设备。
    /// 4、指南针。5、聚焦到达极限/聚焦未到底。6、变焦。
    /// 7、云台角度到达限制/未到限制。8、机械臂角度达到限制/未到限制。
    quint8 deviceStatusTag;
    /// 第 18 字节：本设备的启动停止位（0x01，代表本设备为启动状态；0x02 或 0x00，代表本设备为停止状态；
    /// 则上位机 【P】图标 需要对应）
    quint8 status;
    // 第19、20字节：电流第一字节表示整数部分，第二字节小数部分（两位小数）
    quint8 current_1;
    quint8 current_2;
    // 校验字 1
    quint8 head_1;
    // 校验字 2
    quint8 head_2;
    // 校验字 3
    quint8 head_3;
    // 保留字 1
    quint8 keep_1;
    // 保留字 2
    quint8 keep_2;
    // 校验字
    quint8 check;

    public:
    ReceiveCommand();


};
#endif //RECEIVECOMMAND_h
