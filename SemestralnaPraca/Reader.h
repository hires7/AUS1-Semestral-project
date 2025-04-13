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

};

