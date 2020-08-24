#ifndef GRAPH_UTILITIES_WITHOUT_TEMPLATES_H_
#define GRAPH_UTILITIES_WITHOUT_TEMPLATES_H_

#include <utility>
#include <vector>
#include <list>
#include <span>
#include <iostream>
#include<map>
using namespace std;
#include"Graph.h"
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "boost/graph/copy.hpp"
#include "boost/foreach.hpp"

namespace mcqsgraphutils {
	template<class SomeClass1, class SomeClass2>
	bool CheckIfVectorHaveSameSize(const std::vector<SomeClass1> v1, const std::vector<SomeClass2> v2) {
		return v1.size() == v2.size();
	}

}
#endif
