#ifndef __game_H__
#define __game_H__
#include <stdlib.h>

//食物的结构体
typedef struct
{
    uchar x;
    uchar y;
    uchar score; //这里的分数可以不写在这里，而是作为全局变量
} food;



void food_initate();                                           //食物初始化
void food_display();                                           //显示食物
void food_touch();                                             //判断食物是否被吃到
void score_display();                                          //显示分数
int game_over();                                               //游戏结束判定条件
void print_gamemessage();                                      //打印游戏中不会改变的信息

#endif