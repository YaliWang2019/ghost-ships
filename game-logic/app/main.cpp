#include <iostream>
#include <string>
#include "../src/Grid.hpp"
#include "../src/GridAddress.hpp"

int main()
{
    /*std::string address_string("");
    while (!GridAddress::IsValidInput(address_string)) {
        std::cout << "Enter board position : \n";
        std::cin >> address_string;
    }*/

    Grid g;

    std::cout << g.CellStatus(0) << "\n";


    std::cin.get();
}