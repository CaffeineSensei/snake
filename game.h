#pragma once
#include "define.h"

#define KEY_Q 'q'
#define KEY_W 'w'
#define KEY_A 'a'
#define KEY_S 's'
#define KEY_D 'd'

namespace gm
{
    extern char command;
    extern bool running;
    char getch();
    void keyEvent();
    void commandQuit();
} // namespace gm
