#include <iostream>
#include "windows.h"
#include <conio.h>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

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


bool Is_A_Box(Point* Box, int X, int Y, int Boxes) {
	for (int i = 0; i < Boxes; i++) {
		if (Box[i].x == X && Box[i].y == Y) {
			return true;
		}
	}
	return false;
}

int Box_Num(Point* Box, int X, int Y, int Boxes) {
	for (int i = 0; i < Boxes; i++) {
		if (Box[i].x == X && Box[i].y == Y) {
			return i;
		}
	}
	return -1;
}

bool Move_or_Push(int Dir, Point& Load, Point* Box, int Boxes) {
	if (Dir == 1 && Is_A_Box(Box, Load.x, Load.y - 1, Boxes)) {
		return false;
	}
	else if (Dir == 2 && Is_A_Box(Box, Load.x - 1, Load.y, Boxes)) {
		return false;
	}
	else if (Dir == 3 && Is_A_Box(Box, Load.x, Load.y + 1, Boxes)) {
		return false;
	}
	else if (Dir == 4 && Is_A_Box(Box, Load.x + 1, Load.y, Boxes)) {
		return false;
	}
	return true;
}

void Move(int Dir, Point& Load, string* Map/*, Point* Box, int Boxes*/) {
	if (Dir == 1 && (Map[Load.y - 1][Load.x] == '.' || Map[Load.y - 1][Load.x] == 'p')) {
		Load.y -= 1;
	}
	else if (Dir == 2 && (Map[Load.y][Load.x - 1] == '.' || Map[Load.y][Load.x - 1] == 'p')) {
		Load.x -= 1;
	}
	else if (Dir == 3 && (Map[Load.y + 1][Load.x] == '.' || Map[Load.y + 1][Load.x] == 'p')) {
		Load.y += 1;
	}
	else if (Dir == 4 && (Map[Load.y][Load.x + 1] == '.' || Map[Load.y][Load.x + 1] == 'p')) {
		Load.x += 1;
	}
}

void Push(int Dir, Point& Load, string* Map, Point& Box, int BNum) {
	if (BNum >= 0) {
		if (Dir == 1 && (Map[Load.y - 2][Load.x] == '.' || Map[Load.y - 2][Load.x] == 'p')) {
			Load.y -= 1;
			Box.y -= 1;
		}
		else if (Dir == 2 && (Map[Load.y][Load.x - 2] == '.' || Map[Load.y][Load.x - 2] == 'p')) {
			Load.x -= 1;
			Box.x -= 1;
		}
		else if (Dir == 3 && (Map[Load.y + 2][Load.x] == '.' || Map[Load.y + 2][Load.x] == 'p')) {
			Load.y += 1;
			Box.y += 1;
		}
		else if (Dir == 4 && (Map[Load.y][Load.x + 2] == '.' || Map[Load.y][Load.x + 2] == 'p')) {
			Load.x += 1;
			Box.x += 1;
		}
	}
}

void Draw(Point& Loader, string* Map, Point* Box, int X, int Y, int Boxes) {
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (i == Loader.y && j == Loader.x) {
				cout << setw(2) << "G";
			}
			else if (Is_A_Box(Box, j, i, Boxes)) {
				cout << setw(2) << "B";
			}
			else cout << setw(2) << Map[i][j];
		}
		cout << endl;
	}
}

int Direction(char Key) {
	if (Key == 'w') {
		return 1;
	}
	else if (Key == 'a') {
		return 2;
	}
	else if (Key == 's') {
		return 3;
	}
	else if (Key == 'd') {
		return 4;
	}
	else return 0;
}

int main() {
	//	SetConsoleCP(1251);
	//	SetConsoleOutputCP(1251);

	int X = 0, Y = 0, Dir;
	string* Map = nullptr;
	Point Loader;
	Loader.x = 0, Loader.y = 0;
	int Boxes = 0;
	Point* Box = nullptr;
	int Points = 0;

	int LevelChoise;
	cin >> LevelChoise;
	if (LevelChoise == 1) {
		ifstream input("Lvl1.txt");
		input >> X >> Y;
		Map = new string[Y];
		for (int i = 0; i < Y; i++) {
			input >> Map[i];
		}
		input >> Loader.x >> Loader.y;
		input >> Boxes;
		Box = new Point[Boxes];
		for (int i = 0; i < Boxes; i++) {
			input >> Box[i].x >> Box[i].y;
		}
		input >> Points;
	}
	system("cls");
	char key;
	Draw(Loader, Map, Box, X, Y, Boxes);

	while (Points > 0 || key != 'o') {
		key = _getch();
		system("cls");
		Dir = Direction(key);
		if (!Move_or_Push(Dir, Loader, Box, Boxes)) {
			Move(Direction(key), Loader, Map);
		}
		else {
			int BNum = Box_Num(Box, Loader.x, Loader.y, Boxes);
			Push(Dir, Loader, Map, Box[BNum], BNum);
		}
		Draw(Loader, Map, Box, X, Y, Boxes);
	}


	return 0;
}
