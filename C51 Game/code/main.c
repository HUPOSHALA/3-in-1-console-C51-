#include <REG52.H>
#include <INTRINS.H>
#include <stdlib.h>

#include "ampire.h"
#include "Snake.h"
#include "Game.h"
#include "Menu.h"
#include "BIRD.h"
#include "light.h"

typedef void (*game_ptr)();

//定义中断按钮
sbit X1 = P3 ^ 2;
sbit X2 = P3 ^ 3;

void Game_menu();
void Game_snack();
void Game_bird();
void Game_light();

game_ptr code ptr[4] = {Game_menu, Game_snack, Game_bird, Game_light}; //函数指针数组
uchar game_select = 0;                                                 //游戏选择，函数指针数组的下标
uchar reset = 1;                                                       //重启标志
uchar confirm = 0;                                                     //确认标志
uchar menu_select = 2;                                                 //菜单选择
uchar aab = 0;

int main()
{
    EA = 1;  //开启总中断
    ET1 = 1; //开启定时器1中断

    EX0 = 1; //外部中断0开启
    EX1 = 1; //外部中断1开启

    PX0 = 1;
    PX1 = 1;

    IT1 = 1;
    IT0 = 1;

    TMOD = 0x10; //使用定时器1
    TH1 = 0xff;  //高8位置0xff
    TL1 = 0;     //低8位置0，
    TR1 = 1;     //开启定时器

    //initate(); //显示器的初始化

    while (1)
    {
        while (reset)
        {
            ptr[game_select](); //运行选择的游戏
        }
    }
}

//中断，重置定时器
void timerl() interrupt 3
{
    TR1 = 0;    //关闭定时器
    TH1 = 0xff; //重置定时器的高位和低位
    TL1 = 0;
    TR1 = 1; //开启定时器
}

void ex0() interrupt 0 //外部中断0 选择控制和重置按钮
{
    EX0 = 0;
    delay(60);
    if (0 == X1)
    {
        if (game_select > 0)
        {
            reset = 1;
        }
        else
        {
            aab = 1;
        }
    }
    EX0 = 1;
}

void ex1() interrupt 2
{
    EX1 = 0;
    delay(50);
    if (0 == X2)
    {
        confirm = 1;
    }
    EX1 = 1;
}

void Game_menu()
{

    initate(); //显示器的初始化

    //游戏菜单选择界面
    menu_print();
    select_secreen(3);                      //选择左屏
    print(menu_select, 16, menu_arrow, 16); //光标的打印

    while (1) //游戏选择界面光标的移动和按键的确认
    {
        if (1 == aab)
        {
            print(menu_select, 16, block_clr, 16);

            menu_select += 2;
            if (8 == menu_select)
            {
                menu_select = 2;
            }
            print(menu_select, 16, menu_arrow, 16);
            aab = 0;
        }

        if (1 == confirm)
        {
            break;
        }
    }
    confirm = 0;

    switch (menu_select)
    {
    case 2:
        game_select = 1;
        break;
    case 4:
        game_select = 2;
        break;
    case 6:
        game_select = 3;
        break;
    default:
        break;
    }
}

//贪食蛇游戏主体
void Game_snack()
{

    EX0 = 0;
    EX1 = 0;

    food_initate(); //食物位置的初始化

    initate(); //显示器的初始化

    print_gamemessage(); //打印游戏中的基本信息

    initate_snake(); //蛇属性的初始化

    while (1)
    {
        srand(TL1); //播种        TL1变化范围为(0~0xff)

        snake_controll(); //蛇的控制

        snake_movee(); //蛇的移动

        food_touch(); //判断蛇是否吃掉食物

        snake_printf(); //显示蛇

        if (game_over()) //游戏结束条件判断
        {
            break;
        }

        score_display(); //打印目前所得的分数

        food_display(); //显示食物

        delay(50); //延迟50ms

        snack_clear(); //蛇尾清除
    }
    reset = 0;
    EX0 = 1;
}

//飞行的小鸟游戏主体
void Game_bird()
{
    uchar tmp;

    EX0 = 0; //关闭外部中断
    EX1 = 0;
    initate();        //显示器初始化
    bird_initate();   //初始化小鸟的属性
    bird_message();   //在屏幕右边打印初始信息
    pillar_initate(); //初始化柱子

    while (1)
    {
        srand(TL1);                    //随机函数播种a
        bird_control();                //控制小鸟
        spot_print(bird.x, bird.y, 3); //显示小鸟
        pillar_move();                 //柱子的移动

        pillar_reset();                //柱子到达最左端时面重置
        bird_score();                  //得分条件判断
        score_display();               //分数显示
        pillar_print();                //柱子的显示
        spot_print(bird.x, bird.y, 3); //显示小鸟

        tmp = bird.y; //存放小鸟现在的y坐标，下次移动的时候清除原位置

        if (!bird_collison()) //小鸟触碰判定
        {
            bird_gameover(); //打印游戏结束信息
            break;
        }

        delay(350); //延迟，稍微改善闪屏

        bird.y += bird.down_speed; //小鸟下坠
        spot_clr(bird.x, tmp, 3);  //小鸟的清除
    }
    EX0 = 1;
    reset = 0;
}

void Game_light()
{
    uchar tmp, column, p0_read;

    initate(); //初始化显示器

    bulb_initate(); //初始化16盏灯

    bulb_meassage(); //打印初始信息

    while (1) //以矩阵键盘的扫描程序为循环的主体
    {
        P0 = 0xef;

        for (column = 0; column < 4; column++)
        {
            p0_read = P0 & 0x0f;
            switch (p0_read)
            {
                //P0.0口低电平
            case 0x0e:
                button_press(column * 4);
                count++;
                score_bit++; //个位数+1

                if (count % 10 == 0 && count != 0) //每得10分时，重置个位数组下标，十位数组下标+1
                {
                    score_ten++;
                    score_bit = 0;
                }
                break;

                //P0.1口低电平
            case 0x0d:
                button_press(column * 4 + 1);
                count++;
                score_bit++; //个位数+1

                if (count % 10 == 0 && count != 0)
                {
                    score_ten++;
                    score_bit = 0;
                }
                break;
                //P0.2口低电平
            case 0x0b:
                button_press(column * 4 + 2);
                count++;
                score_bit++; //个位数+1

                if (count % 10 == 0 && count != 0)
                {
                    score_ten++;
                    score_bit = 0;
                }
                break;
                //P0.3口低电平
            case 0x07:
                button_press(column * 4 + 3);
                count++;
                score_bit++; //个位数+1

                if (count % 10 == 0 && count != 0)
                {
                    score_ten++;
                    score_bit = 0;
                }
                break;
            default:
                break;
            }

            delay(20);
            tmp = P0;             //读取此时P0口的状态
            tmp = tmp | 0x0f;     //低四位重置为高电平，读取状态
            tmp = _crol_(tmp, 1); //左移
            tmp = tmp | 0x0f;
            P0 = tmp;
        }

        bulb_print();    //刷新灯泡的显示状态
        score_display(); //显示分数
        if (!button_over())
        {
            bulb_gameover();
            break;
        }
    }
    reset = 0;
}
