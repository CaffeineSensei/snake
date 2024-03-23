#include "model.h"
#include "terminalControl.h"

using namespace std::chrono_literals;
int colour[7] = {9,208,11,10,14,12,13};                                         //颜色数组，对应为红 橙 黄 绿 青 蓝 紫

char model::dir = 'd';                                                          //蛇移动方向，由键盘按键传值

void model::addBody(struct SnakeHead *head, int row, int col, int colour)       //增加蛇身，吃到食物判定时调用
{
    struct SnakeBody *newBody = (SnakeBody *)malloc(sizeof(SnakeBody));
    struct SnakeBody *firstBody = head->next;
    newBody->row = row;
    newBody->col = col;
    newBody->colour = colour;
    head->next = newBody;
    newBody->next = firstBody;
    head->size++;

}

void model::snakeMove(struct SnakeHead *head, char dir)                         //蛇移动，传入的方向值与蛇头方向属性相反时保持原来方向，否则改变方向，同时将移动后的位置参数逐一向后传递
{
    struct SnakeBody *firstBody = head->next;
    int currentRow;
    int currentCol;
    int tempRow = head->row;
    int tempCol = head->col;

    switch (dir)
    {
    case 'd':
        if (head->dir != 'a')
        {
            head->dir = dir;
            head->col++;
        }
        else
        {
            head->col--;
        }
        break;
    case 's':
        if (head->dir != 'w')
        {
            head->dir = dir;
            head->row++;
        }
         else
        {
            head->row--;
        }
        break;
    case 'a':
        if (head->dir != 'd')
        {
            head->dir = dir;
            head->col--;
        }
         else
        {
            head->col++;
        }
        break;
    case 'w':
        if (head->dir != 's')
        {
            head->dir = dir;
            head->row--;
        }
         else
        {
            head->row++;
        }
        break;
    default:
        break;
    }
    while (firstBody != NULL)
    {
        currentRow = firstBody->row;
        currentCol = firstBody->col;
        firstBody->row = tempRow;
        firstBody->col = tempCol;
        tempRow = currentRow;
        tempCol = currentCol;
        firstBody = firstBody->next;
    }
    
}

void model::printSnake(struct SnakeHead *head)                      //打印蛇
{
    struct SnakeBody *current = head->next;
    tc::moveTo(head->row,tc::transition(head->col));
    tc::setBackColor(head->colour);
    std::cout << "   ";
    tc::resetColor();
    while (current != NULL)
    {
        tc::moveTo(current->row,tc::transition(current->col));
        tc::setBackColor(current->colour);
        std::cout << "   ";
        tc::resetColor();
        current = current->next;
    }
    std::cout << std::flush;
    std::this_thread::sleep_for(200ms);
    tc::cleanScreen();
}

void model::freeSnake(struct SnakeHead *head)                       //释放蛇内存
{
    struct SnakeBody *current = head->next;
    struct SnakeBody *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(head);
    head = NULL;
    
}

bool model::limitCheck(SnakeHead *head)                             //规则检查
{
    
    if (head->row<=0 || head->row > 30 || head->col <= 0 || head->col > 30 || head->size > 900) //撞墙检测
    {
        return false;
    }
    struct SnakeBody *firstBody = head->next;
    while (firstBody != NULL)
    {
        if ((head->row == firstBody->row)&&(head->col == firstBody->col))                   //撞身体检测
        {
            return false;
        }
        firstBody = firstBody->next;
    }
    return true;
}

Food model::createFood(SnakeHead *head)                             //生成食物
{
    srand(time(0));
    int row;
    int col;
    do
    {
        row = (rand() % 30) + 1;                                    //赋随机值（1～30）
        col = (rand() % 30) + 1;
    } while (!overlapCheck(head,row,col));                          //生成的食物合理性判断，不合理就继续赋值
    struct Food food;
    food.row = row;
    food.col = col;
    food.colour = colour[rand()%7];
    return food;
}

bool model::overlapCheck(SnakeHead *head, int row, int col)         //重叠检查，传入值如果正好是蛇身上则为false
{
    if ((head->row == row)&&(head->col == col))
    {
        return false;
    }
    struct SnakeBody *firstBody = head->next;
    while (firstBody != NULL)
    {
        if ((firstBody->row == row)&&(firstBody->col == col))
        {
            return false;
        }
        firstBody = firstBody->next;
    }
    return true;
}

void model::printFood(Food *food)                                   //打印食物
{
    tc::moveTo(food->row,tc::transition(food->col));
    tc::setBackColor(food->colour);
    std::cout << "   ";
    tc::resetColor();
    std::cout << std::flush;
}

bool model::ateFood(SnakeHead *head, Food *food)                    //吃到食物检查，蛇头跟食物重合时为true
{
    
    if ((head->row == food->row)&&(head->col == food->col))
    {
        return true;
    }
    return false;
}
