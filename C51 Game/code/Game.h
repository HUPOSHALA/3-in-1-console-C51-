#ifndef __game_H__
#define __game_H__
#include <stdlib.h>

//ʳ��Ľṹ��
typedef struct
{
    uchar x;
    uchar y;
    uchar score; //����ķ������Բ�д�����������Ϊȫ�ֱ���
} food;



void food_initate();                                           //ʳ���ʼ��
void food_display();                                           //��ʾʳ��
void food_touch();                                             //�ж�ʳ���Ƿ񱻳Ե�
void score_display();                                          //��ʾ����
int game_over();                                               //��Ϸ�����ж�����
void print_gamemessage();                                      //��ӡ��Ϸ�в���ı����Ϣ

#endif