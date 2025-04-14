#include "TreeBuilder.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace ds::adt;

MultiwayTree<TerritorialUnit>* TreeBuilder::buildTree(const std::vector<TerritorialUnit>& units)
{
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

void TreeBuilder::assignTowns(ds::adt::MultiwayTree<TerritorialUnit>& tree,
    const std::vector<Town>& towns,
    const std::string& obceFile)
{
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

        TerritorialUnit unit(name, "town", code);
        unit.attachTown(townPtr);
        for (int year = 2020; year <= 2024; ++year) {
            unit.setMalePopulation(year, townPtr->getMale(year));
            unit.setFemalePopulation(year, townPtr->getFemale(year));
            unit.setPopulation(year, townPtr->getPopulation(year));
        }

        Node& newNode = tree.emplaceSon(*regionIt->second, tree.degree(*regionIt->second));
        newNode.data_ = unit;
    }

}
