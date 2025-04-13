#pragma once

#include <string>
#include <vector>
#include "Town.h"

class TerritorialUnit {
private:
    std::string name_;
    std::string type_;
    size_t code_;

    size_t population2020_, male2020_, female2020_;
    size_t population2021_, male2021_, female2021_;
    size_t population2022_, male2022_, female2022_;
    size_t population2023_, male2023_, female2023_;
    size_t population2024_, male2024_, female2024_;

    Town* townData_ = nullptr;

public:
    TerritorialUnit();
    TerritorialUnit(const std::string& name, const std::string& type, size_t code = 0);

    const std::string& getName() const;
    const std::string& getType() const;
    size_t getCode() const;

    void setPopulation(int year, size_t population);
    void setMalePopulation(int year, size_t population);
    void setFemalePopulation(int year, size_t population);

    size_t getPopulation(int year) const;
    size_t getMalePopulation(int year) const;
    size_t getFemalePopulation(int year) const;

    void attachTown(Town* town);
    Town* getTownData() const;

    void aggregateFromChildren(const std::vector<TerritorialUnit*>& children);

    std::string toString() const;
    bool operator==(const TerritorialUnit& other) const;


};
