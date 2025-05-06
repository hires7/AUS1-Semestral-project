#pragma once

#include <complexities/complexity_analyzer.h>
#include <libds/adt/table.h>
#include <random>

namespace ds::utils
{
	//template<typename TableType>
	//class TableRemoveAnalyzer : public ComplexityAnalyzer<TableType>
	//{
	//public:
	//	TableRemoveAnalyzer(const std::string& name)
	//	{
	//		ComplexityAnalyzer(name);
	//		rng_(144);
	//	}

	//	void growToSize(TableType& structure, size_t size) override
	//	{
	//		std::uniform_int_distribution<int> dist(0, (std::numeric_limits<int>::max)());
	//		while (structure.size() < size)
	//		{
	//			const int key = dist(rng_);
	//			try
	//			{
	//				structure.insert(key, key);
	//				keys_.push_back(key);
	//			}
	//			catch (...)
	//			{
	//			}
	//		}
	//	}

	//	void executeOperation(TableType& structure) override
	//	{
	//		// 
	//		//structure.remove();
	//	}
	//private:
	//	std::default_random_engine rng_;
	//	std::vector<int> keys_;
	//};

	//class SSTRemoveAnalyzer : public TableRemoveAnalyzer<adt::SortedSTab<int, int>>
	//{
	//	SSTRemoveAnalyzer() : TableRemoveAnalyzer("SSTRemoveAnalyzer")
	//	{
	//	}
	//};

}


