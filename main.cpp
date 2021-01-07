/***************************************

	文件名称：main.cpp
	程序名称：贪吃蛇
	编译环境：VS2019 && Easyx
	作者相关：小光头
	最后修改：2020/1/7

****************************************/
//包含头文件
#include<stdio.h>
#include<graphics.h>//图形库头文件
#include<conio.h>
#include<time.h>
#include<mmsystem.h> //多媒体设备接口：音乐 视频 麦克风
#pragma comment(lib, "winmm.lib")

#define SNAKELENGTH 100		//蛇的最大长度
#define SNAKESIZE 10	//蛇的大小

void InitSnake();
void DrawSnake();
void MoveSnake();
void ChangeSnake();
void DrawFood();
void CoorFood();
int EatFood();
void BreakSnake();
void OverSnake();

typedef enum ch
{
	up = 72,
	down = 80,
	left = 75,
	right = 77
}CH;
//定义坐标结构体
struct Coor
{
	int x;
	int y;
}COOR;

//定义蛇的结构体 //蛇的属性： 长度 坐标 方向
struct Snake
{
	Coor szb[SNAKELENGTH];		//蛇每一节的坐标
	int n;	//蛇的当前长度
	CH ch;	//蛇的方向
}SNAKE;

// 定义食物的结构体
struct Food
{
	Coor fzb;
	int flag;  //标志 flag=0 食物没有被吃 flag=1 食物被吃
}FOOD;

//主函数
int main() 
{
	int flag = 0;
	InitSnake();
	while (1) 
	{
		while (!_kbhit())
		{
			if(flag == 0){
			
				CoorFood();
			}
			DrawFood();
			BreakSnake();
			MoveSnake();
			flag = EatFood();
			Sleep(100);
			
		}
		ChangeSnake();
	}
	//getchar();
	return 0;
}
//初始化函数
void InitSnake()
{
	initgraph(640, 480,SHOWCONSOLE);
	//circle(320,240,160);
	//rectangle(160,80,480,400);

	mciSendString(L"open 莫扎特小夜曲.mp3 alias bk",0,0,0);
	mciSendString(L"Play bk repeat", 0, 0, 0);

	setbkcolor(RGB(10,20,150));
	cleardevice();

	rectangle(0, 0, 10, 10);	//一条小蛇
	SNAKE.szb[0].x = 0;
	SNAKE.szb[0].y = 0;
	SNAKE.n = 1;
	SNAKE.ch = right;

	FOOD.flag = 0;
	
}

//在界面上画蛇
void DrawSnake() 
{
	for (int i = SNAKE.n-1; i >= 0; i--)
	{
		rectangle(SNAKE.szb[i].x, SNAKE.szb[i].y, SNAKE.szb[i].x + SNAKESIZE, SNAKE.szb[i].y + SNAKESIZE);
	}

	setcolor(RGB(10, 20, 150));
	rectangle(SNAKE.szb[SNAKE.n].x,SNAKE.szb[SNAKE.n].y, SNAKE.szb[SNAKE.n].x+SNAKESIZE, SNAKE.szb[SNAKE.n].y+SNAKESIZE);
	setcolor(RGB(255, 255, 255));
	rectangle(SNAKE.szb[SNAKE.n - 1].x, SNAKE.szb[SNAKE.n - 1].y, SNAKE.szb[SNAKE.n - 1].x + SNAKESIZE, SNAKE.szb[SNAKE.n - 1].y + SNAKESIZE);
}

//蛇移动
void MoveSnake()
{
	for (int i = SNAKE.n; i > 0; i--) 
	{
		SNAKE.szb[i].x = SNAKE.szb[i - 1].x;
		SNAKE.szb[i].y = SNAKE.szb[i - 1].y;
	}
	switch (SNAKE.ch) 
	{
		case up:  
			SNAKE.szb[0].y -= SNAKESIZE;
			break;
		case down:
			SNAKE.szb[0].y += SNAKESIZE;
			break;
		case left:
			SNAKE.szb[0].x -= SNAKESIZE;
			break;
		case right:
			SNAKE.szb[0].x += SNAKESIZE;
			break;
	}
	DrawSnake();
}

//接受键盘
void ChangeSnake()
{
	int move;
	//getchar() getch() getchar()需要按下回车键 getch()不需要按回车
	move = _getch();
	

	switch (move)	//move 整型变量 void *(*p[]) ()
	{
		case up:
			if (SNAKE.ch != down)
			{
				SNAKE.ch = up;
			}
			break;
		case down:
			if (SNAKE.ch != up)
			{
				SNAKE.ch = down;
			}
			break;
		case left:
			if (SNAKE.ch != right)
			{
				SNAKE.ch = left;
			}
			break;
		case right:
			if (SNAKE.ch != left)
			{
				SNAKE.ch = right;
			}
			break;
	}
}

//画食物
void DrawFood()
{
	setcolor(WHITE);
	 
	roundrect(FOOD.fzb.x, FOOD.fzb.y, FOOD.fzb.x + SNAKESIZE, FOOD.fzb.y + SNAKESIZE, 10, 10);
}

//计算食物的坐标
void CoorFood()
{
	srand(unsigned (time(NULL)));

	FOOD.fzb.x = rand() % (640 / SNAKESIZE) * SNAKESIZE;
	FOOD.fzb.y = rand() % (480 / SNAKESIZE) * SNAKESIZE;

	FOOD.flag = 1;
}

//吃食物
int EatFood()
{
	if (SNAKE.szb[0].x == FOOD.fzb.x && SNAKE.szb[0].y == FOOD.fzb.y)
	{
		SNAKE.n++;
		setcolor(RGB(10, 20, 150));
		roundrect(FOOD.fzb.x, FOOD.fzb.y, FOOD.fzb.x + SNAKESIZE, FOOD.fzb.y + SNAKESIZE, 10, 10);
		setcolor(WHITE);

		FOOD.flag = 0;
		return FOOD.flag;
	}
	return 1;
}

//判断是否越界
void BreakSnake()
{
	if (SNAKE.szb[0].x < 0 || SNAKE.szb[0].x > 640 || SNAKE.szb[0].y < 0 || SNAKE.szb[0].y > 480)	//撞墙
	{
		OverSnake();
	}

	for (int i = SNAKE.n-2; i > 0; i--)	//撞自己
	{
		if (SNAKE.szb[0].x == SNAKE.szb[i].x && SNAKE.szb[0].y == SNAKE.szb[i].y)
		{
			OverSnake();
		}
	}
}

//结束界面
void OverSnake()
{
	cleardevice();
	setcolor(YELLOW);
	settextstyle(20, 0, L"华文新魏");
	outtextxy(80, 100, L"  为了您和家人的健康，请合理控制游戏时间 ");
	outtextxy(150, 160, L"  游戏结束  ");

	getchar();
	closegraph();
}