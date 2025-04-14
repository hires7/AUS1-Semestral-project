#include "Town.h"

Town::Town()
{
	this->name_ = "";
	this->code_ = 0;
	this->population2020_ = 0;
	this->population2021_ = 0;
	this->population2022_ = 0;
	this->population2023_ = 0;
	this->population2024_ = 0;
	this->male2020_ = 0;
	this->male2021_ = 0;
	this->male2022_ = 0;
	this->male2023_ = 0;
	this->male2024_ = 0;
	this->female2020_ = 0;
	this->female2021_ = 0;
	this->female2022_ = 0;
	this->female2023_ = 0;
	this->female2024_ = 0;
}

Town::Town(std::string name, size_t code)
{
	this->name_ = name;
	this->code_ = code;
	this->population2020_ = 0;
	this->population2021_ = 0;
	this->population2022_ = 0;
	this->population2023_ = 0;
	this->population2024_ = 0;
	this->male2020_ = 0;
	this->male2021_ = 0;
	this->male2022_ = 0;
	this->male2023_ = 0;
	this->male2024_ = 0;
	this->female2020_ = 0;
	this->female2021_ = 0;
	this->female2022_ = 0;
	this->female2023_ = 0;
	this->female2024_ = 0;
}


void Town::setMale(int year, size_t male) {
	switch (year) {
	case 2020: male2020_ = male; break;
	case 2021: male2021_ = male; break;
	case 2022: male2022_ = male; break;
	case 2023: male2023_ = male; break;
	case 2024: male2024_ = male; break;
	}
}

void Town::setFemale(int year, size_t female) {
	switch (year) {
	case 2020: female2020_ = female; break;
	case 2021: female2021_ = female; break;
	case 2022: female2022_ = female; break;
	case 2023: female2023_ = female; break;
	case 2024: female2024_ = female; break;
	}
}

void Town::setPopulation(int year, size_t population) {
	switch (year) {
	case 2020: population2020_ = population; break;
	case 2021: population2021_ = population; break;
	case 2022: population2022_ = population; break;
	case 2023: population2023_ = population; break;
	case 2024: population2024_ = population; break;
	default: break;
	}
}

size_t Town::getMale(int year) const {
	switch (year) {
	case 2020: return male2020_;
	case 2021: return male2021_;
	case 2022: return male2022_;
	case 2023: return male2023_;
	case 2024: return male2024_;
	default: return 0;
	}
}

size_t Town::getFemale(int year) const {
	switch (year) {
	case 2020: return female2020_;
	case 2021: return female2021_;
	case 2022: return female2022_;
	case 2023: return female2023_;
	case 2024: return female2024_;
	default: return 0;
	}
}

size_t Town::getPopulation(int year) const
{
	switch (year)
	{
	case 2020:
		return this->population2020_;
		break;
	case 2021:
		return this->population2021_;
		break;
	case 2022:
		return this->population2022_;
		break;
	case 2023:
		return this->population2023_;
		break;
	case 2024:
		return this->population2024_;
		break;
	default:
		return 0;
		break;
	}
}


std::string Town::getName() const
{
	return this->name_;
}

size_t Town::getCode() const
{
	return this->code_;
}

Town::~Town(){}

std::string Town::toString() const {
	return "Obec: " + name_ + ", Kod: " + std::to_string(code_) + ", Populacia: " + std::to_string(population2020_) + ", " + std::to_string(population2021_) + ", " + std::to_string(population2022_) + ", " + std::to_string(population2023_) + ", " + std::to_string(population2024_);
}
