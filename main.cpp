#include<curses.h>
#include<unistd.h>
#include<ctime>
#include<iostream>
#include<cmath>
using namespace std;
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
int Num[4][4],num[4][4];
int Color[11]={0,1,1,2,2,3,3,4,4,5,5};
void Color_init(){
	for(int i=1;i<8;i++)
		init_pair(i,i,0);
	init_pair(8,COLOR_WHITE,COLOR_RED);
	init_pair(9,0,COLOR_GREEN);
}
void GetNewNumber(){	//生成新数字
	int x=rand()%4,y=rand()%4;
	while(Num[x][y]!=0){
		x=rand()%4,y=rand()%4;
	}
	int Get_Two=rand()%10;
	Num[x][y]=!Get_Two?4:2;
}
void MoveRight(){		//数字右移
	for(int i=0;i<4;i++){
		for(int j=3;j>0;j--){
			if(Num[i][j]!=0)
				continue;
			for(int k=j-1;k>=0;k--)
				if(Num[i][k]!=0){
					swap(Num[i][j],Num[i][k]);
					break;
				}
		}
	}
}
void MoveLeft(){		//数字左移
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			if(Num[i][j]!=0)
				continue;
			for(int k=j+1;k<4;k++)
				if(Num[i][k]!=0){
					swap(Num[i][j],Num[i][k]);
					break;
				}
		}
	}
}
void MoveDown(){		//数字下移
	for(int j=0;j<4;j++){
		for(int i=3;i>0;i--){
			if(Num[i][j]!=0)
				continue;
			for(int k=i-1;k>=0;k--)
				if(Num[k][j]!=0){
					swap(Num[i][j],Num[k][j]);
					break;
				}
		}
	}
}
void MoveUp(){			//数字上移
	for(int j=0;j<4;j++){
		for(int i=0;i<3;i++){
			if(Num[i][j]!=0)
				continue;
			for(int k=i+1;k<4;k++)
				if(Num[k][j]!=0){
					swap(Num[i][j],Num[k][j]);
					break;
				}
		}
	}
}
int main(){
    initscr();		//初始化窗口
    noecho();		//可视化输入字符
    cbreak();		//开启字符输入
    srand(time(0));	//初始化随机数
	curs_set(0);	//隐藏光标
	start_color();
	Color_init();
	// init_pair(1, COLOR_WHITE, COLOR_RED);
	// attron(COLOR_PAIR(1));
    keypad(stdscr, TRUE);
    clear();
    int key=0;

    GetNewNumber();
    GetNewNumber();
    while(key!=ERR&&key!='q'){
    	// move(40,40);
    	// printw("%d %d\n",key,KEY_RIGHT);

    	memcpy(num,Num,sizeof(Num));

	    if(key==KEY_RIGHT){		//按右键
	    	MoveRight();
	    	for(int j=3;j>=1;j--)
	    		for(int i=0;i<4;i++)
	    			if(Num[i][j]==Num[i][j-1])
	    				Num[i][j]<<=1,Num[i][j-1]=0;
	    	MoveRight();
	    }
	    else if(key==KEY_LEFT){	//按左键
	    	MoveLeft();
	    	for(int j=0;j<3;j++)
	    		for(int i=0;i<4;i++)
	    			if(Num[i][j]==Num[i][j+1])
	    				Num[i][j]<<=1,Num[i][j+1]=0;
	    	MoveLeft();
	    }
	    else if(key==KEY_UP){	//按上键
	    	MoveUp();
	    	for(int i=0;i<3;i++)
	    		for(int j=0;j<4;j++)
	    			if(Num[i][j]==Num[i+1][j])
	    				Num[i][j]<<=1,Num[i+1][j]=0;
	    	MoveUp();
	    }
	    else if(key==KEY_DOWN){	//按下键
	    	MoveDown();
	    	for(int i=3;i>0;i--)
	    		for(int j=0;j<4;j++)
	    			if(Num[i][j]==Num[i-1][j])
	    				Num[i][j]<<=1,Num[i-1][j]=0;
	    	MoveDown();
	    }

	    int Changed=0,win=0,lose=1;
	    for(int i=0;i<4;i++){
	    	for(int j=0;j<4;j++){
	    		if(Num[i][j]!=num[i][j])
	    			Changed=1;
	    		if(Num[i][j]==2048)
	    			win=1;
	    		if(Num[i][j]==0)
	    			lose=0;
	    	}
	    }
	    if(Changed)			//如果所有数字都没有移动，就不再生成新数字	
	    	GetNewNumber();
	    erase();
	    move(0,0);
	   	for(int i=0;i<9;i++)
	   		mvprintw(i,0,GameBox[i]);
	   	for(int i=0;i<4;i++){
	        for(int j=0;j<4;j++){
	            if(Num[i][j]==0)
	            	continue;
	            // move(2*i+1,1+6*j);
	            attron(COLOR_PAIR(Color[(int)log2(Num[i][j])]));
	            mvprintw(2*i+1,1+6*j,"%d",Num[i][j]);
	        	attroff(COLOR_PAIR(Color[(int)log2(Num[i][j])])); 
	        }
	    }

	    if(win){
	    	attron(COLOR_PAIR(8));
	    	mvprintw(4,8,"You Win");
	    	attroff(COLOR_PAIR(8));
	    }
	    else if(lose){
	    	attron(COLOR_PAIR(8));
	    	mvprintw(4,8,"Game Over");
	    	attroff(COLOR_PAIR(8));
	    }
	    
	    attron(COLOR_PAIR(9));
	    mvprintw(10,0,"Press 'r' to reset,Press 'q' to quit");
	    attroff(COLOR_PAIR(9));

	    key=getch();
	    if(key=='q')
	    	break;
	    if(key=='r'){
	    	memset(Num,0,sizeof(Num));
	    	GetNewNumber();
	    	GetNewNumber();
	    }
	}
    endwin();
    exit(EXIT_SUCCESS);
    return 0;
}
