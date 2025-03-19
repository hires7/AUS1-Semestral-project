#pragma once
#include <string>

class Town
{
	private:
		std::string name_;
		size_t code_;

		size_t population2020_;
		size_t population2021_;
		size_t population2022_;
		size_t population2023_;
		size_t population2024_;

	public:
		Town();
		Town(std::string name, size_t code);
		Town(std::string name, size_t code, size_t population2020, size_t population2021, size_t population2022, size_t population2023, size_t population2024);
		void setPopulation2020(size_t population);
		void setPopulation2021(size_t population);
		void setPopulation2022(size_t population);
		void setPopulation2023(size_t population);
		void setPopulation2024(size_t population);
		size_t getPopulation2020();
		size_t getPopulation2021();
		size_t getPopulation2022();
		size_t getPopulation2023();
		size_t getPopulation2024();
		size_t getCode();
		~Town();
		std::string toString() const;
};

