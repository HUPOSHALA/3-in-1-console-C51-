#include "ampire.h"
sbit RS = P2 ^ 0;  //P2 ^ 0��RS����
sbit RW = P2 ^ 1;  //P2 ^ 1��RW����
sbit EN = P2 ^ 2;  //P2 ^ 2��E����
sbit CS1 = P2 ^ 3; //P2 ^ 3��CS1����
sbit CS2 = P2 ^ 4; //P2 ^ 4��CS2����
sbit RST = P2 ^ 5; //P2 ^ 5��RST����
void Delay1ms();   //12MHZ���� �ӳ�1ms

//дָ��
void write_cmd(uchar cmd)
{
    delay(1);
    EN = 1;
    RS = 0; //�͵�ƽдָ��
    RW = 0;
    P1 = cmd; //д��ָ��
    EN = 0;
}

//д����
void write_data(uchar d)
{
    // delay(1);
    EN = 1;
    RS = 1; //�ߵ�ƽд����
    RW = 0;
    P1 = d; //д������
    EN = 0;
}
//��Ļ��ѡ��   1Ϊȫ�� 2Ϊ���� 3Ϊ����
void select_secreen(uchar s)
{
    switch (s)
    {
    case 1:
        CS1 = 0; //CS1��CS2�͵�ƽ��Ч
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

void set_row(uchar x) //��������һҳд��
{
    x = 0x07 & x; //ȡд��ĵ���λ
    x = 0xb8 | x; //1011 1������|x
    write_cmd(x);
}

void set_column(uchar y) //��������һ��д��
{
    y = y & 0x3f; //0011 1111&y
    y = y | 0x40; //01?? ????
    write_cmd(y);
}

//���ó�ʼҳ
void set_startrow(uchar x)
{
    x = x & 0x3f;
    x = x | 0xc0;
    write_cmd(x);
}



//��ʼ����ʾ��
void initate()
{
    RST = 0;
    delay(1);
    RST = 1;
    delay(1);
    write_cmd(0x3f);  //��Ļ��
    set_row(0);
    set_startrow(0);
    set_column(0);
    select_secreen(1);
    screen_clr(1);
}

//����(1-ȫ��  2-����   3-����)
void screen_clr(uchar x)
{
    uchar i, j;
    select_secreen(x); //ȫ������
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
    select_secreen(x); //ȫ������
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

//����ʾ���ϵ�x,y����λ����ʾһ���㣬�������� 2Ϊ������ʾ��3Ϊ������
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

//����Ļ�����һ���㣬��spot_print�Ĺ����෴
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


//�ӳ�tms
void delay(uint t)
{
    while (t--)
    {
        Delay1ms();
    }
}

//�ӳ�1ms
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
