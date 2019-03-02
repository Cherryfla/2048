#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
const int N=4;
const char GameBox[10][30]={
    "+-----+-----+-----+-----+\n",
    "|     |     |     |     |\n",
    "+-----+-----+-----+-----+\n",
    "|     |     |     |     |\n",
    "+-----+-----+-----+-----+\n",
    "|     |     |     |     |\n",
    "+-----+-----+-----+-----+\n",
    "|     |     |     |     |\n",
    "+-----+-----+-----+-----+\n",
};
int a[4][4];
int main(){
    initscr();//初始化窗口
    noecho();//可视化输入字符
    cbreak();//开启字符输入

    for(int i=0;i<9;i++)
        addstr(GameBox[i]);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            move(2*i+1,1+6*j);
            printw("%d",a[i][j]);
        }
    }

    refresh();
    sleep(10);
    endwin();
    exit(EXIT_SUCCESS);
    return 0;
}
