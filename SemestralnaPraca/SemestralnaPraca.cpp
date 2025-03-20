#include <iostream>
#include <windows.h>
#include "Town.h"
#include "Reader.h"
#include "Filter.h"

int main() {
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    std::vector<std::string> filenames = { "2020.csv", "2021.csv", "2022.csv", "2023.csv", "2024.csv" };
    std::vector<Town> towns = Reader::readData(filenames);
    std::vector<Town> filteredTowns;


    Filter::apply(
        towns.begin(),
        towns.end(),
        std::back_inserter(filteredTowns),
        Filter::byName("Gast") //ö
    );

    std::cout << "Filtered towns:\n";
    for (const auto& town : filteredTowns) {
        std::cout << town.toString() << "\n";
    }

    return 0;
}