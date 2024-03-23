#include "define.h"
#include "terminalControl.h"
#include "model.h"
#include "game.h"

void init()
{
    tc::setScreen(30, tc::transition(31) - 1);                     //设置终端大小 30X30的格子棋盘
    tc::cleanScreen();                                             //清屏
    tc::hideCursor();                                              //隐藏光标
}

void loop()
{
    struct SnakeHead *head = (struct SnakeHead *)malloc(sizeof(SnakeHead));     //初始化蛇头和蛇身
    struct SnakeBody *firstBody = (SnakeBody *)malloc(sizeof(SnakeBody));
    head->row = 1;                                                              //赋初值，第1行第3格的地方为蛇头，初始方向向右，初始长度2
    head->col = 3;
    head->colour = 15;
    head->dir = 'd';
    head->size = 2;

    firstBody->row = 1;                                                         //赋初值，第1行第2格，颜色红色
    firstBody->col = 2;
    firstBody->colour = 9;
    firstBody->next = NULL;
    head->next = firstBody;

    struct Food food = model::createFood(head);                                 //生成食物

    while (gm::running)
    {
        
        model::printFood(&food);                                                //打印食物和蛇
        model::printSnake(head);
        if(model::ateFood(head,&food))                                          //食物被吃
        {
            model::addBody(head,food.row,food.col,food.colour);                 //蛇身增长
            food = model::createFood(head);                                     //重新创建食物
        }
        model::snakeMove(head, model::dir);                                     //蛇移动
        
        if (!model::limitCheck(head))                                           //规则检查 蛇撞墙或撞自己时GAMEOVER
        {
            tc::cleanScreen();
            tc::moveTo(1, 1);
            std::cout <<"GAME OVER!!! LENGTH:" << head->size <<std::endl;
            std::cout << "PRESS ANY KEY TO EXIT" << std::endl;
            gm::commandQuit();
        }
    }
    model::freeSnake(head);                                                     //释放内存
}

void quit()                                                                     //复原终端
{
    tc::cleanScreen();
    tc::moveTo(1, 1);
    tc::resetColor();
    tc::showCursor();
}

int main()
{
    std::thread t(gm::keyEvent);                                                //新线程，用于监听键盘按键
    init();
    loop();
    t.join();                                                                   //等待线程执行结束（由于getchar()函数阻塞进程，需要按下任意键盘按键）
    quit();
    return 0;
}