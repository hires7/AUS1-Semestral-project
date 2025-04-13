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

