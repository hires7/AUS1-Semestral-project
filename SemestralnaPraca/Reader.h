#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "Town.h"
#include "TerritorialUnit.h"
#include "libds/adt/tree.h"

class Reader {
public:
   static std::vector<Town> readData(const std::vector<std::string>& filenames);
   static std::vector<TerritorialUnit> parseHierarchy(const std::string& filename);
   static void printHierarchy(const ds::adt::MultiwayTree<TerritorialUnit>& tree,
       const ds::adt::MultiwayTree<TerritorialUnit>::Node* node,
       int indent = 0);
   static void aggregateTree(ds::adt::MultiwayTree<TerritorialUnit>& tree,
       ds::adt::MultiwayTree<TerritorialUnit>::Node* node);
   static size_t safeStoul(const std::string& str);
};

