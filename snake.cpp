/********************************************************
 * Автор: Вяткин Владислав                              *
 * Дата: 13.12.2022                                     *
 * Название: Змейка                                     *  
 * Ссылка на OnlineGDB: https://onlinegdb.com/Au92VJPwO * 
 ********************************************************/

#include <iostream>
#include <ctime>
#include <conio.h> // console input/output
#include <windows.h>

using namespace std;

bool gameOver;

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score, nTail;
int tailX[100], tailY[100];

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void setup() {
	gameOver = false;
	dir = STOP;
	x = (width / 2) - 1;
	y = (height / 2) - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void draw() {
	system("cls");
	cout << "#";
	for (int xCoordinate = 1; xCoordinate <= width;
		++xCoordinate) {
		cout << " #";
	}
	cout << endl;

	for (int yCoordinate = 0; yCoordinate < height;
		++yCoordinate) {
		for (int xCoordinate = 0; xCoordinate < width;
			++xCoordinate) {
			if (xCoordinate == 0 || xCoordinate == width - 1) {
				cout << "#";
			}

			if (yCoordinate == y && xCoordinate == x) {
				cout << "0";
			} else if (yCoordinate == fruitY
				&& xCoordinate == fruitX) {
				cout << "@";
			} else {
				bool print = false;

				for (int tailIndex = 0; tailIndex < nTail;
					++tailIndex) {
					if (tailX[tailIndex] == xCoordinate
						&& tailY[tailIndex] == yCoordinate) {
						print = true;
						cout << "0";
					}
				}

				if (!print) {
					cout << " ";
				}
			}

			cout << " ";
		}

		cout << endl;
	}

	cout << "#";
	for (int xCoordinate = 0; xCoordinate <= width;
		++xCoordinate) {
		cout << " #";
	}
	cout << endl;
	cout << "SCORE: " << score << endl;
	setlocale(LC_ALL, "RUS");
	cout << "Управление: \n w — вверх\n s — вниз\n a — влево\n d — вправо\n";
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			if (dir != RIGHT) {
				dir = LEFT;
			}
			break;
		case 'd':
			if (dir != LEFT) {
				dir = RIGHT;
			}
			break;
		case 'w':
			if (dir != DOWN) {
				dir = UP;
			}
			break;
		case 's':
			if (dir != UP) {
				dir = DOWN;
			}
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void logic() {
	int prevX = tailX[0], prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int tailIndex = 1; tailIndex < nTail; ++tailIndex) {
		prev2X = tailX[tailIndex];
		prev2Y = tailY[tailIndex];

		tailX[tailIndex] = prevX;
		tailY[tailIndex] = prevY;

		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
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
	}

	if (x >= width - 1) {
		x = 0;
	} else if (x < 0) {
		x = width - 2;
	}

	if (y >= height) {
		y = 0;
	}
	else if (y < 0) {
		y = height - 1;
	}

	for (int tailIndex = 0; tailIndex < nTail; ++tailIndex) {
		if (tailX[tailIndex] == x && tailY[tailIndex] == y) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		++score;
		fruitX = rand() % width;
		fruitY = rand() % height;
		++nTail;
	}
}

int main() {
	setup();
	while (!gameOver) {
		draw();
		input();
		logic();
		Sleep(80);
	} 
}
