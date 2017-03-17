#include "snake.h"
#include "score.h"
#include <ctime>
using namespace std;
void Info(int num)
{
    goxy(32,0); Color(Hc,255);
    cout << "■■■■■■■■■■■■■■";
    Color(Hc,15);   goxy(35,5);
    cout << "W上 S下 A左 D右";
    goxy(34,7);
    cout << "空格暂停  B重新开始";
    goxy(36,16);
    cout << "最高记录：";
    Color(Hc,12);   cout << num;
    Color(Hc,15);
    goxy(36,18);
    cout << "当前得分：" << 0;
    goxy(36,25);
    cout << "蛇身长度：" << 3;
    goxy(35,27);
    cout << "游戏已开始 " << 0 << " 秒";
    goxy(32,31); Color(Hc,255);
    cout << "■■■■■■■■■■■■■■";
    Color(Hc,000);
}
void set_sc(Score &S,int *sc,int sl)
{
    sc[0] = 10*(sl - 3);
    sc[2] = sc[0]>sc[1]?sc[0]:sc[1];
    if(sc[1] != sc[2]){
        S.write_s();
        goxy(41,16);    Color(Hc,12);
        cout << sc[2];
        if(sc[1] != 0){
            sc[3]++;
            goxy(35,20);
            if(sc[3] < 15)
                Color(Hc,14);
            else
                Color(Hc,000);
            cout << " 打破记录了！！！";
        }
    }
    goxy(41,18);    Color(Hc,15);
    cout << sc[0];
}
int main()
{
    char ch;
    restart:
        time_t start;
        Score Sr;
        int *s = Sr.get_s();
        Sr.read_s();

        Snake Sk;
        Sk.init();
        Info(s[1]);
        ch = getch();
        start = time(NULL);
    while(ch != 27){
        if(!Sk.fdstatus()){
            Sk.newfood();
        }
        Sleep(300 - Sk.getlen()*5);  //控制蛇运动速度
        if (kbhit()){
            ch = getch();
        }
        Sk.setfx(ch);
        goxy(40,27);    Color(Hc,15);
        cout << " " << (int)(time(NULL) - start) << " 秒";
        if(ch == 32){
            goxy(37,10);    Color(Hc,14);   cout << "暂  停";
            continue;
        }else if(ch == 'B' || ch == 'b'){
            goto restart;
        }
        goxy(37,10);    Color(Hc,10);   cout << "游戏中";
        Sk.smove();
        if(Sk.pd_over())
        {
            goxy(Xx/2 - 3,Yy/2);
            cout << " GAME OVER ";
            goxy(36,10);    Color(Hc,12);   cout << " 游戏结束";
            break;
        }

        int slen = Sk.getlen();
        set_sc(Sr,s,slen);
        if(slen > 50){
            goxy(34,20);    Color(Hc,9);
            if(slen > 53) Color(Hc,000);
            cout << "天哪 你这是什么手速！";
        }
        if(slen > 65){
            goxy(34,20);
            if(slen > 63) Color(Hc,000);
            cout << "卧槽 你已经超越神了！";
        }
        if(slen > 95){
            goxy(33,20);
            cout << "绝对不会有人比你更厉害了！";
        }
        goxy(41,25); Color(Hc,15);    cout << slen;
    }
    reb:
        ch = getch();
        if(ch == 'b' || ch == 'B'){
            goto restart;

        }else if(ch == 'w' || ch == 'W' || ch == 's' || ch == 'S' || ch == 'a' || ch == 'A' || ch == 'd' || ch == 'D')
        {
            goto reb;
        }
    getch();
    return 0;
}
