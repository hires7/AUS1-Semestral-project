#define NOMINMAX
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <windows.h>
#include <limits>
#include "Town.h"
#include "Reader.h"
#include "Filter.h"
#include "TreeBuilder.h"
#include "HierarchyIterator.h"
#include "Sorter.h"
#include "UnitFilter.h"
#include "UnitTable.h"
#include "TerritorialUnit.h"

int main() {
	{
		SetConsoleOutputCP(1250);
		SetConsoleCP(1250);


		std::vector<Town> towns = Reader::readData();
		ds::adt::ImplicitList<TerritorialUnit> units = Reader::parseHierarchy("uzemie.csv");

		auto* tree = TreeBuilder::buildTree(units); //tu
		UnitTable unitTable;
		std::function<void(ds::adt::MultiwayTree<TerritorialUnit>::Node*)> insertAll;
		insertAll = [&](auto* node) {
			unitTable.insert(&node->data_);
			size_t count = tree->degree(*node);
			for (size_t i = 0; i < count; ++i) {
				insertAll(tree->accessSon(*node, i));
			}
			};
		insertAll(tree->accessRoot());


		TreeBuilder::assignTowns(*tree, towns, "obce.csv", unitTable); //tu

		Reader::aggregateTree(*tree, tree->accessRoot());

		bool running = true;
        while (running) {

            std::cout << "\n=== MAIN MENU ===\n";
            std::cout << "1. Zadanie 1 (Town filters)\n";
            std::cout << "2. Zadanie 2 a 3 (Territorial hierarchy)\n";
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
                size_t totalNodes = tree->nodeCount();
                std::cout << "V hierarchii sa nachádza " << totalNodes << " vrcholov.\n";
                HierarchyIterator iterator(tree);
                bool iterating = true;

                while (iterating) {
                    std::cout << "\nAktuálny vrchol:\n";
                    iterator.printCurrent();

                    std::cout << "\nMožnosti:\n";
                    std::cout << "1. Filtrovať obce podľa názvu alebo populácie\n";
                    std::cout << "2. Posun na syna\n";
                    std::cout << "3. Posun k rodičovi\n";
                    std::cout << "4. Vypíš všetkých synov\n";
                    std::cout << "5. Zobraziť populáciu pre rok\n";
                    std::cout << "6. Zadanie 3: Vyhladat jednotku\n";
                    std::cout << "7. Koniec\n";

                    int iterChoice;
                    std::cin >> iterChoice;

                    switch (iterChoice) {
                    case 1: {
                        std::cout << "\n1. Názov obsahuje\n"
                            << "2. Minimálna populácia\n"
                            << "3. Maximálna populácia\n"
                            << "4. Typ jednotky (geo, rep, reg, town)\n"
                            << "Vyber filter: ";

                        int f;
                        std::cin >> f;

                        if (f == 1 || f == 2 || f == 3 || f == 4) {
                            ds::adt::ImplicitList<TerritorialUnit*>* results = nullptr;

                            if (f == 1) {
                                std::string s;
                                std::cout << "Zadaj reťazec: ";
                                std::cin >> s;
                                results = iterator.applyPredicateToDescendants([=](const TerritorialUnit& unit) {
                                    return UnitFilter::nameContains(s)(unit);
                                    });
                            }
                            else if (f == 2) {
                                int year;
                                size_t min;
                                std::cout << "Rok: ";
                                std::cin >> year;
                                std::cout << "Min: ";
                                std::cin >> min;
                                results = iterator.applyPredicateToDescendants([=](const TerritorialUnit& unit) {
                                    return UnitFilter::hasMinPopulation(year, min)(unit);
                                    });
                            }
                            else if (f == 3) {
                                int year;
                                size_t max;
                                std::cout << "Rok: ";
                                std::cin >> year;
                                std::cout << "Max: ";
                                std::cin >> max;
                                results = iterator.applyPredicateToDescendants([=](const TerritorialUnit& unit) {
                                    return UnitFilter::hasMaxPopulation(year, max)(unit);
                                    });
                            }
                            else if (f == 4) {
                                std::string type;
                                std::cout << "Zadaj typ jednotky (geo, rep, reg, town): ";
                                std::cin >> type;
                                results = iterator.applyPredicateToDescendants([=](const TerritorialUnit& unit) {
                                    return UnitFilter::hasType(type)(unit);
                                    });
                            }

                            if (!results || results->isEmpty()) {
                                std::cout << "\nNenašli sa žiadne výsledky.\n";
                                delete results;
                                break;
                            }

                            // výpis nájdených jednotiek
                            std::cout << "\nVýsledky (" << results->size() << "):\n";
                            for (size_t i = 0; i < results->size(); ++i) {
                                const auto* unit = results->access(i);
                                std::cout << " - " << unit->toString() << "\n";
                            }

                            // triediace menu
                            bool sorting = true;
                            Sorter sorter;
                            while (sorting) {
                                bool maleFemalePrint = false;
                                std::cout << "\n--- Zoradiť výsledky ---\n";
                                std::cout << "1. Podľa mena\n";
                                std::cout << "2. Podľa celkovej populácie\n";
                                std::cout << "3. Podľa pohlavia\n";
                                std::cout << "4. Späť\n";
                                std::cout << "Vyber možnosť: ";
                                int sortOption;
                                std::cin >> sortOption;

                                switch (sortOption) {
                                case 1:
                                    sorter.sortByName(results);
                                    break;
                                case 2: {
                                    int year;
                                    std::cout << "Zadaj rok: ";
                                    std::cin >> year;
                                    sorter.sortByPopulation(results, year);
                                    break;
                                }
                                case 3: {
                                    maleFemalePrint = true;
                                    int year;
                                    char gender;
                                    std::cout << "Zadaj rok: ";
                                    std::cin >> year;
                                    std::cout << "M (muži) / F (ženy): ";
                                    std::cin >> gender;
                                    bool isMale = (gender == 'M' || gender == 'm');
                                    sorter.sortByGenderPopulation(results, year, isMale);
                                    std::cout << "\nZoradené výsledky:\n";
                                    if (isMale)
                                    {
                                        for (size_t i = 0; i < results->size(); ++i) {
                                            const auto* unit = results->access(i);
                                            std::cout << " - " << unit->toStringMale() << "\n";
                                        }
                                    }
                                    else
                                    {
                                        for (size_t i = 0; i < results->size(); ++i) {
                                            const auto* unit = results->access(i);
                                            std::cout << " - " << unit->toStringFemale() << "\n";
                                        }
                                    }

                                    break;

                                }
                                case 4:
                                    sorting = false;
                                    continue;
                                default:
                                    std::cout << "Neplatná možnosť.\n";
                                    continue;
                                }
                                if (!maleFemalePrint)
                                {
                                    for (size_t i = 0; i < results->size(); ++i) {
                                        const auto* unit = results->access(i);
                                        std::cout << " - " << unit->toString() << "\n";
                                    }
                                }
                            }


                            delete results;
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
                        iterator.printPopulationByYear();
                        break;
                    case 6: {
                        std::string name, type;
                        std::cout << "Zadaj názov jednotky: ";
                        std::cin.ignore();
                        std::getline(std::cin, name);
                        std::cout << "Zadaj typ jednotky (geo, rep, reg, town): ";
                        std::cin >> type;

                        auto* list = unitTable.findAll(name, type);
                        if (!list || list->size() == 0) {
                            std::cout << "Nenašli sa žiadne jednotky pre: " << name << " [" << type << "]\n";
                        }
                        else {
                            std::cout << "Nájdené jednotky pre '" << name << "' [" << type << "]:\n";
                            for (size_t i = 0; i < list->size(); ++i) {
                                TerritorialUnit* unit = list->access(i);
                                std::cout << " - " << unit->toString() << "\n";
                            }
                        }
                        break;
                    }
                    case 7:
                        iterating = false;
                        break;
                    }
                }

                
                break;
            }


            case 3:
                running = false;
                break;

            default:
                std::cout << "Invalid option.\n";
            }
            delete tree;
            towns.clear();
            units.clear();
        }
		
	}
    _CrtDumpMemoryLeaks();
    return 0;
}
