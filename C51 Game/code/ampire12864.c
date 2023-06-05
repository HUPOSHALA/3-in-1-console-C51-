#include "ampire.h"
sbit RS = P2 ^ 0;  //P2 ^ 0接RS引脚
sbit RW = P2 ^ 1;  //P2 ^ 1接RW引脚
sbit EN = P2 ^ 2;  //P2 ^ 2接E引脚
sbit CS1 = P2 ^ 3; //P2 ^ 3接CS1引脚
sbit CS2 = P2 ^ 4; //P2 ^ 4接CS2引脚
sbit RST = P2 ^ 5; //P2 ^ 5接RST引脚
void Delay1ms();   //12MHZ晶振 延迟1ms

//写指令
void write_cmd(uchar cmd)
{
    delay(1);
    EN = 1;
    RS = 0; //低电平写指令
    RW = 0;
    P1 = cmd; //写入指令
    EN = 0;
}

//写数据
void write_data(uchar d)
{
    // delay(1);
    EN = 1;
    RS = 1; //高电平写数据
    RW = 0;
    P1 = d; //写入数据
    EN = 0;
}
//屏幕的选择   1为全屏 2为右屏 3为左屏
void select_secreen(uchar s)
{
    switch (s)
    {
    case 1:
        CS1 = 0; //CS1和CS2低电平有效
        delay(1);
        CS2 = 0;
        delay(1);
        break;
    case 2:
        CS1 = 1;
        delay(1);
        CS2 = 0;
        delay(1);
        break;
    case 3:
        CS1 = 0;
        delay(1);
        CS2 = 1;
        delay(1);
        break;
    default:
        break;
    }
}

void set_row(uchar x) //设置在那一页写入
{
    x = 0x07 & x; //取写入的低三位
    x = 0xb8 | x; //1011 1？？？|x
    write_cmd(x);
}

void set_column(uchar y) //设置在那一列写入
{
    y = y & 0x3f; //0011 1111&y
    y = y | 0x40; //01?? ????
    write_cmd(y);
}

//设置初始页
void set_startrow(uchar x)
{
    x = x & 0x3f;
    x = x | 0xc0;
    write_cmd(x);
}



//初始化显示器
void initate()
{
    RST = 0;
    delay(1);
    RST = 1;
    delay(1);
    write_cmd(0x3f);  //屏幕开
    set_row(0);
    set_startrow(0);
    set_column(0);
    select_secreen(1);
    screen_clr(1);
}

//清屏(1-全屏  2-右屏   3-左屏)
void screen_clr(uchar x)
{
    uchar i, j;
    select_secreen(x); //全屏清理
    for (i = 0; i < 8; i++)
    {
        set_row(i);
        for (j = 0; j < 64; j++)
        {
            set_column(j);
            write_data(0xff);
        }
    }
}

void screen_clr2(uchar x)
{
    uchar i, j;
    select_secreen(x); //全屏清理
    for (i = 0; i < 8; i++)
    {
        set_row(i);
        for (j = 0; j < 64; j++)
        {
            set_column(j);
            write_data(0);
        }
    }
}

//在显示屏上的x,y坐标位置显示一个点，第三参数 2为右屏显示，3为左屏显
void spot_print(uchar x, uchar y, uchar screen)
{
    uchar  row, column, spot, tmp;
    row = y / 8;
    set_row(row);
    tmp = y % 8;
    spot = y_move[tmp];
    column = x;
    select_secreen(screen);
    set_column(column);
    write_data(spot);
}

//在屏幕上清除一个点，与spot_print的功能相反
void spot_clr(uchar x, uchar y, uchar screen)
{
    uchar  row, column, spot, tmp;
    row = y / 8;
    set_row(row);
    tmp = y % 8;
    spot = 0xff;
    column = x;
    select_secreen(screen);
    set_column(column);
    write_data(spot);
}


//延迟tms
void delay(uint t)
{
    while (t--)
    {
        Delay1ms();
    }
}

//延迟1ms
void Delay1ms() //@12.000MHz
{
    unsigned char i, j;

    i = 2;
    j = 239;
    do
    {
        while (--j)
            ;
    } while (--i);
}
