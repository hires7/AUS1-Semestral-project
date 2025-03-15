#include "Town.h"

Town::Town()
{
	this->name_ = "";
	this->code_ = 0;
	this->population_ = 0;
}

Town::Town(std::string name, int code, int population)
{
	this->name_ = name;
	this->code_ = code;
	this->population_ = population;
}

Town::~Town()
{	
	this->name_ = "";
	this->code_ = 0;
	this->population_ = 0;
}

std::string Town::toString()
{
	return this->name_ + " (" + std::to_string(this->code_) + ") - " + std::to_string(this->population_);
}
