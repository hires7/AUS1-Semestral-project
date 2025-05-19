#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>

#include "Town.h"
#include "TerritorialUnit.h"
#include "libds/adt/tree.h"
#include "libds/adt/list.h"
#include "UnitTable.h"

class TreeBuilder {
public:
    static ds::adt::MultiwayTree<TerritorialUnit>* buildTree(ds::adt::ImplicitList<TerritorialUnit>& units) {
        using namespace ds::adt;

        auto* tree = new MultiwayTree<TerritorialUnit>();

        auto& root = tree->insertRoot();
        root.data_ = TerritorialUnit("Austria", "country", 0);

        ImplicitList<std::pair<size_t, MultiwayTree<TerritorialUnit>::Node*>> createdNodes;
        createdNodes.insertLast(std::make_pair(0, &root));

        ImplicitList<TerritorialUnit> pending;
        for (size_t k = 0; k < units.size(); ++k) {
            TerritorialUnit unit = units.access(k);
            pending.insertLast(unit);
        }

        bool changed = true;
        while (!pending.isEmpty() && changed) {
            changed = false;

            size_t i = 0;
            while (i < pending.size()) {
                TerritorialUnit unit = pending.access(i);
                size_t parentCode = unit.getParentCode();

                bool parentFound = false;
                MultiwayTree<TerritorialUnit>::Node* parentNode = nullptr;
                for (size_t j = 0; j < createdNodes.size(); ++j) {
                    auto nodePair = createdNodes.access(j);
                    if (nodePair.first == parentCode) {
                        parentFound = true;
                        parentNode = nodePair.second;
                        break;
                    }
                }

                if (parentFound) {
                    auto& newNode = tree->emplaceSon(*parentNode, tree->degree(*parentNode));
                    newNode.data_ = unit;

                    createdNodes.insertLast(std::make_pair(unit.getCode(), &newNode));

                    pending.remove(i);

                    changed = true;
                }
                else {
                    ++i;
                }
            }
        }

        return tree;
    }


    static void assignTowns(ds::adt::MultiwayTree<TerritorialUnit>& tree, const std::vector<Town>& towns, const std::string& obceFile, UnitTable& unitTable) {
        using Tree = ds::adt::MultiwayTree<TerritorialUnit>;
        using Node = Tree::Node;

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

            Node* findNodeWithCode = nullptr;
            std::function<void(Node*)> search = [&](Node* node) {
                if (node->data_.getCode() == regionCode) {
                    findNodeWithCode = node;
                    return;
                }

                size_t childCount = tree.degree(*node);
                for (size_t i = 0; i < childCount && !findNodeWithCode; ++i) {
                    search(tree.accessSon(*node, i));
                }
                };

            search(tree.accessRoot());

            if (!findNodeWithCode) {
                std::cerr << "[!] Region node not found for code: " << regionCode << "\n";
                continue;
            }

            Node& newNode = tree.emplaceSon(*findNodeWithCode, tree.degree(*findNodeWithCode));
            newNode.data_ = TerritorialUnit(name, "town", code);

            TerritorialUnit& tu = newNode.data_;
            tu.attachTown(townPtr);

            for (int year = 2020; year <= 2024; ++year) {
                tu.setMalePopulation(year, townPtr->getMale(year));
                tu.setFemalePopulation(year, townPtr->getFemale(year));
                tu.setPopulation(year, townPtr->getPopulation(year));
            }

            unitTable.insert(&tu);
        }
    }


};
