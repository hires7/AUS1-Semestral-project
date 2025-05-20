#pragma once

#include "TerritorialUnit.h"
#include "libds/amt/implicit_sequence.h"
#include "libds/adt/sorts.h" 

class Sorter {
private:
    ds::adt::QuickSort<TerritorialUnit*> sorter_;

public:
    void sortByName(ds::adt::ImplicitList<TerritorialUnit*>* list) {
    ds::amt::ImplicitSequence<TerritorialUnit*>& sequence = *list->getSequence();
    sorter_.sort(sequence, [](const TerritorialUnit* a, const TerritorialUnit* b) {
        return a->getName() < b->getName();
    });
}

void sortByPopulation(ds::adt::ImplicitList<TerritorialUnit*>* list, int year) {
    ds::amt::ImplicitSequence<TerritorialUnit*>& sequence = *list->getSequence();
    sorter_.sort(sequence, [=](const TerritorialUnit* a, const TerritorialUnit* b) {
        return a->getPopulation(year) < b->getPopulation(year);
    });
}

void sortByGenderPopulation(ds::adt::ImplicitList<TerritorialUnit*>* list, int year, bool male) {
    ds::amt::ImplicitSequence<TerritorialUnit*>& sequence = *list->getSequence();
    sorter_.sort(sequence, [=](const TerritorialUnit* a, const TerritorialUnit* b) {
        return male
            ? a->getMalePopulation(year) < b->getMalePopulation(year)
            : a->getFemalePopulation(year) < b->getFemalePopulation(year);
    });
}
};
