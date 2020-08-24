#ifndef GRAPH_UTILITIES_WITHOUT_TEMPLATES_H_
#define GRAPH_UTILITIES_WITHOUT_TEMPLATES_H_

#include <utility>
#include <vector>
#include <list>
#include <span>


#include "boost/graph/copy.hpp"
#include "boost/foreach.hpp"

namespace mcqsgraphutils {
	template<class SomeClass>
	inline bool CheckIfVectorHaveSameSize(std::vector<SomeClass> v1, std::vector<SomeClass> v2) {
		return v1.size() == v2.size();
	}

}
#endif
