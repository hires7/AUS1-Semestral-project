#pragma once
#include <vector>
#include <string>
#include "Town.h"

class Reader {
public:
    static std::vector<Town> readData(const std::vector<std::string>& filenames);
};