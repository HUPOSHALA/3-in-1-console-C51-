#ifndef __SNAKsdE_H__
#define __SNAKsdE_H__
#include <REG52.H>
#include "ampire.h"

//�����������
typedef struct
{
    uchar x;
    uchar y;
} Pos;

typedef struct
{    
    Pos body[40]; //����������ֵ�����       
    char x_speed; //x�����ϵ��ٶ�
    char y_speed; //y�����ϵ��ٶ�   
    uchar Num;    //������ĳ���
    
} snake, *snake_ptr;


void initate_snake();  //��ʼ���ߵ�����

void snake_movee();    //�ߵ��ƶ����������������ı仯��

void snake_printf();   //��ʾ��

void snake_controll(); //�ߵĿ���

void snack_clear();    //��β������

int snack_collision(); //�ж����Ƿ�ײǽ


#endif
