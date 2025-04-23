#pragma once
#include <algorithm>
#include <string>
#include "Town.h"

class Filter {
public:
    template <typename InputIt, typename OutputIt, typename Predicate>
    static void apply(InputIt begin, InputIt end, OutputIt out, Predicate pred) {
        std::copy_if(begin, end, out, pred);
    }

    static auto containsStr(const std::string& searchStr) {
        return [searchStr](const Town& town) {
            return town.getName().find(searchStr) != std::string::npos;
            };
    }

    static auto hasMaxResidents(int year, size_t max) {
        return [year, max](const Town& town) {
            return town.getPopulation(year) <= max;
            };
    }

    static auto hasMinResidents(int year, size_t min) {
        return [year, min](const Town& town) {
            return town.getPopulation(year) >= min;
            };
    }

};