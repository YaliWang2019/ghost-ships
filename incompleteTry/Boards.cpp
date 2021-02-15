#include <iostream>
#include <cstdio>
#include <ctime>   
#include <windows.h> 
#include <cstdlib>
#include <conio.h> 
#include <cstring>
using namespace std;

// Settings for the frame, left board, and right board
void gotoxy(int x, int y) //position function for the whole frame, x for row, y for col
{
	COORD pos;
	pos.X = 2 * (y);
	pos.Y = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void gotoxy1(int x, int y)//position function for the left board, x for row, y for col
{
	COORD pos;
	pos.X = 2 * (y + 5);
	pos.Y = x + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void gotoxy2(int x, int y)//position function for the right board, x for row, y for col
{
	COORD pos;
	pos.X = 2 * (y + 18);
	pos.Y = x + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}