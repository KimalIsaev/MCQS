
#include "StateChange.h"

#include <vector>
#include <utility>
#include <boost/graph/copy.hpp>
#include <viennamath/expression.hpp>
#include <boost/graph/adjacency_list.hpp>
typedef boost::adjacency_list<boost::vecS, boost::vecS,
			      boost::bidirectionalS, StateChange,
			      viennamath::variable*> MCQSGraph;//тут могут возьникнут различные ошибки как-нибудь исправь
typedef boost::graph_traits<MCQSGraph>::vertex_descriptor MCQSVertex_descriptor;

std::pair<MCQSGraph, MCQSVertex_descriptor>
createIncomeGraph(vector<StateChange> &incomingVertexValueVector, 
		  vector<viennamath::variable*> &incomingEdgeValueVector){
	if (incomingVertexValueVector.size() == incomingEdgeValueVector.size()){
		MCQSGraph resultGraph;
	    MCQSVertex_descriptor mainVertex = boost::add_vertex(resultGraph);
		for (int i=0; i<incomingVertexValueVector.size(); i++){
			MCQSVertex_descriptor temp_vertex = boost::add_vertex(incomingVertexValueVector[i], resultGraph);
			//resultGraph[temp_vertex] = incomingVertexValueVector[i];//переопредели оператор равно
			boost::add_edge(temp_vertex, mainVertex, incomingEdgeValueVector[i], resultGraph); 
		}
		return std::make_pair(resultGraph, mainVertex);
	}
	else {
		throw std::invalid_argument("different sizes of edge and vertex value vectors");;
	}									
}

std::pair<MCQSGraph, MCQSVertex_descriptor>
createOutcomeGraph(vector<StateChange> &outcomingVertexValueVector, 
		   vector<viennamath::variable*> &outcomingEdgeValueVector){
	if (outcomingVertexValueVector.size() == outcomingEdgeValueVector.size()){
		MCQSGraph resultGraph;
		MCQSVertex_descriptor mainVertex = boost::add_vertex(resultGraph);
		for (int i=0; i<outcomingVertexValueVector.size(); i++){
			MCQSVertex_descriptor temp_vertex = boost::add_vertex(outcomingVertexValueVector[i], resultGraph);
			boost::add_edge(mainVertex, temp_vertex, outcomingEdgeValueVector[i], resultGraph); 
		}
		return std::make_pair(resultGraph, mainVertex);
	} else {
		throw std::invalid_argument("different sizes of edge and vertex value vectors");;
	}									
}

MCQSGraph connectTwoGraphsWithEdge(MCQSGraph &g, MCQSVertex_descriptor connectFrom,
				   MCQSGraph &j, MCQSVertex_descriptor connectTo, viennamath::variable *edgeValue){
	//https://stackoverflow.com/questions/18162187/merging-graphs-using-boost-graph
	//всё сделано на основе этой ссылки, без понятия работает это или нет
	typedef boost::property_map<MCQSGraph, boost::vertex_index_t>::type index_map_t;
	//typedef boost::iterator_property_map<typename std::vector<MCQSVertex_descriptor>::iterator,
	//				     index_map_t, MCQSVertex_descriptor, MCQSVertex_descriptor&> IsoMap;
	//vector<MCQSVertex_descriptor> orig2copy_data_of_g(boost::num_vertices(g));
	//vector<MCQSVertex_descriptor> orig2copy_data_of_j(boost::num_vertices(j));
	//IsoMap mapG/* = make_iterator_property_map*/(orig2copy_data_of_g.begin());//, get(boost::vertex_index, g));
	//IsoMap mapJ/* = make_iterator_property_map*/(orig2copy_data_of_j.begin());//, get(boost::vertex_index, j));
	typedef std::map<MCQSVertex_descriptor, MCQSVertex_descriptor> MCQSVertex_map;
	MCQSVertex_map vertexMapG, vertexMapJ;
	boost::associative_property_map<MCQSVertex_map> mapG(vertexMapG);
	boost::associative_property_map<MCQSVertex_map> mapJ(vertexMapJ);
	MCQSGraph resultGraph;
	boost::copy_graph(g, resultGraph, boost::orig_to_copy(mapG));
	boost::copy_graph(j, resultGraph, boost::orig_to_copy(mapJ));
	MCQSVertex_descriptor fromG = mapG[connectFrom];
	MCQSVertex_descriptor toJ = mapJ[connectTo];
	boost::add_edge(fromG, toJ, edgeValue, resultGraph);//единица вместа переменной в качестве веса на ребре
	return resultGraph;
}

