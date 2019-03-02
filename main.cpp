#include<curses.h>
#include<unistd.h>
#include<ctime>
#include<iostream>
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
int Num[4][4];
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
				if(Num[i][k]!=0)
					swap(Num[i][j],Num[i][k]);
		}
	}
}
void MoveLeft(){		//数字左移
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			if(Num[i][j]!=0)
				continue;
			for(int k=j+1;k<4;k++)
				if(Num[i][k]!=0)
					swap(Num[i][j],Num[i][k]);
		}
	}
}
void MoveDown(){		//数字下移
	for(int j=0;j<4;j++){
		for(int i=3;i>0;i--){
			if(Num[i][j]!=0)
				continue;
			for(int k=i-1;k>=0;k--)
				if(Num[k][j]!=0)
					swap(Num[i][j],Num[k][j]);
		}
	}
}
void MoveUp(){			//数字上移
	for(int j=0;j<4;j++){
		for(int i=0;i<3;i++){
			if(Num[i][j]!=0)
				continue;
			for(int k=i+1;k<4;k++)
				if(Num[k][j]!=0)
					swap(Num[i][j],Num[k][j]);
		}
	}
}
int main(){
    initscr();		//初始化窗口
    noecho();		//可视化输入字符
    cbreak();		//开启字符输入
    srand(time(0));	//初始化随机数
	curs_set(0);//隐藏光标

    keypad(stdscr, TRUE);
    clear();
    int key=0;

    GetNewNumber();
    GetNewNumber();
    while(key!=ERR&&key!='q'){
    	// move(40,40);
    	// printw("%d %d\n",key,KEY_RIGHT);
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
	    	for(int i=3;i>=1;i--)
	    		for(int j=0;j<4;j++)
	    			if(Num[i][j]==Num[i-1][j])
	    				Num[i][j]<<=1,Num[i-1][j]=0;
	    	MoveUp();
	    }
	    else if(key==KEY_DOWN){	//按下键
	    	MoveDown();
	    	for(int i=0;i<3;i++)
	    		for(int j=0;j<4;j++)
	    			if(Num[i][j]==Num[i+1][j])
	    				Num[i][j]<<=1,Num[i+1][j]=0;
	    	MoveDown();
	    }

	    GetNewNumber();
	    erase();
	    move(0,0);
	   	for(int i=0;i<9;i++)
	   		mvprintw(i,0,GameBox[i]);
	   	for(int i=0;i<4;i++){
	        for(int j=0;j<4;j++){
	            if(Num[i][j]==0)
	            	continue;
	            move(2*i+1,1+6*j);
	            printw("%d",Num[i][j]);
	        }
	    }
	    key=getch();
	}
    endwin();
    exit(EXIT_SUCCESS);
    return 0;
}
