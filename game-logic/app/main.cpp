#include <iostream>
#include <string>
#include "../src/GridAddress.hpp"

int main()
{
    std::string address_string("");
    while (!GridAddress::IsValidInput(address_string)) {
        std::cout << "Enter board position : \n";
        std::cin >> address_string;
    }

    std::cin.get();
}