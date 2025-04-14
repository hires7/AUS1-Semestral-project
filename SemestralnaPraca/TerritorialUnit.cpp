#include "TerritorialUnit.h"

TerritorialUnit::TerritorialUnit()
	: name_(""), type_(""), code_(0), townData_(nullptr),
	population2020_(0), male2020_(0), female2020_(0),
	population2021_(0), male2021_(0), female2021_(0),
	population2022_(0), male2022_(0), female2022_(0),
	population2023_(0), male2023_(0), female2023_(0),
	population2024_(0), male2024_(0), female2024_(0) {
}

TerritorialUnit::TerritorialUnit(const std::string& name, const std::string& type, size_t code)
	: name_(name), type_(type), code_(code), townData_(nullptr),
	population2020_(0), male2020_(0), female2020_(0),
	population2021_(0), male2021_(0), female2021_(0),
	population2022_(0), male2022_(0), female2022_(0),
	population2023_(0), male2023_(0), female2023_(0),
	population2024_(0), male2024_(0), female2024_(0) {
}

const std::string& TerritorialUnit::getName() const {
	return name_;
}

const std::string& TerritorialUnit::getType() const {
	return type_;
}

size_t TerritorialUnit::getCode() const {
	return code_;
}

bool TerritorialUnit::operator==(const TerritorialUnit& other) const
{
    return this->code_ == other.code_;
}

void TerritorialUnit::setPopulation(int year, size_t population) {
    switch (year) {
    case 2020: population2020_ = population; break;
    case 2021: population2021_ = population; break;
    case 2022: population2022_ = population; break;
    case 2023: population2023_ = population; break;
    case 2024: population2024_ = population; break;
    }
}

void TerritorialUnit::setMalePopulation(int year, size_t population) {
    switch (year) {
    case 2020: male2020_ = population; break;
    case 2021: male2021_ = population; break;
    case 2022: male2022_ = population; break;
    case 2023: male2023_ = population; break;
    case 2024: male2024_ = population; break;
    }
}

void TerritorialUnit::setFemalePopulation(int year, size_t population) {
    switch (year) {
    case 2020: female2020_ = population; break;
    case 2021: female2021_ = population; break;
    case 2022: female2022_ = population; break;
    case 2023: female2023_ = population; break;
    case 2024: female2024_ = population; break;
    }
}

size_t TerritorialUnit::getPopulation(int year) const {
    switch (year) {
    case 2020: return population2020_;
    case 2021: return population2021_;
    case 2022: return population2022_;
    case 2023: return population2023_;
    case 2024: return population2024_;
    default: return 0;
    }
}

size_t TerritorialUnit::getMalePopulation(int year) const {
    switch (year) {
    case 2020: return male2020_;
    case 2021: return male2021_;
    case 2022: return male2022_;
    case 2023: return male2023_;
    case 2024: return male2024_;
    default: return 0;
    }
}

size_t TerritorialUnit::getFemalePopulation(int year) const {
    switch (year) {
    case 2020: return female2020_;
    case 2021: return female2021_;
    case 2022: return female2022_;
    case 2023: return female2023_;
    case 2024: return female2024_;
    default: return 0;
    }
}

void TerritorialUnit::attachTown(Town* town)
{
    townData_ = town;
}

Town* TerritorialUnit::getTownData() const
{
	return townData_;
}

void TerritorialUnit::aggregateFromChildren(const std::vector<TerritorialUnit*>& children)
{
    for (int year = 2020; year <= 2024; ++year) {
        size_t totalM = 0, totalF = 0;
        for (const auto* child : children) {
            totalM += child->getMalePopulation(year);
            totalF += child->getFemalePopulation(year);
        }
        setMalePopulation(year, totalM);
        setFemalePopulation(year, totalF);
        setPopulation(year, totalM + totalF);
    }
}

std::string TerritorialUnit::toString() const
{
    return name_ + ", Kod: " + std::to_string(code_) + ", Populacia: " + std::to_string(population2020_) + ", " + std::to_string(population2021_) + ", " + std::to_string(population2022_) + ", " + std::to_string(population2023_) + ", " + std::to_string(population2024_);

}



