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
    TerritorialUnit()
        : name_(""), type_(""), code_(0), townData_(nullptr),
        population2020_(0), male2020_(0), female2020_(0),
        population2021_(0), male2021_(0), female2021_(0),
        population2022_(0), male2022_(0), female2022_(0),
        population2023_(0), male2023_(0), female2023_(0),
        population2024_(0), male2024_(0), female2024_(0) {
    }

    TerritorialUnit(const std::string& name, const std::string& type, size_t code)
        : name_(name), type_(type), code_(code), townData_(nullptr),
        population2020_(0), male2020_(0), female2020_(0),
        population2021_(0), male2021_(0), female2021_(0),
        population2022_(0), male2022_(0), female2022_(0),
        population2023_(0), male2023_(0), female2023_(0),
        population2024_(0), male2024_(0), female2024_(0) {
    }

    TerritorialUnit(const std::string& name, const std::string& type, size_t code, size_t parentCode)
        : name_(name), type_(type), code_(code), parentCode_(parentCode),
        population2020_(0), male2020_(0), female2020_(0),
        population2021_(0), male2021_(0), female2021_(0),
        population2022_(0), male2022_(0), female2022_(0),
        population2023_(0), male2023_(0), female2023_(0),
        population2024_(0), male2024_(0), female2024_(0),
        townData_(nullptr)
    {
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
        population2024_(0), male2024_(0), female2024_(0) {
    }

    const std::string& getName() const { return name_; }
    const std::string& getType() const { return type_; }
    size_t getCode() const { return code_; }

    const std::string& getParentName() const { return parentName_; }
    const std::string& getParentType() const { return parentType_; }

    bool operator==(const TerritorialUnit& other) const {
        return this->code_ == other.code_;
    }

    void setPopulation(int year, size_t population) {
        switch (year) {
        case 2020: population2020_ = population; break;
        case 2021: population2021_ = population; break;
        case 2022: population2022_ = population; break;
        case 2023: population2023_ = population; break;
        case 2024: population2024_ = population; break;
        }
    }

    void setMalePopulation(int year, size_t population) {
        switch (year) {
        case 2020: male2020_ = population; break;
        case 2021: male2021_ = population; break;
        case 2022: male2022_ = population; break;
        case 2023: male2023_ = population; break;
        case 2024: male2024_ = population; break;
        }
    }

    void setFemalePopulation(int year, size_t population) {
        switch (year) {
        case 2020: female2020_ = population; break;
        case 2021: female2021_ = population; break;
        case 2022: female2022_ = population; break;
        case 2023: female2023_ = population; break;
        case 2024: female2024_ = population; break;
        }
    }

    size_t getPopulation(int year) const {
        switch (year) {
        case 2020: return population2020_;
        case 2021: return population2021_;
        case 2022: return population2022_;
        case 2023: return population2023_;
        case 2024: return population2024_;
        default: return 0;
        }
    }

    size_t getMalePopulation(int year) const {
        switch (year) {
        case 2020: return male2020_;
        case 2021: return male2021_;
        case 2022: return male2022_;
        case 2023: return male2023_;
        case 2024: return male2024_;
        default: return 0;
        }
    }

    size_t getFemalePopulation(int year) const {
        switch (year) {
        case 2020: return female2020_;
        case 2021: return female2021_;
        case 2022: return female2022_;
        case 2023: return female2023_;
        case 2024: return female2024_;
        default: return 0;
        }
    }

    void attachTown(Town* town) { townData_ = town; }
    Town* getTownData() const { return townData_; }

    void aggregateFromChildren(const std::vector<TerritorialUnit*>& children) {
        for (const auto* child : children) {
            this->aggregateChild(*child); 
        }
    }


    std::string toString() const {
        return name_ + ", Kod: " + std::to_string(code_) + ", Populacia: " +
            std::to_string(population2020_) + ", " +
            std::to_string(population2021_) + ", " +
            std::to_string(population2022_) + ", " +
            std::to_string(population2023_) + ", " +
            std::to_string(population2024_);
    }

    std::string toStringFemale() const {
        return name_ + ", Kod: " + std::to_string(code_) + ", Populacia zien: " +
            std::to_string(female2020_) + ", " +
            std::to_string(female2021_) + ", " +
            std::to_string(female2022_) + ", " +
            std::to_string(female2023_) + ", " +
            std::to_string(female2024_);
    }

    std::string toStringMale() const {
        return name_ + ", Kod: " + std::to_string(code_) + ", Populacia muzov: " +
            std::to_string(male2020_) + ", " +
            std::to_string(male2021_) + ", " +
            std::to_string(male2022_) + ", " +
            std::to_string(male2023_) + ", " +
            std::to_string(male2024_);
    }

    size_t getParentCode() const {
        if (type_ == "country") return 0;
        if (type_ == "commune") return communeParentCode_;
        if (code_ < 10) return 0;
        return code_ / 10;
    }

    bool isCommune() const { return type_ == "commune"; }

    void aggregateChild(const TerritorialUnit& child) {
        for (int year = 2020; year <= 2024; ++year) {
            setPopulation(year, getPopulation(year) + child.getPopulation(year));
            setMalePopulation(year, getMalePopulation(year) + child.getMalePopulation(year));
            setFemalePopulation(year, getFemalePopulation(year) + child.getFemalePopulation(year));
        }

        /*std::cout << "[AGGREGATE_CHILD] " << child.getName()
            << " -> Pop 2020: " << child.getPopulation(2020) << "\n";*/
    }

    void setParentCode(size_t parent)
    {
	    communeParentCode_ = parent;
    }
};
