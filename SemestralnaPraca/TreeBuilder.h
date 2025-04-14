#pragma once
#include <vector>
#include "TerritorialUnit.h"
#include "libds/adt/tree.h"

class TreeBuilder {
public:
    static ds::adt::MultiwayTree<TerritorialUnit>* buildTree(const std::vector<TerritorialUnit>& units);
    static void assignTowns(ds::adt::MultiwayTree<TerritorialUnit>& tree,
        const std::vector<Town>& towns,
        const std::string& obceFile);

};
