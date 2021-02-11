#include <iostream>
#include <string>
#include "../src/Grid.hpp"
#include "../src/GridAddress.hpp"

int main()
{   
    Grid g;
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
    }


    std::cin.get();
}