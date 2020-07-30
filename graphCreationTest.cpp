#include "boost/graph/adjacency_list.hpp"
#include "StateChange.h"
#include <vector>
#include "MCQSGraphProperty.h"//добавить библиотеку viennamath
#include <utility>
#include <boost/graph/copy.hpp>
#include <viennamath/expression.hpp>
typedef boost::adjacency_list<boost::listS, boost::listS,
			      boost::bidirectionalS, StateChange,
			      viennamath::variable*> MCCQSGraph;//тут могут возьникнут различные ошибки как-нибудь исправь
typedef boost::MCCQSGraph::vertex_descriptor MCCQSVertex_descriptor;

std::pair<MCQSGraph, MCCQSVertex_descriptor>
createIncomeGraph(vector<StateChange> &incomingVertexValueVector, 
		  vector<viennamath::variable*> &incomingEdgeValueVector){
	if (incomingVertexValueVector.length() == incomingEdgeValueVector.length()){
		MCCQSGraph resultGraph;
	    MCCQSVertex_descriptor mainVertex = boost::add_vertex(resultGraph);
		for (int i=0; i<incomingVertexValueVector.length(); i++){
		    temp_vertex = boost::add_vertex(resultGraph);
			resultGraph[temp_vertex] = incomingVertexValueVector[i];//переопредели оператор равно
			boost::add_edge(temp_vertex, mainVertex, incomingEdgeValueVector[i], resultGraph); 
		}
		return std::make_pair(resultGraph, mainVertex)
	} else {
		//RaiseError //сделай как-нибудь
	}									
}

std::pair<MCQSGraph, MCCQSVertex_descriptor>
createOutcomeGraph(vector<StateChange> &outcomingVertexValueVector, 
		   vector<ViennaMath::variable*> &outcomingEdgeValueVector){
	if (outcomingVertexValueVector.length() == outcomingEdgeValueVector.length()){
		MCCQSGraph resultGraph;
	    MCCQSVertex_descriptor mainVertex = boost::add_vertex(resultGraph);
		for (int i=0; i<outcomingVertexValueVector.length(); i++){
		    temp_vertex = boost::add_vertex(resultGraph);
			resultGraph[temp_vertex] = outcomingVertexValueVector[i];//переопредели оператор равно
			boost::add_edge(mainVertex, temp_vertex, outcomingEdgeValueVector[i], resultGraph); 
		}
		return std::make_pair(resultGraph, mainVertex)
	} else {
		//RaiseError //сделай как-нибудь
	}									
}

MCQSGraph connectTwoGraphsWithEdge(MCQSGraph &g, MCCQSVertex_descriptor connectFrom,
				   MCQSGraph &j, MCCQSVertex_descriptor connectTo){
	//https://stackoverflow.com/questions/18162187/merging-graphs-using-boost-graph
	//всё сделано на основе этой ссылки, без понятия работает это или нет
	typedef boost::property_map<MCQSGraph, boost::vertex_index_t>::type index_map_t;
	typedef boost::iterator_property_map<typename std::vector<MCCQSVertex_descriptor>::iterator,
					     index_map_t, MCCQSVertex_descriptor, MCCQSVertex_descriptor&> IsoMap;
	IsoMap mapG, mapJ;
	MCQSGraph resultGraph;
	boost::copy_graph(g, resultGraph, boost::orig_to_copy(mapG));
	boost::copy_graph(j, resultGraph, boost::orig_to_copy(mapJ));
        MCCQSVertex_descriptor fromG = mapG[connectFrom];
	MCCQSVertex_descriptor toJ = mapJ[connectTo];
	boost::add_edge(fromG, toJ, 1, resultGraph);//единица вместа переменной в качестве веса на ребре
	return resultGraph;
}

//MCQSGraph createBasic_Flow_OneOrbit_Exuction(
MCQSGraph createBattery(vector<StateChange> &incomingVertexValueVector, 
			vector<ViennaMath::variable*> &incomingEdgeValueVector,
			vector<StateChange> &outcomingVertexValueVector, 
			vector<ViennaMath::variable*> &outcomingEdgeValueVector){
	std::pair<MCQSGraph, MCCQSVertex_descriptor> incomeGraph = createIncomeGraph(incomingVertexValueVector,
										     incomingEdgeValueVector);
	std::pair<MCQSGraph, MCCQSVertex_descriptor> outcomeGraph = createIncomeGraph(outcomingVertexValueVector,
										      outcomingEdgeValueVector);
	return connectTwoGraphsWithEdge(incomeGraph.first, incomeGraph.second, outcomeGraph.first, outcomeGraph.second);
}



int main(){//example
	viennamath::variable lambda(0);// создаю интенсивность потока
	viennamath::variable sigma(1);// интенсивность орбиты 
	vector<viennamath::variable*> q(2); //вероятность перехода на одну из фаз
	for (int i = 0; i<2; i++)
		q[i] = new viennamath::variable(2+i);
	vector<viennamath::variable*> incomingFlow(2); // забиваю интенсивность потоков в вектор
        incomingFlow[0] = &lambda; //что бы можно было передать в рёбра графа
	incomingFlow[1] = &sigma;
	vector<StateChange> incomingStateChange(2);//создаю вектор изменения состояний, который потом передам в вершины графа
	vector<int> orbitMinus(1);// создаю вектор [-1] состоящий из одного элемента, так как орбита одна
	orbitMinus[0] = -1;
	vector<int> orbitZero(1);// создаю вектор [0] состоящий из одного элемента, так как орбита одна
	zero[0] = 0;
	vector<int> zeroZero(2); //создаю вектор [0,0] для перехода приборов
	for (int i = 0; i<2; i++) twoZero[i] = 0;
	vector<int> oneZero(2);//[0,1]
	vector<int> zeroOne(2);//[1,0]
	oneZero[0] = 1;
	oneZero[1] = 0;
	zeroOne[0] = 0;
	zeroOne[1] = 1;
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
	startGraph_OneFlow_OneOrbit_TwoPhase_WithExuction = createBattery(incomingFlowStateChange,
									  incomingFlow,
									  fullPhaseChange,
									  q);
	//создал граф
	return 0;
}
