#include "keyflag.h"

keyflag::keyflag()
{

}

void keyflag::EnterKey(Qt::Key k){
    /*
     * Num_1, Num_2,
        Shift, Ctrl,
        W, S, A, D, J, K, Q, E, U, I, O, P,
        Left_Semicolon, Right_Semicolon,
        */
    switch (k) {
    case Qt::Key_1:
        KeyQueue.push(KeyEnterCode::Key_Num_1);break;
    case Qt::Key_2:
        KeyQueue.push(KeyEnterCode::Key_Num_2);break;
    case Qt::Key_W:
        KeyQueue.push(KeyEnterCode::Key_W);break;
    case Qt::Key_S:
        KeyQueue.push(KeyEnterCode::Key_S);break;
    case Qt::Key_A:
        KeyQueue.push(KeyEnterCode::Key_A);break;
    case Qt::Key_D:
        KeyQueue.push(KeyEnterCode::Key_D);break;
    case Qt::Key_J:
        KeyQueue.push(KeyEnterCode::Key_J);break;
    case Qt::Key_K:
        KeyQueue.push(KeyEnterCode::Key_K);break;
    case Qt::Key_Q:
        KeyQueue.push(KeyEnterCode::Key_Q);break;
    case Qt::Key_E:
        KeyQueue.push(KeyEnterCode::Key_E);break;
    case Qt::Key_U:
        KeyQueue.push(KeyEnterCode::Key_U);break;
    case Qt::Key_I:
        KeyQueue.push(KeyEnterCode::Key_I);break;
    case Qt::Key_O:
        KeyQueue.push(KeyEnterCode::Key_O);break;
    case Qt::Key_P:
        KeyQueue.push(KeyEnterCode::Key_P);break;
    case Qt::Key_Semicolon:
        KeyQueue.push(KeyEnterCode::Key_Semicolon);break;

    default:
        break;
    }

}
