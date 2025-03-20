#pragma once
#include <vector>
#include <functional>
#include "Town.h"

class Reader {
public:
    static std::vector<Town> readData(const std::vector<std::string>& filenames);
};