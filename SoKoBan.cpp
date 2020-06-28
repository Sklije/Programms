#include <iomanip>
#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

string* Map = NULL;

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


void Draw(Point& Loader, Point* Box, int X, int Y, int Boxes, int F,
int& count) {
int kostil;
 for (int i = 0; i < Y; i++) {
   for (int j = 0; j < X; j++) {
     if (Map[i][j] == 'p' && Is_A_Box(Box, j, i, Boxes, kostil)) {
       F -= 1;
     }
     if (i == Loader.y && j == Loader.x) {attron(COLOR_PAIR(11));
printw("G");refresh();}
     else if (Is_A_Box(Box, j, i, Boxes, kostil))
{attron(COLOR_PAIR(4)); printw("B");refresh();}
     else if (Map[i][j]== '*') {attron(COLOR_PAIR(9)); printw("*");refresh();}
     else if (Map[i][j]== '.') {attron(COLOR_PAIR(12)); printw(".");refresh();}
     else if (Map[i][j]=='p') {attron(COLOR_PAIR(5)); printw("p");refresh();}
     count = F;
   }
   printw("\n");
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
	initscr();
	start_color();
	setlocale(LC_CTYPE, "");
	curs_set(0);
	init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(5, COLOR_BLUE, COLOR_BLUE);
	init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(7, COLOR_CYAN, COLOR_CYAN);
	init_pair(8, COLOR_BLUE, COLOR_BLUE);
	init_pair(9, COLOR_WHITE, COLOR_WHITE);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLUE);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);
	init_pair(11, COLOR_RED, COLOR_RED);
	init_pair(12, COLOR_BLACK, COLOR_BLACK);
	attron(COLOR_PAIR(1));

	int X = 0, Y = 0, Dir;

	Point Loader;
	Loader.x = 0, Loader.y = 0;
	int Boxes = 0;
	Point* Box = NULL;
	int Flag = 0;
	
	int LevelChoise;
	scanw("%i", &LevelChoise);
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
	char key = 'r';
	int count = Flag;

	Draw(Loader, Box, X, Y, Boxes, Flag, count);refresh();
	while (count > 0) {
	  move(1,0);
		key = getch();
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
		Dir = Direction(key);
		Move_or_Push(Dir, Loader, Box, Boxes);
		Draw(Loader, Box, X, Y, Boxes,Flag, count);
		refresh();
	}
	printw("Game over! You win!");refresh();
	endwin();
	return 0;
}
