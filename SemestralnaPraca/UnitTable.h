#pragma once

#include "TerritorialUnit.h"

#include <string>
#include <utility>
#include <iostream>

#include "libds/adt/table.h"

class UnitTable {
private:
    ds::adt::SortedSTab<std::string, TerritorialUnit*> geo_;
    ds::adt::SortedSTab<std::string, TerritorialUnit*> rep_;
    ds::adt::SortedSTab<std::string, TerritorialUnit*> reg_;
    ds::adt::SortedSTab<std::string, TerritorialUnit*> town_;

public:
    void insert(TerritorialUnit* unit) {
        const std::string& type = unit->getType();
        const std::string& name = unit->getName();

        if (type == "geo") {
            geo_.insert(name, unit);
        }
        else if (type == "rep") {
            rep_.insert(name, unit);
        }
        else if (type == "reg") {
            reg_.insert(name, unit);
        }
        else if (type == "town") {
            town_.insert(name, unit);
        }
        else {
            std::cerr << "[UnitTable] Unknown unit type: " << type << "\n";
        }
    }

    TerritorialUnit* find(const std::string& name, const std::string& type) {
        TerritorialUnit* result = nullptr;
        TerritorialUnit** resultPtr = &result;

        if (type == "geo") {
            geo_.tryFind(name, resultPtr);
        }
        else if (type == "rep") {
            rep_.tryFind(name, resultPtr);
        }
        else if (type == "reg") {
            reg_.tryFind(name, resultPtr);
        }
        else if (type == "town") {
            town_.tryFind(name, resultPtr);
        }
        else {
            std::cerr << "[UnitTable] Unknown unit type in find(): " << type << "\n";
        }

        return result;
    }

};

