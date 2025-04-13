#define NOMINMAX 
#include <iostream>
#include <windows.h>
#include <limits>
#include "Town.h"
#include "Reader.h"
#include "Filter.h"


int main() {
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    std::vector<std::string> filenames = { "2020.csv", "2021.csv", "2022.csv", "2023.csv", "2024.csv" };
    std::vector<Town> towns = Reader::readData(filenames);
    std::vector<Town> filteredTowns;


    int choice;
    do {
        std::cout << "\n1. containsStr\n2. hasMaxResidents\n3. hasMinResidents\n4. Exit\nChoose: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            std::string search;
            std::cout << "Enter search string: ";
            std::getline(std::cin, search);
            filteredTowns.clear();
            Filter::apply(towns.begin(), towns.end(), std::back_inserter(filteredTowns),
                Filter::containsStr(search));
            break;
        }
        case 2: {
            int year; size_t max;
            std::cout << "Year (2020-2024): "; 
            std::cin >> year;
            std::cout << "Max population: "; 
            std::cin >> max;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            filteredTowns.clear();
            Filter::apply(towns.begin(), towns.end(), std::back_inserter(filteredTowns),
                Filter::hasMaxResidents(year, max));
            break;
        }
        case 3: {
            int year; size_t min;
            std::cout << "Year (2020-2024): "; 
            std::cin >> year;
            std::cout << "Min population: "; 
            std::cin >> min;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            filteredTowns.clear();
            Filter::apply(towns.begin(), towns.end(), std::back_inserter(filteredTowns),
                Filter::hasMinResidents(year, min));
            break;
        }
        }

        if (choice != 4) {
            std::cout << "\nVysledky (" << filteredTowns.size() << "):\n";
            for (const auto& t : filteredTowns)
                std::cout << " - " << t.toString() << "\n";
        }
    } while (choice != 4);

    return 0;
}