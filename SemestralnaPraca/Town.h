#pragma once
#include <string>

class Town
{
	private:
		std::string name_;
		size_t code_;

		size_t population2020_, male2020_, female2020_;
		size_t population2021_, male2021_, female2021_;
		size_t population2022_, male2022_, female2022_;
		size_t population2023_, male2023_, female2023_;
		size_t population2024_, male2024_, female2024_;

	public:
		Town();
		Town(std::string name, size_t code);
		void setPopulation(int year, size_t population);
		void setMale(int year, size_t male);
		void setFemale(int year, size_t female);
		size_t getMale(int year) const;
		size_t getFemale(int year) const;
		size_t getPopulation(int year) const;
		std::string getName() const;
		size_t getCode() const;
		~Town();
		std::string toString() const;
};

