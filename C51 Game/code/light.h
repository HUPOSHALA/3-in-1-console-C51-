#ifndef __Light_H__
#define __Light_H__
#include "ampire.h"

typedef struct  
{

    int x;                //灯的x坐标
    int y;                //灯的y坐标
    uchar state;          //灯的状态 1-亮  0-灭

}light;

extern uchar count;               //记录玩家的操作次数

void bulb_initate();//初始化16盏灯

void bulb_meassage();//右屏打印初始信息 左屏点亮所有16盏灯

void bulb_gameover();//灭灯游戏胜利打印相应的信息

void button_press(int x);//按下按键 对应按键的灯及其周围灯状态发生反转

void bulb_print(); //刷新显示灯泡的亮灭情况

uchar button_over();//游戏胜利条件

#endif