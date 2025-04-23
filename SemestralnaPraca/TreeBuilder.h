#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>

#include "Town.h"
#include "TerritorialUnit.h"
#include "libds/adt/tree.h"

class TreeBuilder {
public:
    static ds::adt::MultiwayTree<TerritorialUnit>* buildTree(const std::vector<TerritorialUnit>& units) {
        using namespace ds::adt;

        auto* tree = new MultiwayTree<TerritorialUnit>();

        auto& root = tree->insertRoot();
        root.data_ = TerritorialUnit("Austria", "country", 0);

        std::unordered_map<size_t, MultiwayTree<TerritorialUnit>::Node*> nodeMap;
        nodeMap[0] = &root;

        for (const auto& unit : units) {
            size_t parentCode = unit.getParentCode();

            auto parentIt = nodeMap.find(parentCode);
            if (parentIt == nodeMap.end()) {
                std::cerr << "[ERROR] Parent not found for: " << unit.getName()
                    << " (code: " << unit.getCode()
                    << ", parent: " << parentCode << ")\n";
                continue;
            }

            auto& newNode = tree->emplaceSon(*parentIt->second, tree->degree(*parentIt->second));
            newNode.data_ = unit;

            nodeMap[unit.getCode()] = &newNode;
        }

        return tree;
    }

    static void assignTowns(ds::adt::MultiwayTree<TerritorialUnit>& tree, const std::vector<Town>& towns, const std::string& obceFile) {
        using Node = ds::adt::MultiwayTree<TerritorialUnit>::Node;

        std::unordered_map<size_t, Node*> regionNodes;

        // Rekurzívne prejde celý strom a mapuje kódy jednotiek na ich uzly
        std::function<void(Node*)> collectNodes;
        collectNodes = [&](Node* node) {
            const TerritorialUnit& unit = node->data_;
            regionNodes[unit.getCode()] = node;

            size_t childCount = tree.degree(*node);
            for (size_t i = 0; i < childCount; ++i) {
                Node* child = tree.accessSon(*node, i);
                collectNodes(child);
            }
            };

        collectNodes(tree.accessRoot());

        std::ifstream file(obceFile);
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, codeStr, regionStr;

            std::getline(iss, name, ';');
            std::getline(iss, codeStr, ';');
            std::getline(iss, regionStr, ';');

            // Správne spracovanie kódov
            size_t code = std::stoul(codeStr.substr(1, codeStr.size() - 2));
            size_t regionCode = std::stoul(regionStr.substr(2));

            // Nájde obec pod¾a kódu
            Town* townPtr = nullptr;
            for (const auto& t : towns) {
                if (t.getCode() == code) {
                    townPtr = const_cast<Town*>(&t);  // Áno, vieme, hack. Ale máme dôvod.
                    break;
                }
            }

            if (!townPtr) {
                std::cerr << "[!] Town not found: " << name << " (code: " << code << ")\n";
                continue;
            }

            auto regionIt = regionNodes.find(regionCode);
            if (regionIt == regionNodes.end()) {
                std::cerr << "[!] Region node not found for code: " << regionCode << "\n";
                continue;
            }

            Node& newNode = tree.emplaceSon(*regionIt->second, tree.degree(*regionIt->second));
            newNode.data_ = TerritorialUnit(name, "town", code); // prvé naplnenie

            TerritorialUnit& tu = newNode.data_;  // referencia na stromový objekt

            tu.attachTown(townPtr);

            for (int year = 2020; year <= 2024; ++year) {
                size_t pop = townPtr->getPopulation(year);
                size_t male = townPtr->getMale(year);
                size_t female = townPtr->getFemale(year);

                tu.setMalePopulation(year, male);
                tu.setFemalePopulation(year, female);
                tu.setPopulation(year, pop);

                std::cout << "[DATA] " << name << " | year " << year
                    << " => pop: " << pop << ", male: " << male << ", female: " << female << "\n";
            }


            newNode.data_ = tu;  // až teraz priradíš naplnený objekt


            for (int year = 2020; year <= 2024; ++year) {
                size_t pop = townPtr->getPopulation(year);
                size_t male = townPtr->getMale(year);
                size_t female = townPtr->getFemale(year);

                std::cout << "[DATA] " << name << " | year " << year
                    << " => pop: " << pop
                    << ", male: " << male
                    << ", female: " << female << "\n";

                tu.setMalePopulation(year, male);
                tu.setFemalePopulation(year, female);
                tu.setPopulation(year, pop);
            }


        }
    }

};
