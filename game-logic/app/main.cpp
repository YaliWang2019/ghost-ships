#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "../src/Grid.hpp"
#include "../src/GridAddress.hpp"
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
	COORD coord = { 2 * x, y };
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, coord);
}

void printUI() {
	PlaySound(TEXT("C:\\Windows\\media\\Ring10.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	//add music. but why this music only exists on the initial screen?
	//We really wanna do a pretty GRAPHICAL UI
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); //first letter S
	gotoxy(3, 2); cout << "    @@@@@";
	gotoxy(3, 3); cout << "  @";
	gotoxy(3, 4); cout << "  @";
	gotoxy(3, 5); cout << "    @@@@";
	gotoxy(3, 6); cout << "         @";
	gotoxy(3, 7); cout << "         @";
	gotoxy(3, 8); cout << "  @@@@@@";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); // second letter N
	gotoxy(10, 3); cout << "  @      @";
	gotoxy(10, 4); cout << "  @      @";
	gotoxy(10, 5); cout << "  @      @";
	gotoxy(10, 6); cout << "  @@@@@@@@";
	gotoxy(10, 7); cout << "  @      @";
	gotoxy(10, 8); cout << "  @      @";
	gotoxy(10, 9); cout << "  @      @";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	gotoxy(17, 2); cout << "  @@@@@@@ ";
	gotoxy(17, 3); cout << "     @    ";
	gotoxy(17, 4); cout << "     @    ";
	gotoxy(17, 5); cout << "     @    ";
	gotoxy(17, 6); cout << "     @    ";
	gotoxy(17, 7); cout << "  @@@@@@@ ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(24, 3); cout << "  @@@@@   ";
	gotoxy(24, 4); cout << "  @     @ ";
	gotoxy(24, 5); cout << "  @     @ ";
	gotoxy(24, 6); cout << "  @    @  ";
	gotoxy(24, 7); cout << "  @@@@    ";
	gotoxy(24, 8); cout << "  @       ";
	gotoxy(24, 9); cout << "  @       ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//��ɫ
	gotoxy(31, 2); cout << "    @@@@@";
	gotoxy(31, 3); cout << "  @";
	gotoxy(31, 4); cout << "  @";
	gotoxy(31, 5); cout << "    @@@@";
	gotoxy(31, 6); cout << "         @";
	gotoxy(31, 7); cout << "         @";
	gotoxy(31, 8); cout << "  @@@@@@";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); //start buttom
	gotoxy(3, 14);
	cout << "Rules:\n";
	gotoxy(3, 15);
	cout << "1. This is player vs computer mode.\n";
	gotoxy(3, 16);
	cout << "2. Player and computer will each place their ships on their boards.\n";
	gotoxy(3, 17);
	cout << "3. Ships have 5 sizes:Destoryer takes 2 spaces; cruiser takes 3 spaces,\n";
	gotoxy(3, 18);
	cout << "   battleship takes 4 spaces, and carrier takes 5 spaces. \n";
	gotoxy(10, 19);
	cout << "Press any key to start";

	while (1) {
		gotoxy(8, 19);
		cout << ">> ";
		Sleep(500);
		gotoxy(8, 19);
		cout << " >>";
		Sleep(500);
		if (_kbhit()) {
			PlaySound(TEXT("C:\\Windows\\media\\Windows Logon.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
			break;
		}
	}
}

void SetPos(SHORT i, SHORT j) {// set cursor
	COORD p = { i, j };
	SetPos(p);
}

int main()
{   
	printUI();
	system("cls");
    Grid g;
    ShipCollection sc;

    std::cout << "\nCurrent Board Positions : " << "\n";
    std::cout << "\n" << g << "\n";

    for (auto& s : sc.Ships()) {

        std::string address_string;
        bool can_place = false;
        std::vector<ShipPlacement> pl;

        while (!can_place) {

            address_string.clear();
            while (!GridAddress::IsValidInput(address_string)) {
				std::cout << "Board horizonal: 1 - 10. Board vertical: A - J ";
                std::cout << "\n\nEnter start position for " << s.Name << " : \n";
                std::cin >> address_string;
            }
            GridAddress start(address_string);

            if (g.ValidPlacements(s, start, pl)) can_place = true;
        }


        std::vector<std::string> valid_opts;
        for (int i = 0; i < pl.size(); i++) valid_opts.push_back(std::to_string(i + 1));
        std::string selected_opt;

        can_place = false;
        while (!can_place) {

            std::cout << "\nEnter end position for " << s.Name << " : \n";
            for (int i = 0; i < pl.size(); i++) {
                std::cout << "[" << i+1 << "] for " << pl[i].EndPoint().AsString() << "\n";                
            }
            
            std::cin >> selected_opt;
            can_place = std::find(valid_opts.begin(), valid_opts.end(), selected_opt) != valid_opts.end();
        }

        int choice = std::stoi(selected_opt) - 1;
        g.PlaceShip(s, pl[choice]);

        for (int i = 0; i < 100; i++) std::cout << "\n";
        std::cout << "\nCurrent Board Positions : " << "\n";
        std::cout << "\n" << g << "\n\n\n";

        system("pause");
    }
    
    Grid g2;
    g2.PlaceAuto(sc);

    for (int i = 0; i < 100; i++) std::cout << "\n";
    std::cout << "\nFinal Player Positions : " << "\n";
    std::cout << "\n" << g << "\n\n\n";

    std::cout << "\nFinal PC Positions : " << "\n";
    std::cout << "\n" << g2 << "\n\n\n";

    std::cout << "\n\n";
    system("pause");
	
}