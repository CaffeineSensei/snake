#include "terminalControl.h"
#include "define.h"


//将光标移动到row行col列
void tc::moveTo(int row, int col)
{
    std::cout<<CSI<<row<<";"<<col<<'H';
}

//设置前景色 id颜色编号
void tc::setForeColor(int id)
{
    std::cout<<CSI<<"38;5;"<<id<<'m';
}

//设置背景色 id颜色编号
void tc::setBackColor(int id)
{
    std::cout<<CSI<<"48;5;"<<id<<'m';
}

//清屏
void tc::cleanScreen()
{
    std::cout<<CSI<<"2J";
}

//重置颜色
void tc::resetColor()
{
    std::cout<<CSI<<"0m";
}

//隐藏光标
void tc::hideCursor()
{
    std::cout<<CSI<<"?25l";
}

//显示光标
void tc::showCursor()
{
    std::cout<<CSI<<"?25h";
}

//转化格子列数，由于终端3列1行才为一个方格子
int tc::transition(int chessBoardCol)
{
    return 3*chessBoardCol - 2;
}

//设置终端窗口大小 row行col列
void tc::setScreen(int row, int col)
{
    std::cout<<CSI<<"8;"<<row<<";"<<col<<'t';
}
