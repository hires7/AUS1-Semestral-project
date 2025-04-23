#pragma once
#include <string>

class Town {
private:
    std::string name_;
    size_t code_;

    size_t population2020_, male2020_, female2020_;
    size_t population2021_, male2021_, female2021_;
    size_t population2022_, male2022_, female2022_;
    size_t population2023_, male2023_, female2023_;
    size_t population2024_, male2024_, female2024_;

public:
    Town()
        : name_(""), code_(0),
        population2020_(0), male2020_(0), female2020_(0),
        population2021_(0), male2021_(0), female2021_(0),
        population2022_(0), male2022_(0), female2022_(0),
        population2023_(0), male2023_(0), female2023_(0),
        population2024_(0), male2024_(0), female2024_(0) {
    }

    Town(std::string name, size_t code)
        : name_(std::move(name)), code_(code),
        population2020_(0), male2020_(0), female2020_(0),
        population2021_(0), male2021_(0), female2021_(0),
        population2022_(0), male2022_(0), female2022_(0),
        population2023_(0), male2023_(0), female2023_(0),
        population2024_(0), male2024_(0), female2024_(0) {
    }

    void setMale(int year, size_t male) {
        switch (year) {
        case 2020: male2020_ = male; break;
        case 2021: male2021_ = male; break;
        case 2022: male2022_ = male; break;
        case 2023: male2023_ = male; break;
        case 2024: male2024_ = male; break;
        }
    }

    void setFemale(int year, size_t female) {
        switch (year) {
        case 2020: female2020_ = female; break;
        case 2021: female2021_ = female; break;
        case 2022: female2022_ = female; break;
        case 2023: female2023_ = female; break;
        case 2024: female2024_ = female; break;
        }
    }

    void setPopulation(int year, size_t population) {
        switch (year) {
        case 2020: population2020_ = population; break;
        case 2021: population2021_ = population; break;
        case 2022: population2022_ = population; break;
        case 2023: population2023_ = population; break;
        case 2024: population2024_ = population; break;
        default: break;
        }
    }

    size_t getMale(int year) const {
        switch (year) {
        case 2020: return male2020_;
        case 2021: return male2021_;
        case 2022: return male2022_;
        case 2023: return male2023_;
        case 2024: return male2024_;
        default: return 0;
        }
    }

    size_t getFemale(int year) const {
        switch (year) {
        case 2020: return female2020_;
        case 2021: return female2021_;
        case 2022: return female2022_;
        case 2023: return female2023_;
        case 2024: return female2024_;
        default: return 0;
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

    std::string getName() const { return name_; }
    size_t getCode() const { return code_; }

    std::string toString() const {
        return "Obec: " + name_ + ", Kod: " + std::to_string(code_) +
            ", Populacia: " +
            std::to_string(population2020_) + ", " +
            std::to_string(population2021_) + ", " +
            std::to_string(population2022_) + ", " +
            std::to_string(population2023_) + ", " +
            std::to_string(population2024_);
    }

    ~Town() = default;
};
