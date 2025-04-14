#define NOMINMAX
#include <iostream>
#include <windows.h>
#include <limits>
#include "Town.h"
#include "Reader.h"
#include "Filter.h"
#include "TreeBuilder.h"
#include "HierarchyIterator.h"
#include "UnitFilter.h"

int main() {
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    std::vector<std::string> filenames = { "2020.csv", "2021.csv", "2022.csv", "2023.csv", "2024.csv" };
    std::vector<Town> towns = Reader::readData(filenames);
    std::vector<TerritorialUnit> units = Reader::parseHierarchy("uzemie.csv");

    bool running = true;
    while (running) {

        std::cout << "\n=== MAIN MENU ===\n";
        std::cout << "1. Zadanie 1 (Town filters)\n";
        std::cout << "2. Zadanie 2 (Territorial hierarchy)\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose: ";

        int mainChoice;
        std::cin >> mainChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (mainChoice) {
        case 1: {
            std::vector<Town> filteredTowns;
            int choice;
            do {
                std::cout << "\n1. containsStr\n2. hasMaxResidents\n3. hasMinResidents\n4. Back\nChoose: ";
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

                if (choice >= 1 && choice <= 3) {
                    std::cout << "\nVysledky (" << filteredTowns.size() << "):\n";
                    for (const auto& t : filteredTowns)
                        std::cout << " - " << t.toString() << "\n";
                }
            } while (choice != 4);
            break;
        }

        case 2: {
            auto* tree = TreeBuilder::buildTree(units);
            TreeBuilder::assignTowns(*tree, towns, "obce.csv");
            Reader::aggregateTree(*tree, tree->accessRoot());

            HierarchyIterator iterator(tree);
            bool iterating = true;

            while (iterating) {
                size_t totalNodes = tree->nodeCount();
                std::cout << "V hierarchii sa nachádza " << totalNodes << " vrcholov.\n";

                std::cout << "\nAktuálny vrchol:\n";
                iterator.printCurrent();

                std::cout << "\nMožnosti:\n";
                std::cout << "1. Filtrovať obce podľa názvu alebo populácie\n";
                std::cout << "2. Posun na syna\n";
                std::cout << "3. Posun k rodičovi\n";
                std::cout << "4. Vypíš všetkých synov\n";
                std::cout << "5. Koniec\n";
                std::cout << "Tvoja voľba: ";

                int iterChoice;
                std::cin >> iterChoice;

                switch (iterChoice) {
                case 1: {
                    std::cout << "\n1. Názov obsahuje\n2. Minimálna populácia\n3. Maximálna populácia\nVyber filter: ";
                    int f;
                    std::cin >> f;

                    if (f == 1) {
                        std::string s;
                        std::cout << "Zadaj reťazec: ";
                        std::cin >> s;
                        iterator.applyPredicateToDescendants(
                            [=](const TerritorialUnit& unit) {
                                return UnitFilter::isTownOnly()(unit) && UnitFilter::nameContains(s)(unit);
                            });
                    }
                    else if (f == 2) {
                        int year; size_t min;
                        std::cout << "Rok: "; std::cin >> year;
                        std::cout << "Min: "; std::cin >> min;
                        iterator.applyPredicateToDescendants(
                            [=](const TerritorialUnit& unit) {
                                return UnitFilter::isTownOnly()(unit) && UnitFilter::hasMinPopulation(year, min)(unit);
                            });
                    }
                    else if (f == 3) {
                        int year; size_t max;
                        std::cout << "Rok: "; std::cin >> year;
                        std::cout << "Max: "; std::cin >> max;
                        iterator.applyPredicateToDescendants(
                            [=](const TerritorialUnit& unit) {
                                return UnitFilter::isTownOnly()(unit) && UnitFilter::hasMaxPopulation(year, max)(unit);
                            });
                    }
                    break;
                }
                case 2: {
                    iterator.printChildren();
                    std::cout << "Zadaj index syna, na ktorého sa chceš presunúť: ";
                    size_t index;
                    std::cin >> index;
                    iterator.moveToChild(index);
                    break;
                }
                case 3:
                    iterator.moveToParent();
                    break;
                case 4:
                    iterator.printChildren();
                    break;
                case 5:
                    iterating = false;
                    break;
                default:
                    std::cout << "Neplatná voľba.\n";
                }
            }

            delete tree;
            break;
        }

        case 3:
            running = false;
            break;

        default:
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
