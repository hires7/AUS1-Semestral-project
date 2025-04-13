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


ds::adt::MultiwayTree<TerritorialUnit>* Reader::buildHierarchy(const std::string& uzemieFile, const std::string& obceFile, std::vector<Town>& towns)
{
    auto* tree = new ds::adt::MultiwayTree<TerritorialUnit>();

    // 2. Mapovanie kodu alebo mena na node (aby sme vedeli pripojiù deti k rodiËovi)
    std::unordered_map<std::string, ds::adt::MultiwayTree<TerritorialUnit>::Node*> jednotky;

    // 3. NaËÌtaj uzemie.csv
    std::ifstream file(uzemieFile);
    if (!file.is_open()) {
        std::cerr << "Nepodarilo sa otvorit subor: " << uzemieFile << "\n";
        return tree;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string typ, nazov, kodStr, typRodica, nazovRodica, kodRodica;
        std::getline(iss, typ, ';');
        std::getline(iss, nazov, ';');
        std::getline(iss, kodStr, ';');
        std::getline(iss, typRodica, ';');
        std::getline(iss, nazovRodica, ';');
        std::getline(iss, kodRodica, ';');

        size_t kod = kodStr.empty() ? 0 : std::stoul(kodStr);
        TerritorialUnit jednotka(nazov, typ, kod);

        // 4. Vytvor uzol
        ds::adt::MultiwayTree<TerritorialUnit>::Node* node = nullptr;

        if (typRodica.empty()) {
            // Root uzol
            node = &tree->insertRoot();
        }
        else {
            // N·jdeme rodiËa podæa mena + typu
            std::string klucRodic = typRodica + ":" + nazovRodica;
            auto it = jednotky.find(klucRodic);
            if (it != jednotky.end()) {
                node = &tree->emplaceSon(*it->second, 0);
            }
            else {
                std::cerr << "RodiË nenajdeny: " << klucRodic << "\n";
                continue;
            }
        }

        node->data_ = jednotka;

        // 5. UloûÌme do mapy, aby sme mohli neskÙr pripojiù deti
        std::string kluc = typ + ":" + nazov;
        jednotky[kluc] = node;
    }

    return tree;
}


void Reader::printHierarchy(const ds::adt::MultiwayTree<TerritorialUnit>& tree,
    const ds::adt::MultiwayTree<TerritorialUnit>::Node* node,
    int indent)
{
    if (!node) return;

    const TerritorialUnit& unit = node->data_;
    std::string indentation(indent * 2, ' '); // 2 spaces per level

    std::cout << indentation << "- " << unit.getType() << ": " << unit.getName()
        << " (Pop 2024: " << unit.getPopulation(2024) << ")" << std::endl;

    size_t childrenCount = tree.degree(*node);
    for (size_t i = 0; i < childrenCount; ++i) {
        const auto* child = tree.accessSon(*node, i);
        printHierarchy(tree, child, indent + 1);
    }
}

