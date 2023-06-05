#include "BIRD.h"

bird_struct xdata bird; //创建小鸟

pillar_struct xdata pillar[3]; //创建柱子的结构体数组

uchar code gap_position[5] = {8, 16, 24, 32, 40}; //柱子的缺口y坐标数组

//初始化小鸟的属性
void bird_initate()
{
    bird.x = 8;          //小鸟在x方向上不会移动的
    bird.y = 32;         //小鸟初始在中间的位置
    bird.down_speed = 2; //小鸟的下坠速度为2格

    //初始化分数下标
    score_bit = 0;
    score_ten = 0;

    bird.score = 0; //初始化游戏的得分
}

//初始化柱子坐标
void pillar_initate()
{
    //第一根柱子初始化
    pillar[0].x = 30;
    pillar[0].gap_y = gap_position[rand() % 5];
    pillar[0].x_speed = 1;
    pillar[0].pass = 0;

    //第二根柱子初始化
    pillar[1].x = 46;
    pillar[1].gap_y = gap_position[rand() % 5];
    pillar[1].x_speed = 1;
    pillar[1].pass = 0;

    //第三根柱子初始化
    pillar[2].x = 62;
    pillar[2].gap_y = gap_position[rand() % 5];
    pillar[2].x_speed = 1;
    pillar[2].pass = 0;
}

//柱子移动到最左端时，重置柱子坐标和缺口
void pillar_reset()
{

    if (pillar[0].x <= 0)
    {
        pillar[0].x = 62;
        pillar[0].gap_y = gap_position[rand() % 5]; //随机生成缺口位置，缺口位置生成有限制，不会在底端和顶端生成
        pillar[0].x_speed = 1;
        pillar[0].pass = 0;
    }

    if (pillar[1].x <= 0)
    {
        pillar[1].x = 62;
        pillar[1].gap_y = gap_position[rand() % 5];
        pillar[1].x_speed = 1;
        pillar[1].pass = 0;
    }

    if (pillar[2].x <= 0)
    {
        pillar[2].x = 62;
        pillar[2].gap_y = gap_position[rand() % 5];
        pillar[2].x_speed = 1;
        pillar[2].pass = 0;
    }
}

//柱子的清理(清除横坐标为x的柱子)
void pillar_clr(int x)
{
    uchar l;
    for (l = 0; l < 8; l++)
    {
        select_secreen(3);
        set_row(l);
        set_column(x);
        write_data(0xff); //清除
    }
}

//柱子的移动同时清除柱子原本位置
void pillar_move()
{
    int tmp;
    //柱子1的移动和清除
    tmp = pillar[0].x;
    pillar[0].x -= pillar[0].x_speed;
    pillar_clr(tmp);

    //柱子2的移动和清除
    tmp = pillar[1].x;
    pillar[1].x -= pillar[1].x_speed;
    pillar_clr(tmp);

    //柱子3的移动和清除
    tmp = pillar[2].x;
    pillar[2].x -= pillar[2].x_speed;
    pillar_clr(tmp);
}

//柱子的显示
void pillar_print()
{
    uchar l, tmp;

    select_secreen(3); //左屏打印

    //显示柱子1
    tmp = pillar[0].gap_y / 8;

    for (l = 0; l < 8; l++)
    {
        set_row(l); //每一页都打印
        set_column(pillar[0].x);
        if (l == tmp || l == tmp + 1)
        {
            write_data(0xff);
        }
        else
        {
            write_data(0);
        }
    }

    //显示柱子2
    tmp = pillar[1].gap_y / 8;

    for (l = 0; l < 8; l++)
    {
        set_row(l); //每一页都打印
        set_column(pillar[1].x);
        if (l == tmp || l == tmp + 1)
        {
            write_data(0xff); //显示缺口
        }
        else
        {
            write_data(0); //显示柱子
        }
    }

    //显示柱子3
    tmp = pillar[2].gap_y / 8;

    for (l = 0; l < 8; l++)
    {
        set_column(pillar[2].x);
        set_row(l); //每一页都打印
        if (l == tmp || l == tmp + 1)
        {
            write_data(0xff);
        }
        else
        {
            write_data(0);
        }
    }
}

