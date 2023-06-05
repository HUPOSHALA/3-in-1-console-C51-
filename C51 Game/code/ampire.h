#ifndef __ampirasd_H__
#define __ampirasd_H__
#include <REG52.H>
#include <stdlib.h>
typedef unsigned int uint;
typedef unsigned char uchar;
extern uchar code y_move[];                                   
extern uchar code gameover_text[8][16];                        //gameover����
extern uchar code number[10][16];                              //����0~9
extern uchar code score_text[5][16];                           //score��ĸ����
extern uchar xdata score_bit;                                  //��λ��������±�
extern uchar xdata score_ten;                                  //ʮλ��������±�
extern uchar code menu_text11[];                               //"��"
extern uchar code menu_text12[];                               //"��"

void print(uchar row, uchar column, uchar *text, uchar width); //���ִ�ӡ ���� �� ���� ��ȣ�
void delay(uint t);                                            //�����ӳ�tms
void initate();                                                //��ʼ����ʾ��
void screen_on();                                              //��ʾ����
void screen_off();                                             //��ʾ����
void set_startrow(uchar x);                                    //���ó�ʼҳ
void set_column(uchar y);                                      //������
void set_row(uchar x);                                         //����ҳ
void select_secreen(uchar s);                                  //ѡ��ʹ�õ���Ļ  1Ϊȫ�� 2Ϊ���� 3Ϊ����
void write_data(uchar d);                                      //д������
void write_cmd(uchar cmd);                                     //д��ָ��
void screen_clr(uchar x);                                      //����
void screen_clr2(uchar x);                                     //����2
void spot_print(uchar x, uchar y, uchar screen);               //����ʾ���ϵ�x,y����λ����ʾһ���㣬�������� 1Ϊ������ʾ
void score_display();
void spot_clr(uchar x, uchar y, uchar screen);                 //����Ļ�����һ���㣬��spot_print�Ĺ����෴

#endif