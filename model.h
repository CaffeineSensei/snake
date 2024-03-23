#pragma once

#include "define.h"

struct Food
{
    int row;
    int col;
    int colour;
};


struct SnakeBody
{
    int row;
    int col;
    int colour;
    struct SnakeBody* next;
};

struct SnakeHead
{
    int row;
    int col;
    int colour;
    int size;
    char dir;
    struct SnakeBody* next;

};

namespace model
{
    extern char dir;
    void addBody(struct SnakeHead *head,int row,int col,int colour);
    void snakeMove(struct SnakeHead *head ,char dir);
    void printSnake(struct SnakeHead *head);
    void freeSnake(struct SnakeHead *head);
    bool limitCheck(struct SnakeHead *head);
    struct Food createFood(struct SnakeHead *head);
    bool overlapCheck(struct SnakeHead *head,int row,int col);
    void printFood(struct Food *food);
    bool ateFood(struct SnakeHead *head,struct Food *food);
} // namespace model
