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

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(8, 3);
	cout << "01 02 03 04 05 06 07 08 09 10";
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(43, 3);
	cout << "01 02 03 04 05 06 07 08 09 10";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(6, 5);
	cout << "A";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(8, 5);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(41, 5);
	cout << "A";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(43, 5);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(6, 7);
	cout << "B";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(8, 7);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(41, 7);
	cout << "B";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(43, 7);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(6, 9);
	cout << "C";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(8, 9);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(41, 9);
	cout << "C";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(43, 9);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(6, 11);
	cout << "D";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(8, 11);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(41, 11);
	cout << "D";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(43, 11);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(6, 13);
	cout << "E";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(8, 13);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(41, 13);
	cout << "E";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(43, 13);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(6, 15);
	cout << "F";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(8, 15);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(41, 15);
	cout << "F";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(43, 15);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(6, 17);
	cout << "G";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(8, 17);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(41, 17);
	cout << "G";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(43, 17);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(6, 19);
	cout << "H";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(8, 19);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(41, 19);
	cout << "H";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(43, 19);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(6, 21);
	cout << "I";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(8, 21);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(41, 21);
	cout << "I";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(43, 21);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(6, 23);
	cout << "J";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(8, 23);
	cout << ".. .. .. .. .. .. .. .. .. ..";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	gotoxy(41, 23);
	cout << "J";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(43, 23);
	cout << ".. .. .. .. .. .. .. .. .. ..";
}

void ClearRow(int row_num) {

	gotoxy(0, row_num);
	cout << "                                                                           ";
}

void PrintMessage(string msg) {

	for (int i = 0; i < 18; i++) {
		ClearRow(26 + i);
	}

	gotoxy(8, 26);
	cout << msg;
}

GridAddress GetAddress() {

	std::string address_string;

	while (!GridAddress::IsValidInput(address_string)) {
		ClearRow(27);
		gotoxy(8, 27);
		std::cin >> address_string;
	}

	GridAddress ga(address_string);
	return ga;
}

string GetString()
{
	ClearRow(27);
	gotoxy(8, 27);
	string input;
	std::cin >> input;
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

void UpdateComputerAddress(GridAddress ga, string s)
{
	int x = 40 + ga.Column() * 3;
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

int main()
{
	// resize console to fit boards
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 900, 650, TRUE);

	// print game intro; then on 'enter' print blank boards
	printUI();
	system("cls");
	printEmptyBoards();
	ClearRow(27);

	ShipCollection sc; // presently the 'classic' ships; could be customized in future
	Grid player_grid;
	Grid pc_grid;
	pc_grid.PlaceAuto(sc);
	Adversary pc;

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

	int number_player_fires = 0;
	int number_pc_fires = 0;

	while (player_grid.TotalHits() != sc.TotalLength() && pc_grid.TotalHits() != sc.TotalLength()) {

		PrintMessage("Choose target to fire at:");
		GridAddress target;
		bool valid_target = false;
		while (!valid_target) {
			GridAddress ga = GetAddress();
			if (!pc_grid.CellFiredAt(ga.GridIndex())) {
				target = ga;
				valid_target = true;
			}
		}

		Turn player_turn(target.GridIndex(), pc_grid);
		string turn_result;

		if (player_turn.IsHit()) {
			turn_result = "Hit!";
			if (player_turn.IsShipSunk()) turn_result += " You sunk the PC's " + pc_grid.ShipName(target) + "!";
			PrintMessage(turn_result);
			UpdateComputerAddress(target, "xx");
		}
		else {
			turn_result = "Miss!";
			PrintMessage(turn_result);
			UpdateComputerAddress(target, "[]");
		}

		gotoxy(8, 29);
		system("pause");
		ClearRow(29);

		Turn pc_turn = pc.NextTurn(player_grid);

		if (pc_turn.IsHit()) {
			turn_result = "PC Hit! (" + pc_turn.Target().AsString() + ")";
			if (pc_turn.IsShipSunk()) turn_result += " The PC sunk your " + player_grid.ShipName(pc_turn.Target()) + "!";
			PrintMessage(turn_result);
			UpdatePlayerAddress(pc_turn.Target(), "xx");
		}
		else {
			turn_result = "PC Miss!";
			PrintMessage(turn_result);
		}

		gotoxy(8, 29);
		system("pause");
		ClearRow(29);
	}

	if (pc_grid.TotalHits() == sc.TotalLength()) {

		PrintMessage("Congratulations, you've won!");
	}
	else {
		PrintMessage("You've lost, try again -- ");
	}

	std::cin.get();
}