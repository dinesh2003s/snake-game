#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

//inital vairables
bool snakegame;

const int height = 25; 
const int width = 25;
//target vairables
int targetx, targety;
//user vairables
int x, y,spd=1;
int score;
//tail vairables
int tailx[100], taily[100];
int taillenght = 0;
int fposx, fposy, sposx, sposy;
//directions
enum direction { stop = 0, up, down,  lift, RIGHT };
direction dir;
 

void game_setup()
{
	snakegame = true;
	dir = stop;
	//snake head
	x = rand() % width;
	y = rand() % height;
	//fruit apperence
	targetx= rand() % width;
	targety= rand() % height;
	//error if snake head and fruit get same place
	while (targetx==x && targety==y)
	{
		x= rand() % width;
		y = rand() % height;
		targetx = rand() % width;
		targety = rand() % height;
	}
	//score
	score = 0;
}
void game_window()
{
	system("cls");
	//snake box
	for (int i = 0; i < width; i++)
	{
		cout << "*";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for(int j=0;j<width;j++)
		{
			if (j==0||j==width-1)
			{
				cout << "*";
			}
			else if (i==y&&j==x)
			{
				cout << "S";
			}
			else if (targety==i&&targetx==j)
			{
				cout << "O";
			}
			else
			{
				bool tail = false;
				for (int k = 0; k < taillenght; k++)
				{
					if(j==tailx[k]&&i==taily[k])
					{
						cout << "s";
						tail = true;
					}
					
				}
				if (!tail)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	for (int i = 0; i < height; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "scoure: "<<score;
}
void game_input()
{
	if (_kbhit())
	{   
		//snake direction change controls
		switch (_getch())
		{
		    case 'a':
				if (dir != RIGHT)
				{
					dir = lift;
				}
				break;
			case's':
				if (dir!=up)
				{
					dir = down;
				}
				break;
			case 'd':
				if (dir!=lift)
				{
					dir = RIGHT;
				}
				break;
			case'w':
				if (dir!=down)
				{
					dir = up;
				}
				break;
			case '0':
				snakegame = false;

		}
	}
}
void game_program()
{  
	//tail directions
	fposx = tailx[0];
	fposy = taily[0];
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < taillenght; i++)
	{
		sposx = tailx[i];
		sposy = taily[i];
		tailx[i] = fposx;
		taily[i] = fposy;
		fposx = sposx;
		fposy = sposy;
	}
	//snake directions movement
	switch (dir)
	{
	
	case up:
		y -= spd;
		break;
	case down:
		y += spd;
		break;
	case lift:
		x -= spd;
		break;
	case RIGHT:
		x += spd;
		break;
	
	}
	//game over
	if (x<=0||x>=width-1||y<0||y>height-1)
	{
		snakegame = false;
	}
	for (int i = 0; i < taillenght; i++)
	{
		if(x==tailx[i]&&y==taily[i]) 
		{
			snakegame = false;
		}
	}
	//fruit apperence
	if (x==targetx&&y==targety)
	{
		score++;
		taillenght++;
		targetx = rand() % width;
		targety = rand() % height;
		
	}
}
int main()
{
	
		game_setup();
		while (snakegame == true)
		{
			game_window();
			game_input();
			game_program();
			Sleep(50);
		}
	
	return 0;
}
