#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "Town.h"
#include "TerritorialUnit.h"
#include "Reader.h"
#include "libds/adt/tree.h"

class Reader {
public:
   static std::vector<Town> readData(const std::vector<std::string>& filenames);

   static ds::adt::MultiwayTree<TerritorialUnit>* buildHierarchy(
       const std::string& uzemieFile,
       const std::string& obceFile,
       std::vector<Town>& towns
   );

   static void printHierarchy(const ds::adt::MultiwayTree<TerritorialUnit>& tree,
       const ds::adt::MultiwayTree<TerritorialUnit>::Node* node,
       int indent = 0);
};
void Reader::printHierarchy(const ds::adt::MultiwayTree<TerritorialUnit>& tree,
   const ds::adt::MultiwayTree<TerritorialUnit>::Node* node,
   int indent)
{
   if (!node) return;

   const TerritorialUnit& unit = node->data_;
   std::string indentStr(indent * 2, ' ');

   std::cout << indentStr << "- " << unit.getType() << ": " << unit.getName()
       << " (pop: " << unit.getPopulation(2024) << ")" << std::endl;

   size_t childCount = tree.degree(*node);
   for (size_t i = 0; i < childCount; ++i) {
       auto* child = tree.accessSon(*node, i);
       printHierarchy(tree, child, indent + 1);
   }
}