//小鸟的控制
void bird_control()
{
    uchar a;
    P3 = 0xff;
    a = P3 & 0x0f; //读取此时P1口的低4位0000？？？？
    a = ~a;
    a &= 0x0f;

    switch (a)
    {
        //向上的按键被按下，
    case 1:
        bird.y -= 4;
        break;
    default:
        break;
    }
}

//打印游戏相关信息
void bird_message()
{
    uchar l;
    select_secreen(2);             //在右屏打印
    print(0, 0, menu_text7, 16);   //飞
    print(0, 16, menu_text8, 16);  //行
    print(0, 32, menu_text9, 16);  //小
    print(0, 48, menu_text10, 16); //鸟

    print(2, 8, score_text[0], 8);  //字母s
    print(2, 16, score_text[1], 8); //字母c
    print(2, 24, score_text[2], 8); //字母o
    print(2, 32, score_text[3], 8); //字母r
    print(2, 40, score_text[4], 8); //字母e
    print(4, 8, number[0], 8);      //数字0  万位
    print(4, 16, number[0], 8);     //数字0  千位
    print(4, 24, number[0], 8);     //数字0  百位

    //打印边界线
    for (l = 0; l < 8; l++)
    {
        select_secreen(3); //左屏打印
        set_row(l);        //每一页都打印
        set_column(63);
        write_data(0);
    }
}

//判断小鸟的触碰
int bird_collison()
{
    //上边界和下边界的触碰结束游戏
    if (bird.y <= 0 || bird.y >= 63)
    {
        screen_clr2(3); //左屏清理
        return 0;
    }
    //与柱子1碰撞结束游戏
    if (bird.x == pillar[0].x && (bird.y < pillar[0].gap_y || bird.y > pillar[0].gap_y + 15))
    {
        screen_clr2(3);
        return 0;
    }
    //与柱子2碰撞结束游戏
    if (bird.x == pillar[1].x && (bird.y < pillar[1].gap_y || bird.y > pillar[1].gap_y + 15))
    {
        screen_clr2(3);
        return 0;
    }
    //与柱子3碰撞结束游戏
    if (bird.x == pillar[2].x && (bird.y < pillar[2].gap_y || bird.y > pillar[2].gap_y + 15))
    {
        screen_clr2(3);
        return 0;
    }

    return 1; //无发生碰撞则返回1
}

//得分设置 每次通过一根柱子加一分
void bird_score()
{
    //通过柱子1
    if (bird.x > pillar[0].x && 0 == pillar[0].pass)
    {
        pillar[0].pass = 1; //表示这根柱子也被通过
        score_bit++;        //得一分

        if (bird.score % 10 == 0 && bird.score != 0) //每得10分时，重置个位数组下标，十位数组下标+1
        {
            score_ten++;
            score_bit = 0;
        }
        
    }

    //通过柱子2
    if (bird.x > pillar[1].x && 0 == pillar[1].pass)
    {
        pillar[1].pass = 1; //表示这根柱子也被通过
        score_bit++;        //得一分

        if (bird.score % 10 == 0 && bird.score != 0) //每得10分时，重置个位数组下标，十位数组下标+1
        {
            score_ten++;
            score_bit = 0;
        }
       
    }

    //通过柱子3
    if (bird.x > pillar[2].x && 0 == pillar[2].pass)
    {
        pillar[2].pass = 1; //表示这根柱子也被通过
        score_bit++;        //得一分

        if (bird.score % 10 == 0 && bird.score != 0) //每得10分时，重置个位数组下标，十位数组下标+1
        {
            score_ten++;
            score_bit = 0;
        }
        
    }
}

//小鸟游戏失败信息打印
void bird_gameover()
{

    screen_clr2(3); //左屏清理

    select_secreen(3); //选择左屏打印

    //打印gameover
    print(2, 0, gameover_text[0], 8);
    print(2, 8, gameover_text[1], 8);
    print(2, 16, gameover_text[2], 8);
    print(2, 24, gameover_text[3], 8);
    print(2, 32, gameover_text[4], 8);
    print(2, 40, gameover_text[5], 8);
    print(2, 48, gameover_text[6], 8);
    print(2, 56, gameover_text[7], 8);
}
