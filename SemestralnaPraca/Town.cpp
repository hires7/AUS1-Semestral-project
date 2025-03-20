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
}

Town::Town(std::string name, size_t code, size_t population2020, size_t population2021, size_t population2022, size_t population2023, size_t population2024)
{
	this->name_ = name;
	this->code_ = code;
	this->population2020_ = population2020;
	this->population2021_ = population2021;
	this->population2022_ = population2022;
	this->population2023_ = population2023;
	this->population2024_ = population2024;
}

void Town::setPopulation2020(size_t population)
{
	this->population2020_ = population;
}

void Town::setPopulation2021(size_t population)
{
	this->population2021_ = population;
}

void Town::setPopulation2022(size_t population)
{
	this->population2022_ = population;
}

void Town::setPopulation2023(size_t population)
{
	this->population2023_ = population;
}

void Town::setPopulation2024(size_t population)
{
	this->population2024_ = population;
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

size_t Town::getCode()
{
	return this->code_;
}

Town::~Town(){}

std::string Town::toString() const {
	return "Obec: " + name_ + ", Kod: " + std::to_string(code_) + ", Populacia: " + std::to_string(population2020_) + ", " + std::to_string(population2021_) + ", " + std::to_string(population2022_) + ", " + std::to_string(population2023_) + ", " + std::to_string(population2024_);
}
