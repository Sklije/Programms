#include <iostream>
#include "windows.h"
#include <conio.h>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

string* Map = nullptr;

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


bool Is_A_Box(Point* Box, int X, int Y, int Boxes, int& BNum) {
	for (int i = 0; i < Boxes; i++) {
		if (Box[i].x == X && Box[i].y == Y) {
			BNum = i;
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

void Move(int Dir, Point& Load) {
	if (Dir == 1 && (Map[Load.y - 1][Load.x] != '*')) {
		Load.y -= 1;
	}
	else if (Dir == 2 && (Map[Load.y][Load.x - 1] != '*')) {
		Load.x -= 1;
	}
	else if (Dir == 3 && (Map[Load.y + 1][Load.x] != '*')) {
		Load.y += 1;
	}
	else if (Dir == 4 && (Map[Load.y][Load.x + 1] != '*')) {
		Load.x += 1;
	}
}

void Push(int Dir, Point& Load, Point& Box, int BNum) {
	if (BNum >= 0) {
		if (Dir == 1 && (Map[Load.y - 2][Load.x] != '*')) {
			Load.y -= 1;
			Box.y -= 1;
		}
		else if (Dir == 2 && (Map[Load.y][Load.x - 2] != '*')) {
			Load.x -= 1;
			Box.x -= 1;
		}
		else if (Dir == 3 && (Map[Load.y + 2][Load.x] != '*')) {
			Load.y += 1;
			Box.y += 1;
		}
		else if (Dir == 4 && (Map[Load.y][Load.x + 2] != '*')) {
			Load.x += 1;
			Box.x += 1;
		}
	}
}

void Move_or_Push(int Dir, Point& Load, Point* Box, int Boxes) {
	int BNum;
	int tmp;
	if (Dir == 1 && Is_A_Box(Box, Load.x, Load.y - 1, Boxes, BNum) && !Is_A_Box(Box, Load.x, Load.y - 2, Boxes, tmp)) {
		Push(Dir, Load, Box[BNum], BNum);
	}
	else if (Dir == 2 && Is_A_Box(Box, Load.x - 1, Load.y, Boxes, BNum) && !Is_A_Box(Box, Load.x - 2, Load.y, Boxes, tmp)) {
		Push(Dir, Load, Box[BNum], BNum);
	}
	else if (Dir == 3 && Is_A_Box(Box, Load.x, Load.y + 1, Boxes, BNum) && !Is_A_Box(Box, Load.x, Load.y + 2, Boxes, tmp)) {
		Push(Dir, Load, Box[BNum], BNum);
	}
	else if (Dir == 4 && Is_A_Box(Box, Load.x + 1, Load.y, Boxes, BNum) && !Is_A_Box(Box, Load.x + 2, Load.y, Boxes, tmp)) {
		Push(Dir, Load, Box[BNum], BNum);
	}
	else if (Dir == 1 && !Is_A_Box(Box, Load.x, Load.y - 1, Boxes, BNum) ||
		Dir == 2 && !Is_A_Box(Box, Load.x - 1, Load.y, Boxes, BNum) ||
		Dir == 3 && !Is_A_Box(Box, Load.x, Load.y + 1, Boxes, BNum) ||
		Dir == 4 && !Is_A_Box(Box, Load.x + 1, Load.y, Boxes, BNum)) {
		Move(Dir, Load);
	}
}

string Draw(Point& Loader, Point* Box, int X, int Y, int Boxes, int F, int& count) {
	int kostil;
	string out = "Left: ";
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (Map[i][j] == 'p' && Is_A_Box(Box, j, i, Boxes, kostil)) {
				F -= 1;
			}
			if (i == Loader.y && j == Loader.x) {
				cout << setw(2) << "G";
			}
			else if (Is_A_Box(Box, j, i, Boxes, kostil)) {
				cout << setw(2) << "B";
			}
			else cout << setw(2) << Map[i][j];
		}
		cout << endl;
	}
	count = F;
	return out + to_string(F);
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
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int X = 0, Y = 0, Dir;

	Point Loader;
	Loader.x = 0, Loader.y = 0;
	int Boxes = 0;
	Point* Box = nullptr;
	int Flag = 0;

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
		input >> Flag;
	}
	else if (LevelChoise == 2) {
		ifstream input("Lvl2.txt");
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
		input >> Flag;
	}
	else if (LevelChoise == 3) {
		ifstream input("Lvl3.txt");
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
		input >> Flag;
	}

	system("cls");
	char key = 'r';
	int count = Flag;
	cout << Draw(Loader, Box, X, Y, Boxes, Flag, count);
	while (count > 0) {
		key = _getch();
		if (key == 'r') {
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
				input >> Flag;
			}
			else if (LevelChoise == 2) {
				ifstream input("Lvl2.txt");
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
				input >> Flag;
			}
			else if (LevelChoise == 3) {
				ifstream input("Lvl3.txt");
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
				input >> Flag;
			}
		}
		system("cls");
		Dir = Direction(key);
		Move_or_Push(Dir, Loader, Box, Boxes);
		cout << Draw(Loader, Box, X, Y, Boxes, Flag, count);
	}
	system("cls");
	cout << "Game over!" << endl << "You win!";

	return 0;
}
