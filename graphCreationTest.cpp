#include "boost/graph/adjacency_list.hpp"
#include "StateChange.h"
#include <vector>
#include "MCQSGraphProperty.h"
typedef boost::adjacency_list<boost::listS, boost::listS,
			      boost::bidirectionalS, StateChange,
			      ViennaMath::variable> MCCQSGraph;//тут могут возьникнут различные ошибки как-нибудь исправь

MCQSGraph createIncomeGraph(vector<StateChange> incomingVertexValueVector, 
			    vector<ViennaMath::variable> incomingEdgeValueVector){
	if (incomingVertexValueVector.length() == incomingEdgeValueVector.length){
		MCCQSGraph resultGraph;
		boost::adjacency_list<>::vertex_descriptor mainVertex = boost::add_vertex(resultGraph);
		for (int i=0; i<incomingVertexValueVector.length(); i++){
		        temp_vertex = boost::add_vertex(resultGraph);
			resultGraph[temp_vertex] = incomingVertexValueVector[i];//переопредели оператор равно
			boost::add_edge(temp_vertex, mainVertex, resultGraph); 
			std::pair<Edge, bool> temp_edge = boost::edge(temp_vertex, mainVertex, resultGraph);
		        boost::put(boost::edge_weight_t(), resultGraph, temp_edge.first, incomingEdgeValueVector[i]);
		}
		return resultGraph
	} else {
		//RaiseError //сделай как-нибудь
	}									
}

MCQSGraph createOutcomeGraph(vector<StateChange> incomingVertexValueVector, 
			    vector<ViennaMath::variable> incomingEdgeValueVector){
	if (incomingVertexValueVector.length() == incomingEdgeValueVector.length){
		MCCQSGraph resultGraph;
		boost::adjacency_list<>::vertex_descriptor mainVertex = boost::add_vertex(resultGraph);
		for (int i=0; i<incomingVertexValueVector.length(); i++){
		        temp_vertex = boost::add_vertex(resultGraph);
			resultGraph[temp_vertex] = incomingVertexValueVector[i];//переопредели оператор равно
			boost::add_edge(mainVertex, temp_vertex, resultGraph); 
			std::pair<Edge, bool> temp_edge = boost::edge(mainVertex, temp_vertex, resultGraph);
		        boost::put(boost::edge_weight_t(), resultGraph, temp_edge.first, incomingEdgeValueVector[i]);
		}
		return resultGraph
	} else {
		//RaiseError //сделай как-нибудь
	}									
}


