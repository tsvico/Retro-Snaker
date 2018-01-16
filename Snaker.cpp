/*****************
人工智能版贪吃蛇
2017/7/25
编译器vs2015
*************************/
#include <iostream>
#include <graphics.h>
#include <conio.h>  //getch()
#include<mmstream.h>

#include <time.h>  //随机数头文件
#pragma comment(lib,"winmm.lib")

using namespace std;

/************************************************************************/

IMAGE blank, snakeHead, snakeImage, Snake1, SnakeOver;
//枚举方向
typedef enum Ch { up = 72, down = 80, left = 75, right = 77 } CH;
typedef struct Cool
{
	int x;
	int y;

}COOR;

struct Snake
{
	CH ch; //枚举方向
	int n;  //节数
	COOR scr[100];
}snake;

struct Food
{
	COOR fcr;
	int isEat;  //标记食物是否被吃
}food;

void GameInit();
void DrawSnake();
void SnakeMove();
void ChangCh();
void DrawFood();
void coorFood();
void EatFood();
void Gameover();
void BreakGame();
int main()
{
	GameInit();
	while (1)
	{
		if (food.isEat == 0)
		{
			coorFood();
		}
		/*while(1)
		{ for (int i = 0; i < 640; i += 10)
		{
		moveto(0, i), lineto(640,  i);
		}
		}*/


		while (!kbhit())
		{
			Sleep(100);
			cleardevice();

			DrawSnake();
			SnakeMove();
			BreakGame();
			DrawFood();
		}
		ChangCh();
	}

	getch();
	return 0;
}
void GameInit()
{
	initgraph(640, 480);
	srand((unsigned int)time(NULL));

	mciSendString(L"open ./甩葱歌.mp3 alias gaowenjie", 0, 0, 0);
	mciSendString(L"play gaowenjie repeat", 0, 0, 0);
	//L 宽字符
	//初始化一条小蛇
	/*loadimage(&blank, L"./snake/blank.jpg", 640, 480);
	loadimage(&Snake1, L"./snake/snake,jpg", 640, 480);
	loadimage(&snakeHead, L"./snake/SnakeHead.png", 60, 60);
	loadimage(&snakeImage, L"./image/end.gif", 60, 60);
	loadimage(&SnakeOver, L"./image/SnakeOver.png", 640, 480);
*/


	setfillcolor(YELLOW);
	solidrectangle(0, 0, 10, 10);  //画矩形  加solid石信
								   //rectangle(0, 0, 10, 10);

	snake.n = 2;
	snake.scr[0].x = 0;
	snake.scr[0].y = 0;
	snake.ch = Ch::right; //往下走
	putimage(0, 0, &blank);

	//食物
	food.isEat = 0;
}
void DrawSnake()
{
	for (int i = 0; i< snake.n; i++)
	{
		solidrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + 10, snake.scr[i].y + 10);

	}
}
void SnakeMove()
{
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.scr[i].x = snake.scr[i - 1].x;   //传递
		snake.scr[i].y = snake.scr[i - 1].y;
	}

	//只要改变蛇头坐标
	switch (snake.ch)
	{
	case up:
		snake.scr[0].y -= 10;
		break;
	case down:
		snake.scr[0].y += 10;
		break;
	case Ch::left:
		snake.scr[0].x -= 10;
		break;
	case Ch::right:
		snake.scr[0].x = snake.scr[0].x + 10;
		break;
	}
	EatFood();
}
void ChangCh()
{
	int move;
	move = getch();
	switch (move)
	{
	case 'W':
	case'w':
	case Ch::up:
		if (snake.ch != Ch::down)
			snake.ch = Ch::up;
		break;
	case 'S':
	case's':
	case Ch::down:
		if (snake.ch != Ch::up)
			snake.ch = Ch::down;
		break;

	case 'A':
	case 'a':
	case Ch::left:
		if (snake.ch != Ch::right)
			snake.ch = Ch::left;
		break;
	case 'D':
	case 'd':
	case Ch::right:
		if (snake.ch != Ch::left)
			snake.ch = Ch::right;
		break;
	default:
		break;
	}
}
void coorFood()
{
	food.fcr.x = rand() % 64 * 10;
	food.fcr.y = rand() % 48 * 10;

	food.isEat = 1;
}
void DrawFood()
{
	solidroundrect(food.fcr.x, food.fcr.y, food.fcr.x + 10, food.fcr.y + 10, 10, 10);
}
void EatFood()
{
	if (snake.scr[0].x == food.fcr.x&&snake.scr[0].y == food.fcr.y)
	{
		snake.n++;
		food.isEat = 0;
	}
}
void BreakGame()
{
	if (snake.scr[0].x < 0 || snake.scr[0].x>640 ||
		snake.scr[0].y < 0 || snake.scr[0].y>480)
	{
		//closegraph();
		Gameover();
	}
	if (snake.n>3)
	{
		for (int i = snake.n - 1; i>0; i--)
		{
			if (snake.scr[0].x == snake.scr[i].x&&snake.scr[0].y == snake.scr[i].y)
			{
				Gameover();
			}
		}
	}
}
void Gameover()
{
	cleardevice();
	settextcolor(GREEN);
	settextstyle(40, 0, L"华文琥珀");
	outtextxy(40, 80, L"你输了");
	while (getch)
	{
		cleardevice();  //清屏
		outtextxy(20, 80, L"你输了");
		circle(320, 240, rand() % 240);  // 画圆
		rectangle(rand() % 360, rand() % 240, rand() % 360, rand() % 240);
		Sleep(25);
		//exit(0);
	}

}