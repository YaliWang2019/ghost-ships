#include <iostream>
#include <string>
#include "../src/Grid.hpp"
#include "../src/GridAddress.hpp"

int main()
{   
    {
        ShipPlacement pl(5);
        pl.Add(15);
        pl.Add(25);
        pl.Finalize();

        std::cout << "START : " << pl.StartPoint().AsString() << "\n";
        std::cout << "LENGTH: " << pl.Length() << "\n";
        std::cout << "END   : " << pl.EndPoint().AsString() << "\n";
    }


    Grid g;
    Ship s{ "TestShip",2 };
    GridAddress ga{ "C3" };

    std::vector<ShipPlacement> places;
    bool result = g.ValidPlacements(s, ga, places);

    std::cout << " HAS PLACEMENTS : " << result << "\n";

    for (auto& s : places) {
        for (int i = 0; i < s.Length(); i++) {
            GridAddress new_add{ s[i] };
            std::cout << new_add.AsString() << " ";
        }
        std::cout << "\n";
    }

    


    /*Grid g;
    bool rerun = true;

    std::cout << "\nCurrent Board Positions : " << "\n";
    std::cout << "\n" << g << "\n";

    while (rerun) {

        std::string address_string("");

        while (!GridAddress::IsValidInput(address_string)) {
            std::cout << "Enter ship position : \n";
            std::cin >> address_string;
        }

        GridAddress ga(address_string);
        g.SetShip(ga);

        std::cout << "\nCurrent Board Positions : " << "\n";
        std::cout << "\n" << g << "\n";

        std::cout << "Add another position? [ y / n ]" << "\n";
        char c;
        std::cin >> c;
        rerun = toupper(c) == 'Y';
    }*/


    std::cin.get();
}