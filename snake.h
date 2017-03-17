#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
// 控制台句柄函数
#define Hc GetStdHandle(STD_OUTPUT_HANDLE)
// 重定义控制台颜色函数
#define Color SetConsoleTextAttribute
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#define Xx 32
#define Yy Xx
// 构造地图的二维数组
int smap[Yy][Xx];
// 控制移动方向的枚举
enum Di{up,down,left,right};
// 跳转到此坐标位置输出
void goxy(SHORT x, SHORT y)
{
    COORD po = {(SHORT)(x*2), y};
    SetConsoleCursorPosition(Hc,po);
}
// 随机产生食物
void c_rand(int *f)
{
    srand((unsigned)time(NULL));
    f[0] = rand()%(Xx-4) + 2;
    f[1] = rand()%(Yy-4) + 2;
    f[2] = 1;
}
// 隐藏光标
void hide()
{
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(Hc, &cci);
    cci.bVisible = 0;
    SetConsoleCursorInfo(Hc, &cci);
}
// 构造和蛇行为有关的类
class Snake
{
    int food[3];
    enum Di fx;   //蛇运动方向
    int sl;    //蛇身长度
    typedef struct _sbody{
        int x;          //储存蛇身坐标
        int y;
    }sbody; sbody *sbd;
    // 蛇尾
    sbody tail;

public:
    Snake(int sl = 3){
        this->sl = sl;
    }
    ~Snake(){
        for(int i = 0;i<sl;i++)
            free(&sbd[i]);
    }
    // 蛇长度接口
    int getlen(){   return sl;  }
    // 食物状态接口
    int fdstatus(){ return food[2];  }
    void init();
    void setfx(char f);
    bool eat();
    bool pd_over();
    void smove();
    void newfood();
    void sfree();
};
// 初始化
void Snake::init()
{
    fx = up;
    hide();
    // 设置窗口大小
    system("mode con: cols=92 lines=34");

    // 初始化基础地图
    for(int i = 0;i < Yy;i++){
        for(int j = 0;j < Xx;j++){
            Color(Hc,001);
            if(i == 0 || j == 0 || i == Yy - 1 || j == Xx - 1)  Color(Hc,255);
            if(i == 1 || j == 1 || i == Yy - 2 || j == Xx - 2)  Color(Hc,2);
            std::cout << "■";
        }
        std::cout << std::endl;
    }
    // 初始化蛇身位置
    sbd = (sbody*)calloc(sl,sizeof(sbody));
    sbd[0].x = Xx/2 - 1;   sbd[0].y = Yy/2 - 1;
    for(int i = 0;i < sl;i++){
            sbd[i].x = sbd[0].x;
            sbd[i].y = sbd[0].y + i;
            goxy(sbd[i].x,sbd[i].y);
            Color(Hc,4); std::cout << "●";
    }
    // 初始化食物位置
    newfood();
}

// 获取并修改移动方向
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
// 判断是否吃到食物
bool Snake::eat()
{
    if(sbd[0].x == food[0] && sbd[0].y == food[1]){
        food[2] = 0;
        return true;
    }else
        return false;
}
// 当蛇越界或蛇头碰到蛇身时结束游戏
bool Snake::pd_over()
{
    if(sbd[0].y - 1 == 0 || sbd[0].y + 1 == Yy - 1 || sbd[0].x - 1 == 0 || sbd[0].x + 1 == Xx - 1)  return true;

    for(int i = 1;i<sl;i++)
        if(sbd[0].x == sbd[i].x && sbd[0].y == sbd[i].y){
            return true;
        }
    return false;
}
// 核心函数 控制蛇的移动
void Snake::smove()
{
    bool fll = eat();
    tail = sbd[sl-1];
    // 清除蛇尾
    goxy(tail.x,tail.y); Color(Hc,001); std::cout << "■";

    Color(Hc,4);
    // 蛇身前移
    for(int i=sl-1;i>0;i--){
        sbd[i] = sbd[i-1];
    }
    // 重绘蛇头
    switch(fx)
    {
        case up:
            goxy(sbd[0].x,--sbd[0].y); std::cout << "●";  break;
        case down:
            goxy(sbd[0].x,++sbd[0].y); std::cout << "●";  break;
        case left:
            goxy(--sbd[0].x,sbd[0].y); std::cout << "●";  break;
        case right:
            goxy(++sbd[0].x,sbd[0].y); std::cout << "●";  break;
    }
    // 吃到食物增加蛇长度
    if(fll){
        sbd = (sbody*)realloc(sbd,++sl*sizeof(sbody));
        sbd[sl-1] = tail;
    }
}
// 生成新的食物
void Snake::newfood()
{
    rebuild:
        c_rand(food);
        for(int i = 0;i<sl;i++){
            if(sbd[i].x == food[0] && sbd[i].y == food[1]) // 避免食物出现在蛇身体上
                goto rebuild;
        }
    goxy(food[0],food[1]); Color(Hc,14);  std::cout << "★";
}

#endif
