#include <vector>
#include <utility>

#include "boost/graph/adjacency_list.hpp"
#include "viennamath/expression.hpp"

#include "state_change.h"
#include "graph_utilities.h"

typedef boost::adjacency_list < boost::vecS, boost::vecS,
	boost::bidirectionalS, StateChange,
	viennamath::variable*> MCQSGraph;
typedef boost::graph_traits<MCQSGraph>::vertex_descriptor MCQSVertex_descriptor;

int main()
{
	std::vector<viennamath::variable*> lambda = {new viennamath::variable(0), new viennamath::variable(1) };
	std::vector<viennamath::variable*> sigma = {new viennamath::variable(2),new viennamath::variable(3),new viennamath::variable(4) };
	std::vector<StateChange> vector_state_change1 = { StateChange(), StateChange() };
	std::vector<StateChange> vector_state_change2 = { StateChange(), StateChange(), StateChange() };
	std::pair<MCQSGraph, MCQSVertex_descriptor> g = mcqsgraphutils::CreatePompon<MCQSGraph, 
		std::vector<viennamath::variable*>, std::vector<StateChange>>(lambda, vector_state_change1, sigma, vector_state_change2);
	return 0;
}