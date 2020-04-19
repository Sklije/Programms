#include <iostream>
#include "windows.h"
#include <conio.h>
#include <iomanip>
#include <vector>
#include <string>


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

struct Map {
	Point Loader;
	vector<string>* map;
	int Boxes;
} Lvl1;



void Move(char Direction, Point& Loader) {
	if (Direction == 'w' && (*Lvl1.map)[Loader.y - 1][Loader.x] != '*') { Loader.y -= 1; }
	else if (Direction == 's' && (*Lvl1.map)[Loader.y + 1][Loader.x] != '*') { Loader.y += 1; }
	else if (Direction == 'a' && (*Lvl1.map)[Loader.y][Loader.x - 1] != '*') { Loader.x -= 1; }
	else if (Direction == 'd' && (*Lvl1.map)[Loader.y][Loader.x + 1] != '*') { Loader.x += 1; }
}

void Drow(Point& Loader) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			if (Loader.y == i && Loader.x == j) {
				cout << setw(2) << "G";
			}
			else {
				cout << setw(2) << (*Lvl1.map)[i][j];
			}
		}
		cout << endl;
	}
}
int main() {
	//	SetConsoleCP(1251);
	//	SetConsoleOutputCP(1251);

	Lvl1.map = new vector<string>{
		"******..",
		"*p*..**.",
		"*ppp..**",
		"*.*B...*",
		"*.B.*..*",
		"**.B.B.*",
		".*B.B.**",
		".*...**.",
		".*****.."
	};
	Lvl1.Loader.x = 3;
	Lvl1.Loader.y = 4;

	Point Loader = Lvl1.Loader;
	char key;
	/*for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			if ((*Lvl1.map)[i][j] == 'G') {
				Loader.y = i;
				Loader.x = j;
			}
		}
	}*/
	int krya = 1;
	Drow(Loader);
	while (krya != 0) {
		key = _getch();
		system("cls");

		Move(key, Loader);
		Drow(Loader);

	}
	return 0;
}