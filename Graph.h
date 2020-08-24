#pragma once
#include <vector>
#include <utility>

#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/copy.hpp"
#include "boost/foreach.hpp"
#include "boost/tuple/tuple.hpp"
#include "viennamath/expression.hpp"


typedef boost::adjacency_list<boost::vecS, boost::vecS,
	boost::bidirectionalS, map<int, vector<int>>,
	viennamath::variable*> MCQSGraph;
typedef boost::graph_traits<MCQSGraph>::vertex_descriptor MCQSVertex_descriptor;