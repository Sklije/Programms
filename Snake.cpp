#include <iostream>
#include "windows.h"
#include <conio.h>
#include <iomanip>
using namespace std;

enum Direction { Up, Down, Left, Right }; //направления

struct Point {
	int x;
	int y;
	bool operator == (const Point& p) {
		return this->x == p.x && this->y == p.y;
	}
	bool operator != (const Point& p) {
		return this->x != p.x || this->y != p.y;
	}
};

struct Food {  //еда
	Point Dis;
	int Taste;
	bool valid;
};

bool Snake_Part(Point* Snake, int Lenght, int Y, int X) {
	for (int m = 0; m < Lenght; m++) {
		if (Snake[m].y == Y && Snake[m].x == X) return true;

	}
	return false;
}

void FoodPosition(Point* Snake, Food& eda, int maxX, int maxY, int Lenght) { //размещение еды
	bool Position = false;
	while (eda.valid != true) {
		eda.Taste = rand() % 9 + 1;
		eda.Dis.x = rand() % (maxX - 2) + 1;
		eda.Dis.y = rand() % (maxY - 2) + 1;
		for (int i = 0; i < Lenght; i++) {
			Position = true;
			if (Snake_Part(Snake, Lenght, eda.Dis.y, eda.Dis.x)) {
				Position = false;
			}
		}
		if (Position) eda.valid = true;
	}
}

void Move(Point* Snake, int Lenght, Direction directon) {   // движение
	if (Lenght == 2) {
		Snake[1] = Snake[0];
	}
	else Snake[1] = Snake[Lenght - 1];
	for (int i = Lenght; i > 2; i--) {
		Snake[i] = Snake[i - 1];
	}
	Snake[2] = Snake[0];
	if (directon == Direction::Up) Snake[0].y -= 1;
	else if (directon == Direction::Down) Snake[0].y += 1;
	else if (directon == Direction::Left) Snake[0].x -= 1;
	else Snake[0].x += 1;
}

void Move_long(Point* Snake, int& Lenght, Direction directon, int& Long) {// движение+рост
	if (Lenght == 2) {
		Snake[1] = Snake[0];
	}
	Snake[Lenght] = Snake[Lenght - 1];
	for (int i = Lenght - 1; i > 2; i--) {
		Snake[i] = Snake[i - 1];
	}
	Snake[2] = Snake[0];
	if (directon == Direction::Up) Snake[0].y -= 1;
	else if (directon == Direction::Down) Snake[0].y += 1;
	else if (directon == Direction::Left) Snake[0].x -= 1;
	else Snake[0].x += 1;
	Lenght += 1;
	Long -= 1;
}

bool OutOfBorder(int maxX, int maxY, Point Head) { // выход за границы
	return (Head.x <= 0 || Head.x >= maxX - 1 ||
		Head.y <= 0 || Head.y >= maxY - 1);
}

bool Death(Point* Snake, int Lenght) { // смерть
	for (int i = 1; i < Lenght - 1; i++) {
		if (Snake[0] == Snake[i]) {
			return true;
		}
	}
	return false;
}

bool Game_over(int maxX, int maxY, Point* Snake, int Lenght) {
	return (Death(Snake, Lenght) || OutOfBorder(maxX, maxY, Snake[0]));
}

void Draw(int maxX, int maxY, Point* Snake, Food eda, int Lenght) {
	for (int i = 0; i < maxY; i++) {
		for (int j = 0; j < maxX; j++) {
			if (Snake_Part(Snake, Lenght, i, j)) {
				if (Snake[0].y == i && Snake[0].x == j) cout << setw(2) << "@";
				else if (Snake[1].y == i && Snake[1].x == j) cout << setw(2) << "o";
				else cout << setw(2) << "u";
			}
			else {
				if (i == 0 || i == maxY - 1 || j == 0 || j == maxX - 1) cout << setw(2) << "*";
				else if (eda.Dis.y == i && eda.Dis.x == j) cout << setw(2) << "F";
				else cout << setw(2) << ".";
			}
		}
		cout << endl;
	}
}



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int X, Y, Lenght = 2, Count = 0;
	char key;
	Food eda;
	eda.valid = false;
	Direction dir = Direction::Right;
	cin >> Y >> X;

	Point* Snake = new Point[X * Y];
	Snake[0].x = X / 2;
	Snake[0].y = Y / 2;
	Snake[1].x = Snake[0].x - 1;
	Snake[1].y = Y / 2;

	while (!Game_over(X, Y, Snake, Lenght)) {
		Sleep(500);
		if (_kbhit()) {
			key = _getch();
			if (key == 'w' || key == 'ц') dir = Direction::Up;
			else if (key == 'a' || key == 'ф') dir = Direction::Left;
			else if (key == 's' || key == 'ы') dir = Direction::Down;
			else if (key == 'd' || key == 'в') dir = Direction::Right;
		}

		system("cls");
		if (Count == 0) {
			Move(Snake, Lenght, dir);
		}
		else {
			Move_long(Snake, Lenght, dir, Count);
		}
		if (Snake[0] == eda.Dis) {
			eda.valid = false;
			Count += eda.Taste;
		}
		if (!eda.valid) FoodPosition(Snake, eda, X, Y, Lenght);
		Draw(X, Y, Snake, eda, Lenght);
		Sleep(250);
	}
	system("cls");
	cout << "Game over";
	delete[] Snake;

	return 0;
}
