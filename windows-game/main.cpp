#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include "../game-logic/src/Adversary.hpp"
#include "../game-logic/src/Grid.hpp"
#include "../game-logic/src/GridAddress.hpp"
#include "../game-logic/src/ShipCollection.hpp"
#include "../game-logic/src/ShipPlacement.hpp"
#include "../game-logic/src/Turn.hpp"

using namespace std;

typedef struct Frame {//basic frame
	COORD position[2]; //position
	bool blocked; //block
	int flag;
}Frame;

void SetPos(COORD a) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, a); //control cursor
}

void gotoxy(SHORT x, SHORT y) {  //control cursor
	//COORD coord = { 2 * x, y };
	COORD coord = { x, y };
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, coord);
}

void printUI() {
	PlaySound(TEXT("C:\\Windows\\media\\Ring10.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); //first letter S
	gotoxy(6, 2); cout << "    @@@@@";
	gotoxy(6, 3); cout << "  @";
	gotoxy(6, 4); cout << "  @";
	gotoxy(6, 5); cout << "    @@@@";
	gotoxy(6, 6); cout << "         @";
	gotoxy(6, 7); cout << "         @";
	gotoxy(6, 8); cout << "  @@@@@@";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); // second letter N
	gotoxy(20, 3); cout << "  @      @";
	gotoxy(20, 4); cout << "  @      @";
	gotoxy(20, 5); cout << "  @      @";
	gotoxy(20, 6); cout << "  @@@@@@@@";
	gotoxy(20, 7); cout << "  @      @";
	gotoxy(20, 8); cout << "  @      @";
	gotoxy(20, 9); cout << "  @      @";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	gotoxy(34, 2); cout << "  @@@@@@@ ";
	gotoxy(34, 3); cout << "     @    ";
	gotoxy(34, 4); cout << "     @    ";
	gotoxy(34, 5); cout << "     @    ";
	gotoxy(34, 6); cout << "     @    ";
	gotoxy(34, 7); cout << "  @@@@@@@ ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(48, 3); cout << "  @@@@@   ";
	gotoxy(48, 4); cout << "  @     @ ";
	gotoxy(48, 5); cout << "  @     @ ";
	gotoxy(48, 6); cout << "  @    @  ";
	gotoxy(48, 7); cout << "  @@@@    ";
	gotoxy(48, 8); cout << "  @       ";
	gotoxy(48, 9); cout << "  @       ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//вои╚
	gotoxy(62, 2); cout << "    @@@@@";
	gotoxy(62, 3); cout << "  @";
	gotoxy(62, 4); cout << "  @";
	gotoxy(62, 5); cout << "    @@@@";
	gotoxy(62, 6); cout << "         @";
	gotoxy(62, 7); cout << "         @";
	gotoxy(62, 8); cout << "  @@@@@@";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); //start buttom
	gotoxy(6, 14);
	cout << "Rules:\n";
	gotoxy(6, 15);
	cout << "1. This is player vs computer mode.\n";
	gotoxy(6, 16);
	cout << "2. Player and computer will each place their ships on their boards.\n";
	gotoxy(6, 17);
	cout << "3. Ships have 5 sizes: Destoryer takes 2 spaces; Cruiser takes 3 spaces,\n";
	gotoxy(6, 18);
	cout << "   Submarine takes 3 spaces, Battleship takes 4 spaces,\n";
	gotoxy(6, 19);
	cout << "   and Carrier takes 5 spaces. \n";
	gotoxy(20, 21);
	cout << "Press Enter key to start";

	while (1) {
		gotoxy(16, 21);
		cout << ">> ";
		Sleep(500);
		gotoxy(16, 21);
		cout << " >>";
		Sleep(500);
		//if (_kbhit()) {
		if (cin.get()) {
			PlaySound(TEXT("C:\\Windows\\media\\Windows Logon Sound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
			break;
		}
	}
}

void printEmptyBoards() {

	gotoxy(8, 3);
	cout << "01 02 03 04 05 06 07 08 09 10      01 02 03 04 05 06 07 08 09 10";

	gotoxy(6, 5);
	cout << "A .. .. .. .. .. .. .. .. .. ..    A .. .. .. .. .. .. .. .. .. ..";

	gotoxy(6, 7);
	cout << "B .. .. .. .. .. .. .. .. .. ..    B .. .. .. .. .. .. .. .. .. ..";

	gotoxy(6, 9);
	cout << "C .. .. .. .. .. .. .. .. .. ..    C .. .. .. .. .. .. .. .. .. ..";

	gotoxy(6, 11);
	cout << "D .. .. .. .. .. .. .. .. .. ..    D .. .. .. .. .. .. .. .. .. ..";

	gotoxy(6, 13);
	cout << "E .. .. .. .. .. .. .. .. .. ..    E .. .. .. .. .. .. .. .. .. ..";

	gotoxy(6, 15);
	cout << "F .. .. .. .. .. .. .. .. .. ..    F .. .. .. .. .. .. .. .. .. ..";

	gotoxy(6, 17);
	cout << "G .. .. .. .. .. .. .. .. .. ..    G .. .. .. .. .. .. .. .. .. ..";

	gotoxy(6, 19);
	cout << "H .. .. .. .. .. .. .. .. .. ..    H .. .. .. .. .. .. .. .. .. ..";

	gotoxy(6, 21);
	cout << "I .. .. .. .. .. .. .. .. .. ..    I .. .. .. .. .. .. .. .. .. ..";

	gotoxy(6, 23);
	cout << "J .. .. .. .. .. .. .. .. .. ..    J .. .. .. .. .. .. .. .. .. ..";
}

void ClearRow(int row_num) {

	gotoxy(0, row_num);
	cout << "                                                                    ";
}

void PrintMessage(string msg) {

	ClearRow(26);
	gotoxy(8, 26);
	cout << msg;
}

GridAddress GetAddress() {

	std::string address_string;

	while (!GridAddress::IsValidInput(address_string)) {
		ClearRow(27);
		gotoxy(8, 27);
		cin >> address_string;
	}

	GridAddress ga(address_string);
	return ga;
}

string GetString()
{
	ClearRow(27);
	gotoxy(8, 27);
	string input;
	cin >> input;
	return input;
}

void UpdatePlayerAddress(GridAddress ga, string s)
{
	int x = 5 + ga.Column() * 3;
	// waaaay better ways to do this....
	int y = 5;
	if (ga.Row() == 'B') y += 2;
	if (ga.Row() == 'C') y += 4;
	if (ga.Row() == 'D') y += 6;
	if (ga.Row() == 'E') y += 8;
	if (ga.Row() == 'F') y += 10;
	if (ga.Row() == 'G') y += 12;
	if (ga.Row() == 'H') y += 14;
	if (ga.Row() == 'I') y += 16;
	if (ga.Row() == 'J') y += 18;

	gotoxy(x, y);
	cout << s.substr(0, 2);
}

/*void soopa() {
	for (int i = 0; i < 17; i++) {
		gotoxy(i, 25 + i);
		cout << i;
	}
}*/

int main()
{
	printUI();
	system("cls");
	gotoxy(4, 27);
	printEmptyBoards();

	ShipCollection sc; // presently the 'classic' ships; could be customized in future
	Grid player_grid;
	Grid pc_grid;
	pc_grid.PlaceAuto(sc);

	for (auto& s : sc.Ships()) {

		bool can_place = false;
		vector<ShipPlacement> placements;

		while (!can_place) {

			PrintMessage("Enter start position for " + s.Name + ":");
			GridAddress start_add = GetAddress();
			if (player_grid.ValidPlacements(s, start_add, placements)) can_place = true;
		}

		vector<string> valid_opts;
		for (int i = 0; i < placements.size(); i++) valid_opts.push_back(to_string(i + 1));
		string selected_opt;

		can_place = false;
		while (!can_place) {
			string end_opts = "Choose endpoint:";
			for (int i = 0; i < placements.size(); i++) {
				end_opts += " [" + to_string(i + 1) + "] for " + placements[i].EndPoint().AsString();
			}

			PrintMessage(end_opts);
			selected_opt = GetString();
			can_place = find(valid_opts.begin(), valid_opts.end(), selected_opt) != valid_opts.end();
		}

		int choice = stoi(selected_opt) - 1;
		player_grid.PlaceShip(s, placements[choice]);

		for (int i = 0; i < placements[choice].Length(); i++) {
			UpdatePlayerAddress(placements[choice][i], s.Name);
		}
	}



	PrintMessage("Game is complete. Press enter to quit.");
	cin.get();
}