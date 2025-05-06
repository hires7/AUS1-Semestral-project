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

        // Vložíme koreň
        auto& root = tree->insertRoot();
        root.data_ = TerritorialUnit("Austria", "country", 0);

        // Uchováme si zoznam už pridaných vrcholov a ich uzlov
        std::vector<std::pair<size_t, MultiwayTree<TerritorialUnit>::Node*>> createdNodes;
        createdNodes.emplace_back(0, &root);

        // Jednotky, ktoré ešte nevieme priradiť (lebo nemajú zatiaľ rodiča v strome)
        std::vector<TerritorialUnit> pending = units;

        bool changed = true;
        while (!pending.empty() && changed) {
            changed = false;

            for (auto it = pending.begin(); it != pending.end(); ) {
                size_t parentCode = it->getParentCode();

                // Hľadaj rodiča medzi už vytvorenými uzlami
                auto parentIt = std::find_if(createdNodes.begin(), createdNodes.end(),
                    [=](const auto& pair) {
                        return pair.first == parentCode;
                    });

                if (parentIt != createdNodes.end()) {
                    // Rodič existuje → pridáme vrchol
                    auto& parentNode = *parentIt->second;
                    auto& newNode = tree->emplaceSon(parentNode, tree->degree(parentNode));
                    newNode.data_ = *it;

                    // Zapíš medzi vytvorené
                    createdNodes.emplace_back(it->getCode(), &newNode);

                    it = pending.erase(it);
                    changed = true;
                }
                else {
                    ++it;
                }
            }
        }

        // Ak niektoré jednotky zostali, výpis ich ako chybu
        for (const auto& u : pending) {
            std::cerr << "[ERROR] Parent not found for: " << u.getName()
                << " (code: " << u.getCode() << ", parent: " << u.getParentCode() << ")\n";
        }

        return tree;
    }


    static void assignTowns(ds::adt::MultiwayTree<TerritorialUnit>& tree, const std::vector<Town>& towns, const std::string& obceFile) {
        using Node = ds::adt::MultiwayTree<TerritorialUnit>::Node;

        std::unordered_map<size_t, Node*> regionNodes;

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

            size_t code = std::stoul(codeStr.substr(1, codeStr.size() - 2));
            size_t regionCode = std::stoul(regionStr.substr(2));

            Town* townPtr = nullptr;
            for (const auto& t : towns) {
                if (t.getCode() == code) {
                    townPtr = const_cast<Town*>(&t);
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
            newNode.data_ = TerritorialUnit(name, "town", code);

            TerritorialUnit& tu = newNode.data_;

            tu.attachTown(townPtr);

            for (int year = 2020; year <= 2024; ++year) {
                size_t pop = townPtr->getPopulation(year);
                size_t male = townPtr->getMale(year);
                size_t female = townPtr->getFemale(year);

                tu.setMalePopulation(year, male);
                tu.setFemalePopulation(year, female);
                tu.setPopulation(year, pop);

                /*std::cout << "[DATA] " << name << " | year " << year
                    << " => pop: " << pop << ", male: " << male << ", female: " << female << "\n";*/
            }


            newNode.data_ = tu;


            for (int year = 2020; year <= 2024; ++year) {
                size_t pop = townPtr->getPopulation(year);
                size_t male = townPtr->getMale(year);
                size_t female = townPtr->getFemale(year);

                /*std::cout << "[DATA] " << name << " | year " << year
                    << " => pop: " << pop
                    << ", male: " << male
                    << ", female: " << female << "\n";*/

                tu.setMalePopulation(year, male);
                tu.setFemalePopulation(year, female);
                tu.setPopulation(year, pop);
            }


        }
    }

};
