#pragma once

#include "TerritorialUnit.h"
#include "libds/adt/table.h"
#include "libds/adt/list.h"
#include <string>
#include <iostream>

class UnitTable {
private:
    using UnitList = ds::adt::ImplicitList<TerritorialUnit*>;

    ds::adt::SortedSTab<std::string, UnitList*> geo_;
    ds::adt::SortedSTab<std::string, UnitList*> rep_;
    ds::adt::SortedSTab<std::string, UnitList*> reg_;
    ds::adt::SortedSTab<std::string, UnitList*> town_;
    ds::adt::SortedSTab<std::string, UnitList*> country_;

    ds::adt::SortedSTab<std::string, UnitList*>& getTable(const std::string& type) {
        if (type == "geo") return geo_;
        if (type == "rep") return rep_;
        if (type == "reg") return reg_;
        if (type == "town") return town_;
        if (type == "country") return country_;
        throw std::invalid_argument("Unknown type: " + type);
    }

public:
    ~UnitTable() {
        auto cleanup = [](auto& table) {
            for (auto& item : table) {
                delete item.data_;
            }
            table.clear();
            };

        cleanup(geo_);
        cleanup(rep_);
        cleanup(reg_);
        cleanup(town_);
        cleanup(country_);
    }

    void insert(TerritorialUnit* unit) {
        const std::string& name = unit->getName();
        const std::string& type = unit->getType();
        auto& table = getTable(type);

        UnitList* list = nullptr;
        UnitList** listPtr = &list;

        if (!table.tryFind(name, listPtr)) {
            list = new UnitList();
            list->insertLast(unit);
            table.insert(name, list);
        }
        else {
            (*listPtr)->insertLast(unit);
        }
    }

    UnitList* findAll(const std::string& name, const std::string& type) {
        auto& table = getTable(type);
        UnitList* list = nullptr;
        UnitList** listPtr = &list;

        if (table.tryFind(name, listPtr)) {
            return *listPtr;
        }
        return nullptr;
    }

    TerritorialUnit* findFirst(const std::string& name, const std::string& type) {
        UnitList* list = findAll(name, type);
        return (list && list->size() > 0) ? list->access(0) : nullptr;
    }
};
