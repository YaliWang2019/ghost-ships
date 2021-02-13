#include <iostream>
#include <string>
#include "../src/Grid.hpp"
#include "../src/GridAddress.hpp"

int main()
{   
    Grid g;

    std::cout << "\nCurrent Board Positions : " << "\n";
    std::cout << "\n" << g << "\n";

    ShipCollection sc;

    for (auto& s : sc.Ships()) {

        std::string address_string;
        bool can_place = false;
        std::vector<ShipPlacement> pl;

        while (!can_place) {

            address_string.clear();
            while (!GridAddress::IsValidInput(address_string)) {
                std::cout << "Enter start position for " << s.Name << " : \n";
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

        std::cout << "\nCurrent Board Positions : " << "\n";
        std::cout << "\n" << g << "\n";

        system("pause");
    }

    std::cin.get();
}