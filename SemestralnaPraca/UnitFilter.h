#pragma once

#include "TerritorialUnit.h"
#include <functional>
#include <string>

class UnitFilter {
public:
    static std::function<bool(const TerritorialUnit&)> nameContains(const std::string& substr) {
        return [substr](const TerritorialUnit& unit) {
            return unit.getName().find(substr) != std::string::npos;
            };
    }

    static std::function<bool(const TerritorialUnit&)> hasMinPopulation(int year, size_t min) {
        return [year, min](const TerritorialUnit& unit) {
            return unit.getPopulation(year) >= min;
            };
    }

    static std::function<bool(const TerritorialUnit&)> hasMaxPopulation(int year, size_t max) {
        return [year, max](const TerritorialUnit& unit) {
            return unit.getPopulation(year) <= max;
            };
    }

    static std::function<bool(const TerritorialUnit&)> isTownOnly() {
        return [](const TerritorialUnit& unit) {
            return unit.getType() == "town" || unit.getType() == "obec";
            };
    }
};
