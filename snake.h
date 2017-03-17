#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
// ����̨�������
#define Hc GetStdHandle(STD_OUTPUT_HANDLE)
// �ض������̨��ɫ����
#define Color SetConsoleTextAttribute
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#define Xx 32
#define Yy Xx
// �����ͼ�Ķ�ά����
int smap[Yy][Xx];
// �����ƶ������ö��
enum Di{up,down,left,right};
// ��ת��������λ�����
void goxy(SHORT x, SHORT y)
{
    COORD po = {(SHORT)(x*2), y};
    SetConsoleCursorPosition(Hc,po);
}
// �������ʳ��
void c_rand(int *f)
{
    srand((unsigned)time(NULL));
    f[0] = rand()%(Xx-4) + 2;
    f[1] = rand()%(Yy-4) + 2;
    f[2] = 1;
}
// ���ع��
void hide()
{
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(Hc, &cci);
    cci.bVisible = 0;
    SetConsoleCursorInfo(Hc, &cci);
}
// ���������Ϊ�йص���
class Snake
{
    int food[3];
    enum Di fx;   //���˶�����
    int sl;    //������
    typedef struct _sbody{
        int x;          //������������
        int y;
    }sbody; sbody *sbd;
    // ��β
    sbody tail;

public:
    Snake(int sl = 3){
        this->sl = sl;
    }
    ~Snake(){
        for(int i = 0;i<sl;i++)
            free(&sbd[i]);
    }
    // �߳��Ƚӿ�
    int getlen(){   return sl;  }
    // ʳ��״̬�ӿ�
    int fdstatus(){ return food[2];  }
    void init();
    void setfx(char f);
    bool eat();
    bool pd_over();
    void smove();
    void newfood();
    void sfree();
};
// ��ʼ��
void Snake::init()
{
    fx = up;
    hide();
    // ���ô��ڴ�С
    system("mode con: cols=92 lines=34");

    // ��ʼ��������ͼ
    for(int i = 0;i < Yy;i++){
        for(int j = 0;j < Xx;j++){
            Color(Hc,001);
            if(i == 0 || j == 0 || i == Yy - 1 || j == Xx - 1)  Color(Hc,255);
            if(i == 1 || j == 1 || i == Yy - 2 || j == Xx - 2)  Color(Hc,2);
            std::cout << "��";
        }
        std::cout << std::endl;
    }
    // ��ʼ������λ��
    sbd = (sbody*)calloc(sl,sizeof(sbody));
    sbd[0].x = Xx/2 - 1;   sbd[0].y = Yy/2 - 1;
    for(int i = 0;i < sl;i++){
            sbd[i].x = sbd[0].x;
            sbd[i].y = sbd[0].y + i;
            goxy(sbd[i].x,sbd[i].y);
            Color(Hc,4); std::cout << "��";
    }
    // ��ʼ��ʳ��λ��
    newfood();
}

// ��ȡ���޸��ƶ�����
void Snake::setfx(char f)
{
    switch(f){
        case 'w': case 'W':
            if(fx != down)
                fx = up; break;
        case 's': case 'S':
            if(fx != up)
                fx = down; break;
        case 'd': case 'D':
            if(fx != left)
                fx = right; break;
        case 'a': case 'A':
            if(fx != right)
                fx = left; break;
    }
}
// �ж��Ƿ�Ե�ʳ��
bool Snake::eat()
{
    if(sbd[0].x == food[0] && sbd[0].y == food[1]){
        food[2] = 0;
        return true;
    }else
        return false;
}
// ����Խ�����ͷ��������ʱ������Ϸ
bool Snake::pd_over()
{
    if(sbd[0].y - 1 == 0 || sbd[0].y + 1 == Yy - 1 || sbd[0].x - 1 == 0 || sbd[0].x + 1 == Xx - 1)  return true;

    for(int i = 1;i<sl;i++)
        if(sbd[0].x == sbd[i].x && sbd[0].y == sbd[i].y){
            return true;
        }
    return false;
}
// ���ĺ��� �����ߵ��ƶ�
void Snake::smove()
{
    bool fll = eat();
    tail = sbd[sl-1];
    // �����β
    goxy(tail.x,tail.y); Color(Hc,001); std::cout << "��";

    Color(Hc,4);
    // ����ǰ��
    for(int i=sl-1;i>0;i--){
        sbd[i] = sbd[i-1];
    }
    // �ػ���ͷ
    switch(fx)
    {
        case up:
            goxy(sbd[0].x,--sbd[0].y); std::cout << "��";  break;
        case down:
            goxy(sbd[0].x,++sbd[0].y); std::cout << "��";  break;
        case left:
            goxy(--sbd[0].x,sbd[0].y); std::cout << "��";  break;
        case right:
            goxy(++sbd[0].x,sbd[0].y); std::cout << "��";  break;
    }
    // �Ե�ʳ�������߳���
    if(fll){
        sbd = (sbody*)realloc(sbd,++sl*sizeof(sbody));
        sbd[sl-1] = tail;
    }
}
// �����µ�ʳ��
void Snake::newfood()
{
    rebuild:
        c_rand(food);
        for(int i = 0;i<sl;i++){
            if(sbd[i].x == food[0] && sbd[i].y == food[1]) // ����ʳ���������������
                goto rebuild;
        }
    goxy(food[0],food[1]); Color(Hc,14);  std::cout << "��";
}

#endif
