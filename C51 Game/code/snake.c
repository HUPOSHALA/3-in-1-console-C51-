#include "Snake.h"
uchar code y_move[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
//����һ����
snake xdata p;

//��ʼ���ߵ�����
void initate_snake()
{
    int i, j;
    j = 1;

    p.x_speed = 1;
    p.y_speed = 0;
    p.Num = 6;

    for (i = 5; i >= 0; i--)
    {
        p.body[i].x = j;
        p.body[i].y = 0;
        j++;
    }
}

//�ߵ��ƶ�����������ĸı䣩
void snake_movee()
{

    uchar i = (p.Num) - 1;
    for (i; i > 0; i--)
    {
        p.body[i].x = p.body[i - 1].x;
        p.body[i].y = p.body[i - 1].y;
    }

    p.body[0].x += p.x_speed;
    p.body[0].y += p.y_speed;
}

//��ʾ��
void snake_printf()
{
    uchar tmp_x, tmp_row, tmp_y, tmp, i, head_column, column, row, rowx, rowxx, d1, d2, a;
    head_column = p.body[0].x; //ȡ��ͷ��x����
    i = 1;
    column = p.body[i].x; //ȡ�ߵĵ�i�������x����
    //��Ӧ������ת��
    row = (p.body[0].y) / 8;
    rowx = (p.body[i].y) / 8;
    rowxx = (p.body[0].y) % 8;
    d1 = ~(y_move[rowxx]);
    if (p.y_speed != 0) //y�����ϵ��ٶȲ�Ϊ0����ֱ�ƶ�
    {
        while (row == rowx && head_column == column)
        {
            a = (p.body[i].y) % 8;
            d2 = ~(y_move[a]);
            d1 += d2;
            i++;
            column = p.body[i].x;
            rowx = (p.body[i].y) / 8;
        }
        d1 = ~d1;
        set_row(row);
        select_secreen(3);
        set_column(head_column);
        write_data(d1);
    }
    else //ˮƽ�������ƶ�
    {

        for (i = 0; i < p.Num; i++) //����ͷ��ʼ��ӡ
        {
            tmp_row = (p.body[i].y) / 8; //����õ����ڵ�ҳ����Ҳ�������λY�����ϵ�������
            set_row(tmp_row);            //��������һҳд������
            tmp = (p.body[i].y) % 8;
            tmp_y = y_move[tmp];
            tmp_x = p.body[i].x;

            select_secreen(3); //������ӡ
            set_column(tmp_x); //������һ��д��
            write_data(tmp_y);
        }
    }
}

//�ߵĿ���
void snake_controll()
{
    uchar a;
    P3 = 0xff;
    a = P3 & 0x0f; //��ȡ��ʱP1�ڵĵ�4λ0000��������
    a = ~a;
    a &= 0x0f;

    switch (a)
    {
        //�����ƶ����ı��ߵ��ƶ�����
    case 1:
        if (p.y_speed == 0)
        {
            p.y_speed = -1;
            p.x_speed = 0;
        }
        break;
        //�����ƶ� �ı��ߵ��ƶ�����
    case 2:
        if (p.x_speed == 0)
        {
            p.x_speed = -1;
            p.y_speed = 0;
        }
        break;
        //�����ƶ� �ı��ߵ��ƶ�����
    case 4:
        if (p.y_speed == 0)
        {
            p.y_speed = 1;
            p.x_speed = 0;
        }
        break;
        //�����ƶ� �ı��ߵ��ƶ�����
    case 8:
        if (p.x_speed == 0)
        {
            p.x_speed = 1;
            p.y_speed = 0;
        }
    default:
        break;
    }
}

//��β������
void snack_clear()
{
    uchar i, j, k;
    i = (p.Num) - 1;
    j = p.body[i].x;
    k = p.body[i].y;
    k /= 8;

    select_secreen(3);
    set_row(k);
    set_column(j);
    write_data(0xff);
}

//�ж����Ƿ�ײǽ
int snack_collision()
{
    //�ϱ߽�
    if (p.y_speed == -1 && p.body[1].y == 0)
    {
        screen_clr2(3);
        return 0;
    }

    //�±߽�
    if (p.y_speed == 1 && p.body[1].y == 63)
    {
        screen_clr2(3);
        return 0;
    }

    //��߽�
    if (p.x_speed == -1 && p.body[1].x == 0)
    {
        screen_clr2(3);
        return 0;
    }

    //�ұ߽�
    if (p.x_speed == 1 && p.body[1].x == 63)
    {
        screen_clr2(3);
        return 0;
    }
    return 1;
}

//返回一条蛇
// snake_ptr sanke_createrl()
// {
//     int k;
//     snake tmp;
//     tmp.x_speed = 1;
//     tmp.y_speed = 0;
//     tmp.Num = 1;
//     tmp.body[0].x = 1;
//     tmp.body[0].y = 1;
//     return &tmp;
// }

//蛇的移动
// void snake_move(snake_ptr s)
// {
//     int k;
//     //uchar i = s->Num;
//     // for (i; i > 0; i--)
//     // {
//     //     s->body[i].x = s->body[i - 1].x;
//     //     s->body[i].y = s->body[i - 1].y;
//     // }
//     s->body[0].x += s->x_speed;
//     s->body[0].y += s->y_speed;
// }

//显示�?
// void snake_print(snake_ptr s)
// {
//     int k;
//     uchar tmp_x, tmp_row, tmp_y, tmp, i;

//     for (i = 0; i < s->Num; i++)
//     {
//         tmp_row = (s->body[i].y) / 8;
//         set_row(tmp_row);
//         tmp = (s->body[i].y) % 8;

//         tmp_y = y_move[tmp];
//         tmp_x = s->body[i].x;
//         if (tmp_x > 63)
//         {
//             select_secreen(2);
//             tmp_x %= 63;
//             set_column(tmp_x);
//             write_data(tmp_y);
//         }
//         else
//         {
//             select_secreen(3);
//             set_column(tmp_x);
//             write_data(tmp_y);
//         }
//     }
// }

//控制�?
// void snake_control(snake_ptr p)
// {
//     uchar a;
//     P3 = 0xff;
//     a = P3 & 0x0f; //读取此时P1口的�?4�?0000？？？？
//     a = ~a;
//     a &= 0x0f;
//     switch (a)
//     {
//         //向上移动，改变蛇的移动方�?
//     case 1:
//         if (p->y_speed == 0)
//         {
//             p->y_speed = -1;
//             p->x_speed = 0;
//         }
//         break;
//         //向左移动 改变蛇的移动方向
//     case 2:
//         if (p->x_speed == 0)
//         {
//             p->x_speed = -1;
//             p->y_speed = 0;
//         }
//         break;
//         //向下移动 改变蛇的移动方向
//     case 4:
//         if (p->y_speed == 0)
//         {
//             p->y_speed = 1;
//             p->x_speed = 0;
//         }
//         break;
//         //向右移动 改变蛇的移动方向
//     case 8:
//         if (p->x_speed == 0)
//         {
//             p->x_speed = 1;
//             p->y_speed = 0;
//         }
//     default:
//         break;
//     }
// }