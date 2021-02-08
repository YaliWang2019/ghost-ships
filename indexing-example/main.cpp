#include <iostream>
#include <string>
#include "GridAddress.hpp"

GridAddress PromptForAddress() {

    char row_name;
    int col_num = 0;

    while (!GridAddress::CanCompileAddress(row_name, col_num))
    {
        std::cout << "\nEnter Row : ";
        std::cin >> row_name;
        std::cout << "\nEnter Column : ";
        std::cin >> col_num;
    }

    GridAddress ga(row_name, col_num);
    return ga;
}

int main()
{
    GridAddress ga = PromptForAddress();

    std::cout << "\nAddress is " << ga.Row() << std::to_string(ga.Column()) << "\n";
    std::cout << "\nGrid Index is : " << ga.GridIndex() << "\n";

    std::cin.get();
}