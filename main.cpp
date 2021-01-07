/***************************************

	�ļ����ƣ�main.cpp
	�������ƣ�̰����
	���뻷����VS2019 && Easyx
	������أ�С��ͷ
	����޸ģ�2020/1/7

****************************************/
//����ͷ�ļ�
#include<stdio.h>
#include<graphics.h>//ͼ�ο�ͷ�ļ�
#include<conio.h>
#include<time.h>
#include<mmsystem.h> //��ý���豸�ӿڣ����� ��Ƶ ��˷�
#pragma comment(lib, "winmm.lib")

#define SNAKELENGTH 100		//�ߵ���󳤶�
#define SNAKESIZE 10	//�ߵĴ�С

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
//��������ṹ��
struct Coor
{
	int x;
	int y;
}COOR;

//�����ߵĽṹ�� //�ߵ����ԣ� ���� ���� ����
struct Snake
{
	Coor szb[SNAKELENGTH];		//��ÿһ�ڵ�����
	int n;	//�ߵĵ�ǰ����
	CH ch;	//�ߵķ���
}SNAKE;

// ����ʳ��Ľṹ��
struct Food
{
	Coor fzb;
	int flag;  //��־ flag=0 ʳ��û�б��� flag=1 ʳ�ﱻ��
}FOOD;

//������
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
//��ʼ������
void InitSnake()
{
	initgraph(640, 480,SHOWCONSOLE);
	//circle(320,240,160);
	//rectangle(160,80,480,400);

	mciSendString(L"open Ī����Сҹ��.mp3 alias bk",0,0,0);
	mciSendString(L"Play bk repeat", 0, 0, 0);

	setbkcolor(RGB(10,20,150));
	cleardevice();

	rectangle(0, 0, 10, 10);	//һ��С��
	SNAKE.szb[0].x = 0;
	SNAKE.szb[0].y = 0;
	SNAKE.n = 1;
	SNAKE.ch = right;

	FOOD.flag = 0;
	
}

//�ڽ����ϻ���
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

//���ƶ�
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

//���ܼ���
void ChangeSnake()
{
	int move;
	//getchar() getch() getchar()��Ҫ���»س��� getch()����Ҫ���س�
	move = _getch();
	

	switch (move)	//move ���ͱ��� void *(*p[]) ()
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

//��ʳ��
void DrawFood()
{
	setcolor(WHITE);
	 
	roundrect(FOOD.fzb.x, FOOD.fzb.y, FOOD.fzb.x + SNAKESIZE, FOOD.fzb.y + SNAKESIZE, 10, 10);
}

//����ʳ�������
void CoorFood()
{
	srand(unsigned (time(NULL)));

	FOOD.fzb.x = rand() % (640 / SNAKESIZE) * SNAKESIZE;
	FOOD.fzb.y = rand() % (480 / SNAKESIZE) * SNAKESIZE;

	FOOD.flag = 1;
}

//��ʳ��
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

//�ж��Ƿ�Խ��
void BreakSnake()
{
	if (SNAKE.szb[0].x < 0 || SNAKE.szb[0].x > 640 || SNAKE.szb[0].y < 0 || SNAKE.szb[0].y > 480)	//ײǽ
	{
		OverSnake();
	}

	for (int i = SNAKE.n-2; i > 0; i--)	//ײ�Լ�
	{
		if (SNAKE.szb[0].x == SNAKE.szb[i].x && SNAKE.szb[0].y == SNAKE.szb[i].y)
		{
			OverSnake();
		}
	}
}

//��������
void OverSnake()
{
	cleardevice();
	setcolor(YELLOW);
	settextstyle(20, 0, L"������κ");
	outtextxy(80, 100, L"  Ϊ�����ͼ��˵Ľ���������������Ϸʱ�� ");
	outtextxy(150, 160, L"  ��Ϸ����  ");

	getchar();
	closegraph();
}