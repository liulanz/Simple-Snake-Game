#include <iostream>
#include <conio.h> // use for input 
#include <Windows.h>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y; // head position
int fruitX, fruitY; // fruit position
int score;
int tailX[100], tailY[100];
int nTail; //specify how long is the tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


void Setup()
{
	gameOver = false;
	dir = STOP; // snake will not move until user enter an input
	//snake will start in the middle of the map
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls"); // commmand for clearing screen on window
	for (int i = 0; i < width + 2; i++) // print the top wall
		cout << "#";
	cout << endl;

	// print the map
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (w == 0)
				cout << "#";
			if (h == y && w == x) // print "O" represents head
				cout << "O";
			else if (h == fruitY && w == fruitX) // print "F" represents fruit
				cout << "F"; 
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					
					if (tailX[k] == w && tailY[k] == h)
					{
						cout << "o";
						print = true;
					}
					
				}
				if (!print)
					cout << " ";

			}

			if (w == width - 1)
				cout << "#";
		}
		cout << endl;

	}
	for (int i = 0; i < width + 2; i++) // print the bottom wall
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl; 

}
void Input()
{
	if (_kbhit()) //_kbhit() return 1 if keyboard is pressed else return 0
	{
		switch (_getch()) // _getch() will return ascii value of character that was pressed on keyboard
		{
			// a - left
			// w - up
			// d - right
			// s - down
			case 'a':
				dir = LEFT;
				break;
			case 'w':
				dir = UP;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				gameOver = true;
				break;

		}
	}
}
void Logic()
{
	
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) // moving tail with head
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
/*	if (x > width || x < 0 || y > height || y < 0) // if head hit the wall, program terminates
		gameOver = true;
*/
	//Allows the snake to hit the wall and enter from the other side of the wall
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
	if (x == fruitX && y == fruitY)  // if eats the fruit score, increment by 10
	{
		
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}


int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic(); // makes snake move slower
		Sleep(10);
	}
	return 0;
}