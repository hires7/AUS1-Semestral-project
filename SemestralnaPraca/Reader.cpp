#include "Reader.h"
#include <fstream>
#include <sstream>
#include <string>

std::vector<Town> Reader::readData(const std::vector<std::string>& filenames) {
    std::vector<Town> towns;

    for (const auto& filename : filenames) {
        int year = std::stoi(filename.substr(0, 4));

        std::ifstream file(filename);
        if (!file.is_open()) continue;

        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;

            while (std::getline(iss, token, ';')) {
                tokens.push_back(token);
            }

            std::string name = tokens[0];
            size_t code = std::stoul(tokens[1].substr(1, tokens[1].size() - 2));

            size_t male = tokens[2].empty() ? 0 : std::stoul(tokens[2]);
            size_t female = tokens[4].empty() ? 0 : std::stoul(tokens[4]);
            size_t total = male + female;

            bool found = false;
            for (auto& town : towns) {
                if (town.getCode() == code) {
                    town.setPopulation(year, total);
                    town.setMale(year, male);
                    town.setFemale(year, female);
                    found = true;
                    break;
                }
            }

            if (!found) {
                Town newTown(name, code);
                newTown.setPopulation(year, total);
                newTown.setMale(year, male);
                newTown.setFemale(year, female);
                towns.push_back(newTown);
            }
        }
    }
    return towns;
}

std::vector<TerritorialUnit> Reader::parseHierarchy(const std::string& filename)
{
    std::vector<TerritorialUnit> units;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, codeStr;
        std::getline(iss, name, ';');
        std::getline(iss, codeStr, ';');

        // 1. Extract only digits from "ATxxx"
        std::string digits;
        for (char c : codeStr) {
            if (std::isdigit(c)) {
                digits += c;
            }
        }

        // 2. Convert to number
        size_t code = safeStoul(digits);

        // 3. Determine parent code
        size_t parentCode = 0;
        if (code >= 100) {
            parentCode = code / 10;   // e.g., 121 → 12
        }
        else if (code >= 10) {
            parentCode = code / 10;   // e.g., 12 → 1
        }
        else {
            parentCode = 0;           // e.g., 1 → root Austria
        }

        // 4. Determine type
        std::string type;
        if (code < 10) type = "geo";
        else if (code < 100) type = "rep";
        else type = "reg";

        // 5. Add unit
        units.emplace_back(name, type, code, parentCode);

        // Debug (optional)
        std::cout << "[DEBUG] " << name << " (code: " << code << ", parent: " << parentCode << ")\n";
    }

    return units;
}


void Reader::printHierarchy(const ds::adt::MultiwayTree<TerritorialUnit>& tree,
    const ds::adt::MultiwayTree<TerritorialUnit>::Node* node,
    int indent)
{
    if (!node) return;

    const TerritorialUnit& unit = node->data_;
    std::string indentation(indent * 2, ' ');

    // Format code with AT
    std::string codeStr = "AT" + std::to_string(unit.getCode());
    std::string parentCodeStr = (unit.getCode() == 0) ? "-" : "AT" + std::to_string(unit.getParentCode());

    std::cout << indentation
        << "- " << unit.getType() << ": " << unit.getName()
        << " (code: " << codeStr
        << ", parent: " << parentCodeStr
        << ", Pop 2024: " << unit.getPopulation(2024)
        << ")\n";

    size_t children = tree.degree(*node);
    for (size_t i = 0; i < children; ++i) {
        const auto* child = tree.accessSon(*node, i);
        printHierarchy(tree, child, indent + 1);
    }
}


void Reader::aggregateTree(ds::adt::MultiwayTree<TerritorialUnit>& tree,
    ds::adt::MultiwayTree<TerritorialUnit>::Node* node)
{
    if (!node) return;

    std::vector<TerritorialUnit*> children;

    size_t count = tree.degree(*node);
    for (size_t i = 0; i < count; ++i) {
        auto* child = tree.accessSon(*node, i);
        aggregateTree(tree, child);
        children.push_back(&child->data_);
    }

    node->data_.aggregateFromChildren(children);
}

size_t Reader::safeStoul(const std::string& str)
{
    try {
        return std::stoul(str);
    }
    catch (const std::invalid_argument&) {
        return 0;
    }
    catch (const std::out_of_range&) {
        return 0;
    }
}

