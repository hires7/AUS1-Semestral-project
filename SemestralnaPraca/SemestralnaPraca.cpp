#include <iostream>
#include <windows.h>
#include "Town.h"
#include "Reader.h"

int main()
{
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);

    std::vector<std::string> filenames = { "2020.csv", "2021.csv", "2022.csv", "2023.csv", "2024.csv" };
    std::vector<Town> towns = Reader::readData(filenames);
	std::cout << "Pocet obci: " << towns.size() << "\n";
    for (const auto& town : towns) {
        std::cout << town.toString() << "\n";
    }

    return 0;
}