MCQSGraph createBattery(vector<StateChange> &incomingVertexValueVector, 
			vector<viennamath::variable*> &incomingEdgeValueVector,
			vector<StateChange> &outcomingVertexValueVector, 
			vector<viennamath::variable*> &outcomingEdgeValueVector, viennamath::variable *edgeValue){
		std::pair<MCQSGraph, MCQSVertex_descriptor> incomeGraph = createIncomeGraph(incomingVertexValueVector,
			incomingEdgeValueVector);
		std::pair<MCQSGraph, MCQSVertex_descriptor> outcomeGraph = createIncomeGraph(outcomingVertexValueVector,
			outcomingEdgeValueVector);
	return connectTwoGraphsWithEdge(incomeGraph.first, incomeGraph.second, outcomeGraph.first, outcomeGraph.second, edgeValue);
}

vector<vector<int>> GenereteOneMatrixVector(int n)
{
	vector<vector<int>> onesMatrixVector(n);
	for (int i = 0; i < n; i++) {
		vector<int> vec(n);
		onesMatrixVector[i] = vec;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			onesMatrixVector[i][j] = 0;
		onesMatrixVector[i][i] = 1;
	}
	return onesMatrixVector;
}

vector<int> GenereteZeroVector(int n)
{
	vector<int> vec(n);
	for (int i = 0; i < vec.size(); i++)
		vec[i] = 0;
	return vec;
}


vector<StateChange> createStateChangeVectorFromOrbitAndPhase(vector<vector<int>> orbit,
							     vector<vector<int>> phase){
	
}

vector<StateChange> createStateChangeVectorFromOrbitAndPhase(vector<int> orbit,
							     vector<vector<int>> phase){
	
}

vector<StateChange> createStateChangeVectorFromOrbitAndPhase(vector<vector<int>> orbit,
							     vector<int> phase){
	
}

int main(){//example
	vector<vector<int>> onesMatrixVector = GenereteOneMatrixVector(5);
	vector<int> zeroVector = GenereteZeroVector(3);
	/*viennamath::variable one(0);
	viennamath::variable lambda(1);// создаю интенсивность потока
	viennamath::variable sigma(2);// интенсивность орбиты 
	vector<viennamath::variable*> q(2); //вероятность перехода на одну из фаз
	for (int i = 0; i<2; i++)
		q[i] = new viennamath::variable(3+i);
	vector<viennamath::variable*> incomingFlow(2); // забиваю интенсивность потоков в вектор
    incomingFlow[0] = &lambda; //что бы можно было передать в рёбра графа
	incomingFlow[1] = &sigma;
	vector<StateChange> incomingStateChange(2);//создаю вектор изменения состояний, который потом передам в вершины графа
	vector<int> orbitMinus(1);// создаю вектор [-1] состоящий из одного элемента, так как орбита одна
	orbitMinus[0] = -1;
	vector<int> orbitZero(1);// создаю вектор [0] состоящий из одного элемента, так как орбита одна
	orbitZero[0] = 0;
	vector<int> zeroZero(2); //создаю вектор [0,0] для перехода приборов
	for (int i = 0; i<2; i++) zeroZero[i] = 0;
	vector<vector<int>> onesMatrixVector(2);//[0,1]
	//vector<int> zeroOne(2);//[1,0]
	//oneZero[0] = 1;
	//oneZero[1] = 0;
	//zeroOne[0] = 0;
	//zeroOne[1] = 1;
	StateChange orbitChange(orbitMinus, zeroZero);
	StateChange mainFlowChange(orbitZero, zeroZero);
	StateChange zeroPhaseChange(orbitZero, oneZero);
	StateChange onePhaseChange(orbitZero, zeroOne);
	vector<StateChange> incomingFlowStateChange(2);//создаю вектора который можно вставить в функции по созданию графов
        incomingFlowStateChange[0] = mainFlowChange;
	incomingFlowStateChange[1] = orbitChange;
	vector<StateChange> fullPhaseChange(2);//тут тоже создаю вектора который можно вставить в функции по созданию графов
	fullPhaseChange[0] = zeroPhaseChange;
	fullPhaseChange[1] = onePhaseChange;
	try {
		MCQSGraph startGraph_OneFlow_OneOrbit_TwoPhase_WithExuction = createBattery(incomingFlowStateChange,
			incomingFlow,
			fullPhaseChange,
			q, &one);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
	}*/
	//создал граф
	return 0;
}
