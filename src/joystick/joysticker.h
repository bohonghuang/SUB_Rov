#ifndef JOYSTICKER_H
#define JOYSTICKER_H

#include <QString>
#include <QLibrary>
#include "Windows.h"
#include "mmsystem.h"
#include "WinUser.h"

// 手柄号
#define JSX JOYSTICKID1

// DLL库函数声明
typedef int (*mPrototype) (HWND, UINT, UINT, BOOL);
extern mPrototype qJoySetCapture;

typedef void (*mPrototype_1) (UINT);
extern mPrototype_1 qJoyReleaseCapture;

typedef void (*mPrototype_2) (UINT, LPJOYINFOEX);
extern mPrototype_2 qJoyGetPosEx;

typedef void (*mPrototype_0) (UINT, LPJOYINFO);
extern mPrototype_0 qJoyGetPos;

typedef void (*mPrototype_3) (UINT, LPUINT);
extern mPrototype_3 qJoyGetThreshold;

typedef void (*mPrototype_4) (UINT, LPJOYCAPS, UINT);
extern mPrototype_4 qJoyGetDevCaps;

typedef void (*mPrototype_5) (void);
extern mPrototype_5 qJoyGetNumDevs;


// joystick 外部窗口

void openJoy();
struct joyinfoex_tag joyRead_row();



#endif // JOYSTICKER_H
