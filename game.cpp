#include "game.h"
#include "model.h"

char gm::command;
bool gm::running = true;


char gm::getch()              //获取键盘按键值
{
    char c;
    struct termios old, cur;
    tcgetattr(0, &cur);
    old = cur;
    cfmakeraw(&cur);
    tcsetattr(0, 0, &cur);
    c = getchar();
    tcsetattr(0, 0, &old);
    return c;
}

void gm::keyEvent()             //键盘按键值判断，新线程执行此函数
{
    while (running)
    {
        command = getch();
        switch (command)
        {
        case 'q':
            commandQuit();
            break;
        case 'w':
            model::dir = 'w';
            break;
        case 'd':
            model::dir = 'd';
            break;
        case 's':
            model::dir = 's';
            break;
        case 'a':
            model::dir = 'a';
            break;
        default:
            break;
        }
    }
}

void gm::commandQuit()                 //退出循环函数，按下q时或者GAMEOVER时执行
{
    running = false;
}

