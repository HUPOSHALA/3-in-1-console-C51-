#include "ampire.h"
#include "Game.h"
#include "Snake.h"
uchar xdata score_bit;      //��λ��������±�
uchar xdata score_ten;      //ʮλ��������±�
extern snake xdata p;             //��sanke.c�ļ����Ѿ����壬������Ҫ����
extern uchar code y_move[]; //������ͬ��

//����ʳ��
food xdata f;

//̰
uchar code text1[] =
    {
        0xDF, 0xDF, 0xEF, 0xEF, 0xD7, 0xDB, 0xDD, 0xD6, 0x4D, 0x9B, 0xD7, 0xEF, 0xEF, 0xDF, 0xDF, 0xFF,
        0xFF, 0x7F, 0x7F, 0x60, 0xBE, 0xBE, 0xDE, 0xE2, 0xFE, 0xDE, 0xDE, 0xA0, 0xBF, 0x7F, 0xFF, 0xFF};

//ʳ
uchar code text2[] =
    {
        0xDF, 0xDF, 0xEF, 0x0F, 0x57, 0x5B, 0x55, 0x4E, 0x5D, 0x5B, 0x57, 0x0F, 0xEF, 0xDF, 0xDF, 0xFF,
        0xFF, 0xFF, 0xFF, 0x00, 0x7D, 0xBD, 0xDD, 0xF5, 0xF5, 0xED, 0xED, 0xD4, 0xBB, 0x7F, 0xFF, 0xFF

};

//��
uchar code text3[] =
    {

        0xFF, 0x07, 0xF7, 0x00, 0xF7, 0x07, 0xDF, 0xE7, 0x37, 0xF7, 0xF6, 0xF1, 0x77, 0xD7, 0xE7, 0xFF,
        0xDF, 0x9C, 0xDE, 0xE0, 0xEE, 0xE6, 0xCF, 0xFF, 0xC0, 0xBB, 0xBD, 0xBE, 0xBF, 0xBF, 0x87, 0xFF};

//����0~9
uchar code number[10][16] = {
    {0xFF, 0x1F, 0xEF, 0xF7, 0xF7, 0xEF, 0x1F, 0xFF, 0xFF, 0xF0, 0xEF, 0xDF, 0xDF, 0xEF, 0xF0, 0xFF},
    {0xFF, 0xFF, 0xEF, 0xEF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xDF, 0xC0, 0xDF, 0xDF, 0xFF},
    {0xFF, 0x8F, 0xF7, 0xF7, 0xF7, 0xF7, 0x0F, 0xFF, 0xFF, 0xCF, 0xD7, 0xDB, 0xDD, 0xDE, 0xCF, 0xFF},
    {0xFF, 0xCF, 0xF7, 0xF7, 0xF7, 0x77, 0x8F, 0xFF, 0xFF, 0xE7, 0xDF, 0xDE, 0xDE, 0xDD, 0xE3, 0xFF},
    {0xFF, 0xFF, 0x7F, 0xBF, 0xCF, 0x07, 0xFF, 0xFF, 0xFF, 0xF9, 0xFA, 0xDB, 0xDB, 0xC0, 0xDB, 0xDB},
    {0xFF, 0x07, 0x77, 0x77, 0x77, 0xF7, 0xF7, 0xFF, 0xFF, 0xE6, 0xDF, 0xDF, 0xDF, 0xEE, 0xF1, 0xFF},
    {0xFF, 0x1F, 0xEF, 0x77, 0x77, 0x6F, 0xFF, 0xFF, 0xFF, 0xF0, 0xEE, 0xDF, 0xDF, 0xDF, 0xE0, 0xFF},
    {0xFF, 0xE7, 0xF7, 0xF7, 0x77, 0x97, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xC1, 0xFE, 0xFF, 0xFF, 0xFF},
    {0xFF, 0x8F, 0x77, 0xF7, 0xF7, 0x77, 0x8F, 0xFF, 0xFF, 0xE3, 0xDD, 0xDE, 0xDE, 0xDD, 0xE3, 0xFF},
    {0xFF, 0x0F, 0xF7, 0xF7, 0xF7, 0xEF, 0x1F, 0xFF, 0xFF, 0xFE, 0xED, 0xDD, 0xDD, 0xEE, 0xF0, 0xFF}

};

//��ĸgameover
uchar code gameover_text[8][16] =
    {
        {0xC0, 0x30, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0x07, 0x18, 0x20, 0x20, 0x22, 0x1E, 0x02, 0x00},
        {0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x19, 0x24, 0x24, 0x12, 0x3F, 0x20, 0x00},
        {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x3F, 0x20, 0x00, 0x3F},
        {0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x1F, 0x24, 0x24, 0x24, 0x24, 0x17, 0x00},
        {0xE0, 0x10, 0x08, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x0F, 0x10, 0x20, 0x20, 0x20, 0x10, 0x0F, 0x00},
        {0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x03, 0x0C, 0x30, 0x0C, 0x03, 0x00, 0x00},
        {0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x1F, 0x24, 0x24, 0x24, 0x24, 0x17, 0x00},
        {0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x20, 0x20, 0x3F, 0x21, 0x20, 0x00, 0x01, 0x00}};

