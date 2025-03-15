#pragma once
#include <string>

class Town
{
	private:
		int code_;
		int population_;
		std::string name_;

	public:
		Town();
		Town(std::string name, int code, int population);
		~Town();
		std::string toString();
};

