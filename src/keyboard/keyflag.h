#ifndef KEYFLAG_H
#define KEYFLAG_H

#include <queue>
#include <QKeyEvent>
using namespace std;
enum KeyEnterCode{
      Key_Num_1, Key_Num_2,
        Key_Shift, Key_Ctrl,
        Key_W, Key_S, Key_A, Key_D, Key_J, Key_K, Key_Q, Key_E, Key_U, Key_I, Key_O, Key_P,
        Key_Semicolon
};

class keyflag
{
public:
    queue<KeyEnterCode> KeyQueue;
public:
    keyflag();
    void EnterKey(Qt::Key);
};

#endif // KEYFLAG_H
