#include "joysticker.h"

static joyinfoex_tag now_act;


// 加载多媒体库
QLibrary mylib("Winmm.dll");

// 解析游戏杆捕获函数joySetCapture
mPrototype qJoySetCapture = (mPrototype) mylib.resolve("joySetCapture");

// 返回游戏杆的位置及按钮活动函数
mPrototype_0 qJoyGetPos = (mPrototype_0) mylib.resolve("joyGetPos");

// 游戏杆数获取函数
mPrototype_1 qJoyReleaseCapture = (mPrototype_1) mylib.resolve("joyReleaseCapture");

// 返回游戏杆的位置及按钮活动函数 ???
mPrototype_2 qJoyGetPosEx = (mPrototype_2) mylib.resolve("joyGetPosEx");

// 读取操纵杆移动阈值
mPrototype_3 qJoyGetThreshold = (mPrototype_3) mylib.resolve("joyGetThreshold");

// 获取操纵杆的属性信息，咦结构体JoyCaps接收
mPrototype_4 qJoyGetDevCaps = (mPrototype_4) mylib.resolve("joyGetDevCapsW");

// 有多少个游戏杆可以用
mPrototype_5 qJoyGetNumDevs = (mPrototype_5) mylib.resolve("joyGetNumDevs");

void openJoy() {
    JOYCAPS joycaps;
    qJoyGetDevCaps(JSX, &joycaps, sizeof(joycaps) );

}

struct joyinfoex_tag joyRead_row() {
    now_act.dwSize = sizeof( joyinfoex_tag );
    now_act.dwFlags = (int) JOY_RETURNBUTTONS;
    qJoyGetPosEx(JSX, &now_act);

    return now_act;
}
