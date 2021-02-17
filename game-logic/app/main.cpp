#include <iostream>
#include <string>
#include "../src/Grid.hpp"
#include "../src/GridAddress.hpp"
#include "../src/Turn.hpp"

void PlacementDemo()
{
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
                std::cout << "[" << i + 1 << "] for " << pl[i].EndPoint().AsString() << "\n";
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

void FiringDemo()
{
    ShipCollection sc;

    Grid g;
    g.PlaceAuto(sc);

    std::cout << "\nShip Positions : " << "\n";
    std::cout << "\n" << g << "\n\n\n";

    while (g.TotalHits() != sc.TotalLength())
    {
        std::string address_string;
        bool valid_input = false;
        int fire_index;

        while (!valid_input) {

            address_string.clear();
            while (!GridAddress::IsValidInput(address_string)) {
                std::cout << "\nEnter position to fire on :\n";
                std::cin >> address_string;
            }

            GridAddress fire_location(address_string);
            valid_input = (g.CellStatus(fire_location) == "Empty" || g.CellStatus(fire_location) == "Ship");
            fire_index = fire_location.GridIndex();
        }
        
        Turn t(fire_index, g);

        if (t.IsHit()) {
            std::cout << "\nHit!";
            if (t.IsShipSunk()) std::cout << " You sunk the " + g.ShipName(fire_index) << "!";
            std::cout << "\n";
        }
        else std::cout << "\nMiss!\n";
    }

    system("pause");
}

void AutoTurnDemo()
{
    Grid g;
    ShipCollection sc;
    g.PlaceAuto(sc);
    std::cout << g << "\n\n";

    for (int i = 0; i < 15; i++) {
        Turn t = Turn::AutoFire(g);

        std::cout << "Target : " << t.Target().AsString() << "\n";
        std::cout << t.IsHit() << "\n";
    }
}

int main()
{
    //PlacementDemo();
    //FiringDemo();
    AutoTurnDemo();
}