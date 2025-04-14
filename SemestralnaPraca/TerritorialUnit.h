#pragma once

#include <string>
#include <vector>
#include "Town.h"

class TerritorialUnit {
private:
    std::string name_;
    std::string type_;
    size_t code_;

    std::string parentName_;
    std::string parentType_;
    size_t parentCode_;

    size_t communeParentCode_ = 0;

    size_t population2020_, male2020_, female2020_;
    size_t population2021_, male2021_, female2021_;
    size_t population2022_, male2022_, female2022_;
    size_t population2023_, male2023_, female2023_;
    size_t population2024_, male2024_, female2024_;

    Town* townData_ = nullptr;

public:
    TerritorialUnit();
    TerritorialUnit(const std::string& name, const std::string& type, size_t code = 0);
    TerritorialUnit(const std::string& name, const std::string& type, size_t code, size_t parentCode)
        : name_(name), type_(type), code_(code), parentCode_(parentCode) {
    }
    TerritorialUnit(const std::string& name, const std::string& type, size_t code,
        const std::string& parentName, const std::string& parentType)
        : name_(name), type_(type), code_(code),
        parentName_(parentName), parentType_(parentType),
        townData_(nullptr),
        population2020_(0), male2020_(0), female2020_(0),
        population2021_(0), male2021_(0), female2021_(0),
        population2022_(0), male2022_(0), female2022_(0),
        population2023_(0), male2023_(0), female2023_(0),
        population2024_(0), male2024_(0), female2024_(0)
    {
    }


    const std::string& getName() const;
    const std::string& getType() const;
    size_t getCode() const;

    const std::string& getParentName() const { return parentName_; }
    const std::string& getParentType() const { return parentType_; }

    bool operator==(const TerritorialUnit& other) const;

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

    size_t getParentCode() const {
        if (type_ == "country") return 0;
        if (type_ == "commune") return communeParentCode_;


        if (code_ < 10) return 0;
        if (code_ < 100) return code_ / 10;

        return code_ / 10;
    }

    bool isCommune() const { return type_ == "commune"; }

    void aggregateChild(const TerritorialUnit& child) {
        population2020_ += child.population2020_;
        male2020_ += child.male2020_;
        female2020_ += child.female2020_;

        population2021_ += child.population2021_;
        male2021_ += child.male2021_;
        female2021_ += child.female2021_;

        population2022_ += child.population2022_;
        male2022_ += child.male2022_;
        female2022_ += child.female2022_;

        population2023_ += child.population2023_;
        male2023_ += child.male2023_;
        female2023_ += child.female2023_;

        population2024_ += child.population2024_;
        male2024_ += child.male2024_;
        female2024_ += child.female2024_;
    }

    void setParentCode(size_t parent) { communeParentCode_ = parent; }
};
