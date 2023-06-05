#ifndef __ampirasd_H__
#define __ampirasd_H__
#include <REG52.H>
#include <stdlib.h>
typedef unsigned int uint;
typedef unsigned char uchar;
extern uchar code y_move[];                                   
extern uchar code gameover_text[8][16];                        //gameover数组
extern uchar code number[10][16];                              //数字0~9
extern uchar code score_text[5][16];                           //score字母数组
extern uchar xdata score_bit;                                  //个位数数组的下标
extern uchar xdata score_ten;                                  //十位数数组的下标
extern uchar code menu_text11[];                               //"灭"
extern uchar code menu_text12[];                               //"灯"

void print(uchar row, uchar column, uchar *text, uchar width); //文字打印 （行 列 数组 宽度）
void delay(uint t);                                            //设置延迟tms
void initate();                                                //初始化显示器
void screen_on();                                              //显示器开
void screen_off();                                             //显示器关
void set_startrow(uchar x);                                    //设置初始页
void set_column(uchar y);                                      //设置列
void set_row(uchar x);                                         //设置页
void select_secreen(uchar s);                                  //选择使用的屏幕  1为全屏 2为右屏 3为左屏
void write_data(uchar d);                                      //写入数据
void write_cmd(uchar cmd);                                     //写入指令
void screen_clr(uchar x);                                      //清屏
void screen_clr2(uchar x);                                     //清屏2
void spot_print(uchar x, uchar y, uchar screen);               //在显示屏上的x,y坐标位置显示一个点，第三参数 1为左屏显示
void score_display();
void spot_clr(uchar x, uchar y, uchar screen);                 //在屏幕上清除一个点，与spot_print的功能相反

#endif