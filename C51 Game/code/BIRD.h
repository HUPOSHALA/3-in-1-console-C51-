#ifndef __Bird_H__
#define __Bird_H__
#include "Menu.h"

typedef struct
{
    uchar x;          //小鸟的x坐标   恒定不变
    int y;            //小鸟的y坐标
    uchar down_speed; //小鸟的下坠速度
    uchar score;      //小鸟的得分
} bird_struct;


typedef struct
{
    int x;         //柱子的x坐标
    uchar gap_y;     //柱子的缺口y坐标
    uchar x_speed;   //柱子的x方向上移动速度
    uchar pass;      //柱子是否被通过
}pillar_struct;


extern bird_struct xdata bird;          //声明小鸟

extern uchar code gap_position[5];       //缺口y坐标数组

void bird_initate(); //初始化小鸟的属性

void bird_control(); //小鸟的控制

void bird_message(); //打印游戏相关信息

int bird_collison(); //判断小鸟的触碰

void bird_gameover(); //小鸟游戏结束信息的打印

void pillar_initate();//初始化柱子坐标

void pillar_reset();//柱子移动到最左端时，重置柱子坐标和缺口

void pillar_move();//柱子的移动同时清除柱子原本位置

void pillar_print();//柱子的显示

void bird_score(); //得分设置 每次通过一根柱子加一分


#endif
