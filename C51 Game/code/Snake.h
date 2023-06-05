#ifndef __SNAKsdE_H__
#define __SNAKsdE_H__
#include <REG52.H>
#include "ampire.h"

//蛇身体的坐标
typedef struct
{
    uchar x;
    uchar y;
} Pos;

typedef struct
{    
    Pos body[40]; //蛇身体各部分的坐标       
    char x_speed; //x方向上的速度
    char y_speed; //y方向上的速度   
    uchar Num;    //蛇身体的长度
    
} snake, *snake_ptr;


void initate_snake();  //初始化蛇的属性

void snake_movee();    //蛇的移动（身体各部分坐标的变化）

void snake_printf();   //显示蛇

void snake_controll(); //蛇的控制

void snack_clear();    //蛇尾的清理

int snack_collision(); //判断蛇是否撞墙


#endif
