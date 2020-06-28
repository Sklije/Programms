#include <iostream>
#include <iomanip>
#include <ncurses.h>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
using namespace std;

enum Direction { Up, Down, Left, Right }; //iai?aaeaiey

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

struct Food {  //aaa
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

void FoodPosition(Point* Snake, Food& eda, int maxX, int maxY, int
Lenght) { //?aciauaiea aau
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

void Move(Point* Snake, int Lenght, Direction directon) {   // aae?aiea
        if (Lenght == 2) {
                Snake[1] = Snake[0];
        }
        else Snake[1] = Snake[Lenght - 1];
        for (int i = Lenght; i > 2; i--) {
                Snake[i] = Snake[i - 1];
        }
        Snake[2] = Snake[0];
        if (directon == Up) Snake[0].y -= 1;
        else if (directon == Down) Snake[0].y += 1;
        else if (directon == Left) Snake[0].x -= 1;
        else Snake[0].x += 1;
}

void Move_long(Point* Snake, int& Lenght, Direction directon, int&
Long) {// aae?aiea+?ino
        if (Lenght == 2) {
                Snake[1] = Snake[0];
        }
        Snake[Lenght] = Snake[Lenght - 1];
        for (int i = Lenght - 1; i > 2; i--) {
                Snake[i] = Snake[i - 1];
        }
        Snake[2] = Snake[0];
        if (directon == Up) Snake[0].y -= 1;
        else if (directon == Down) Snake[0].y += 1;
        else if (directon == Left) Snake[0].x -= 1;
        else Snake[0].x += 1;
        Lenght += 1;
        Long -= 1;
}

bool OutOfBorder(int maxX, int maxY, Point Head) { // auoia ca a?aieou
        return (Head.x <= 0 || Head.x >= maxX - 1 ||
                Head.y <= 0 || Head.y >= maxY - 1);
}

bool Death(Point* Snake, int Lenght) { // nia?ou
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
 	move(0,0);
        for (int i = 0; i < maxY; i++) {
                for (int j = 0; j < maxX; j++) {
                        if (Snake_Part(Snake, Lenght, i, j)) {
                          if (Snake[0].y == i && Snake[0].x == j) {attron(COLOR_PAIR(5));  printw("@@");refresh();}
                          else if (Snake[1].y == i && Snake[1].x == j) {attron(COLOR_PAIR(3)); printw("oo");refresh();}
                          else {
					attron(COLOR_PAIR(4));
					printw("uu"); refresh();
				}
                        }
                        else {
                          if (i == 0 || i == maxY - 1 || j == 0 || j == maxX - 1)
				{attron(COLOR_PAIR(9)); printw("**");refresh();}
                          else if (eda.Dis.y == i && eda.Dis.x == j) {attron(COLOR_PAIR(11));printw("FF");refresh();}
                          else {attron(COLOR_PAIR(12)); printw("..");refresh();}
                        }
                }
                printw("\n");
        }
        }



int main() {
 	initscr();
        int X = 40, Y = 40, Lenght = 2, Count = 0;
        char key;
        Food eda;
	start_color();
	setlocale(LC_CTYPE,"");
	curs_set(0);
        init_pair(4,  COLOR_YELLOW,  COLOR_YELLOW);
        init_pair(5,  COLOR_BLUE,    COLOR_BLUE);
        init_pair(6,  COLOR_MAGENTA, COLOR_MAGENTA);
        init_pair(7,  COLOR_CYAN,    COLOR_CYAN);
        init_pair(8,  COLOR_BLUE,    COLOR_BLUE);
        init_pair(9,  COLOR_WHITE,   COLOR_WHITE);
	init_pair(3, COLOR_GREEN, COLOR_GREEN );
	init_pair(2, COLOR_BLUE, COLOR_BLACK );
	init_pair(1, COLOR_BLUE, COLOR_BLUE );
	init_pair(10, COLOR_WHITE, COLOR_BLACK );
	init_pair(11, COLOR_RED, COLOR_RED );
	init_pair(12, COLOR_BLACK, COLOR_BLACK );
	attron(COLOR_PAIR(1));

        eda.valid = false;
        Direction dir = Right;
        //scanw ("%i", &Y);
        //scanw ("%i", &X);
        Point* Snake = new Point[X * Y];
        Snake[0].x = X / 2;
        Snake[0].y = Y / 2;
        Snake[1].x = Snake[0].x - 1;
        Snake[1].y = Y / 2;
	nodelay(stdscr,TRUE);
        while (!Game_over(X, Y, Snake, Lenght)) {
                key = getch();
                if (key == 'w') dir = Up;
                else if (key == 'a') dir = Left;
                else if (key == 's') dir = Down;
                else if (key == 'd') dir = Right;
                
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
               	unsigned int ms = 200000;
		usleep(ms);
        }
 
        printw("Game over");

       	endwin();
        delete[] Snake;

        return 0;
}
//end