//��ĸscore
uchar code score_text[5][16] =
    {
        {0xFF, 0x8F, 0x77, 0xF7, 0xF7, 0xF7, 0xC7, 0xFF, 0xFF, 0xC7, 0xDF, 0xDE, 0xDE, 0xDD, 0xE3, 0xFF},
        {0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xF1, 0xEE, 0xDF, 0xDF, 0xDF, 0xEE, 0xFF},
        {0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xE0, 0xDF, 0xDF, 0xDF, 0xDF, 0xE0, 0xFF},
        {0x7F, 0x7F, 0x7F, 0xFF, 0x7F, 0x7F, 0x7F, 0xFF, 0xDF, 0xDF, 0xC0, 0xDE, 0xDF, 0xFF, 0xFE, 0xFF},
        {0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xE0, 0xDB, 0xDB, 0xDB, 0xDB, 0xE8, 0xFF}};

//���ִ�ӡ ���� �� ���� ���ȣ�
void print(uchar row, uchar column, uchar *text, uchar width)
{
    uchar i, j;
    for (i = 0; i < 2; i++) //��ĸ������ȡģ��ĸ߶ȶ���16����������ĸ��8��������16
    {
        set_row(row + i);
        set_column(column);
        for (j = 0; j < width; j++)
        {
            write_data(text[width * i + j]);
        }
    }
}

//ʳ���ʼ��
void food_initate()
{
    f.x = 32; //��ʼ��ʳ�������x,y
    f.y = 32;
    f.score = 0;   //�÷ֳ�ʼ��Ϊ0
    score_bit = 0; //��λ������±��ʼ��Ϊ0
    score_ten = 0; //ʮλ������±��ʼ��Ϊ0
}

//��ʾʳ��
void food_display()
{
    uchar row;
    uchar coulumn;
    uchar ix;
    row = f.y / 8; //����Ŀǰʳ������ҳ
    set_row(row);
    ix = f.y % 8;
    coulumn = f.x; //�õ�ʳ�����ڵ�����
    set_column(coulumn);
    write_data(y_move[ix]);
}

//�ж�ʳ���Ƿ񱻳Ե�
void food_touch()
{
    if (p.body[0].x == f.x && p.body[0].y == f.y) //ʳ�����������ͷ���������
    {
        set_row(f.x);
        set_column(f.y);
        write_data(0xff);  //���ԭ��ʳ���λ��
        f.x = rand() % 63; //�������ʳ����µ�x����
        f.y = rand() % 63; //�������ʳ����µ�y����
        f.score++;         //����+1
        score_bit++;       //��λ������±�+1
        p.Num++;           //�ߵ�����+1

        if (f.score % 10 == 0 && f.score != 0) //ÿ��10��ʱ�����ø�λ�����±꣬ʮλ�����±�+1
        {
            score_ten++;
            score_bit = 0;
        }
    }
}

//��ʾ����
void score_display()
{
    select_secreen(2);                  //������������ӡ
    print(4, 32, number[score_ten], 8); //��ӡʮλ������
    print(4, 40, number[score_bit], 8); //��ӡ��λ������
    select_secreen(3);                  //�л�������
}

//��Ϸ�����ж�����
int game_over()
{
    select_secreen(3);
    if (!snack_collision()) //��ײǽʱ������Ϸ����������ӡ��Ϣ
    {

        //��ӡgameover
        print(2, 0, gameover_text[0], 8);
        print(2, 8, gameover_text[1], 8);
        print(2, 16, gameover_text[2], 8);
        print(2, 24, gameover_text[3], 8);
        print(2, 32, gameover_text[4], 8);
        print(2, 40, gameover_text[5], 8);
        print(2, 48, gameover_text[6], 8);
        print(2, 56, gameover_text[7], 8);

        return 1;
    }
    return 0;
}

//��ӡ��Ϸ�в���ı����Ϣ
void print_gamemessage()
{
    uchar l;
    select_secreen(2);              //��������ӡ
    print(0, 8, text1, 16);         //̰
    print(0, 24, text2, 16);        //ʳ
    print(0, 40, text3, 16);        //��
    print(2, 8, score_text[0], 8);  //��ĸs
    print(2, 16, score_text[1], 8); //��ĸc
    print(2, 24, score_text[2], 8); //��ĸo
    print(2, 32, score_text[3], 8); //��ĸr
    print(2, 40, score_text[4], 8); //��ĸe
    print(4, 8, number[0], 8);      //����0  ��λ    �������������õ���߷�99��������Ȼ�������ߵĳ��ȶ���������ô��
    print(4, 16, number[0], 8);     //����0  ǧλ
    print(4, 24, number[0], 8);     //����0  ��λ


    //��ӡ�ұߵı߽���
    for (l = 0; l < 8; l++)
    {
        select_secreen(3); //������ӡ
        set_row(l);        //ÿһҳ����ӡ
        set_column(63);
        write_data(0);
    }
}