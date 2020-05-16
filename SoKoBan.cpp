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


bool It_Is_A_Box(Point* Box, int X, int Y, int Boxes) {
	for (int i = 0; i < Boxes; i++) {
		if (Box[i].x == X && Box[i].y == Y) {
			return true;
		}
	}
	return false;
}


void Move(char Direction, Point& Loader, string* Map, Point* Box, int Boxes) {
	int offset = 1;
	int num = -1;
	for (int i = 0; i < Boxes; i++) {
		if (Direction == 'w' && It_Is_A_Box(Box, Loader.x, Loader.y - 1, Boxes)/*Loader.y - 1 == Box[i].y && Loader.x == Box[i].x*/) {
			offset = 2;
			num = i;
		}
		else if (Direction == 's' && It_Is_A_Box(Box, Loader.x, Loader.y + 1, Boxes)/*Loader.y + 1 == Box[i].y && Loader.x == Box[i].x*/) {
			offset = 2;
			num = i;
		}
		else if (Direction == 'a' && It_Is_A_Box(Box, Loader.x - 1, Loader.y, Boxes)/*Loader.y == Box[i].y && Loader.x - 1 == Box[i].x*/) {
			offset = 2;
			num = i;
		}
		else if (Direction == 'd' && It_Is_A_Box(Box, Loader.x + 1, Loader.y, Boxes)/*Loader.y == Box[i].y && Loader.x + 1 == Box[i].x*/) {
			offset = 2;
			num = i;
		}
		else offset = 1;
	}

	if (Direction == 'w' && (Map[Loader.y - offset][Loader.x] == '.' || Map[Loader.y - offset][Loader.x] == 'p')) {
		Loader.y -= 1;
		if (offset == 2) Box[num].y -= 1;
	}
	else if (Direction == 's' && (Map[Loader.y + offset][Loader.x] == '.' || Map[Loader.y + offset][Loader.x] == 'p')) {
		Loader.y += 1;
		if (offset == 2) Box[num].y += 1;
	}
	else if (Direction == 'a' && (Map[Loader.y][Loader.x - offset] == '.' || Map[Loader.y][Loader.x - offset] == 'p')) {
		Loader.x -= 1;
		if (offset == 2) Box[num].x -= 1;
	}
	else if (Direction == 'd' && (Map[Loader.y][Loader.x + offset] == '.' || Map[Loader.y][Loader.x + offset] == 'p')) {
		Loader.x += 1;
		if (offset == 2) Box[num].x += 1;
	}
	offset = 1;
	num = -1;
}

void Push() {

}

void Draw(Point& Loader, string* Map, Point* Box, int X, int Y, int Boxes) {
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (i == Loader.y && j == Loader.x) {
				cout << setw(2) << "G";
			}
			else if (It_Is_A_Box(Box, j, i, Boxes)) {
				cout << setw(2) << "B";
			}
			else cout << setw(2) << Map[i][j];
		}
		cout << endl;
	}
}


int main() {
	//	SetConsoleCP(1251);
	//	SetConsoleOutputCP(1251);

	int X = 0, Y = 0;
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

	while (Points > 0 || key) {
		key = _getch();
		system("cls");
		Move(key, Loader, Map, Box, Boxes);
		Draw(Loader, Map, Box, X, Y, Boxes);
	}


	return 0;
}
