#include <vector>
#include <utility>

#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/copy.hpp"
#include "boost/foreach.hpp"
#include "boost/tuple/tuple.hpp"
#include "viennamath/expression.hpp"

#include "state_change.h"

typedef boost::adjacency_list<boost::vecS, boost::vecS,
			      boost::bidirectionalS, StateChange,
			      viennamath::variable*> MCQSGraph;
typedef boost::graph_traits<MCQSGraph>::vertex_descriptor MCQSVertex_descriptor;

//Помпон - это ориентированный звёздочный граф степени (n+m)
//в котором n входящих в центральную вершину рёбер
//и m исходящих
//эта функция выдаёт сам помпон и его центральную вершину
//для любого i, i-ое свойство ребра будет присвоено ребру которое выходит из вершины с i-ым свойством вершины
std::pair<MCQSGraph, MCQSVertex_descriptor>
CreatePompon(const vector<StateChange> &incoming_vertex_value, 
	     const vector<viennamath::variable*> &incoming_edge_value,
	     const vector<StateChange> &outcoming_vertex_value, 
	     const vector<viennamath::variable*> &outcoming_edge_value){
	if ((incoming_vertex_value.size() == incoming_edge_value.size()) && (outcoming_vertex_value.size() == outcoming_edge_value.size())){
		MCQSGraph result_graph;
		MCQSVertex_descriptor main_vertex = boost::add_vertex(result_graph);
	        MCQSVertex_descriptor temp_vertex;
		BOOST_FOREACH(boost::tuple<StateChange&, viennamath::variable*> v, boost::combine(incoming_vertex_value, incoming_edge_value)){
			temp_vertex = boost::add_vertex(v.get<0>(), result_graph);
			boost::add_edge(temp_vertex, main_vertex, v.get<1>(), result_graph); 
		}
		BOOST_FOREACH(boost::tuple<StateChange&, viennamath::variable*> v, boost::combine(outcoming_vertex_value, outcoming_edge_value)){
			temp_vertex = boost::add_vertex(v.get<0>(), result_graph);
			boost::add_edge(main_ertex, temp_vertex, v.get<1>(), result_graph); 
		}
		return std::make_pair(result_graph, main_vertex);
	} else {
		throw std::invalid_argument("different sizes of edge and vertex value vectors");;
	}
}


//Соединяет два графа между собой ребром со значением заданной переменной
//Выдаёт новый граф, не изменяя данные ему
MCQSGraph ConnectTwoGraphsWithEdge(const MCQSGraph &g, const MCQSVertex_descriptor connect_from,
				   const MCQSGraph &j, const MCQSVertex_descriptor connect_to,
				   const viennamath::variable *edge_value){
	typedef std::map<MCQSVertex_descriptor, MCQSVertex_descriptor> MCQSVertex_map;//этот тип позволяет сделать соответствие 
	MCQSVertex_map vertex_map_g, vertex_map_j; //из номера вершины в старом графе в номеро вершины в новом графе
	boost::associative_property_map<MCQSVertex_map> map_g(vertex_map_g);//инициализация
	boost::associative_property_map<MCQSVertex_map> map_j(vertex_map_j);//инициализация
	MCQSGraph result_graph;
	boost::copy_graph(g, result_graph, boost::orig_to_copy(map_g));//копирование графа
	boost::copy_graph(j, result_graph, boost::orig_to_copy(map_j));//с запонимаем под каким новым номером существует старая вершина 
	MCQSVertex_descriptor from_g = map_g[connect_from];//смотрим номер вершины от которой хотим провести ребро
	MCQSVertex_descriptor to_j = map_j[connect_to];//смотрим номер вершины в которую хотим провести ребро
	boost::add_edge(from_g, to_j, edge_value, result_graph);//создаём ребро
	return result_graph;
}

//выдаёт граф, который используется после окончания работы прибора
MCQSGraph CreateExecutionGraph(const viennamath::variable *orbit_chance,
			       const viennamath::variable *exit_chance,
			       const viennamath::variable *connection_to_phase_graph,
			       const std::pair<MCQSGraph, MCQSVertex_descriptor>> phase_graph){
	MCQSGraph temp_graph;
	vector<int> orbit_change = {+1};//временная мера, потом придумаем какой размер должен быть тут
	StateChange only_orbit_change = StateChange::StateChangeWithOrbit(orbit_change);
	MCQSVertex_descriptor main_vertex = boost::add_vertex(temp_graph),
		orbit_vertex = boost::add_vertex(temp_graph, only_orbit_change),
		exit_vertex = boost::add_vertex(temp_graph);
	boost::add_edge(main_vertex, orbit_vertex, orbit_chance, result_graph);
	boost::add_edge(main_vertex, exit_vertex, exit_chance, result_graph); 
	return connectTwoGraphsWithEdge(temp_graph, again_vertex,
					phase_graph.first, phase_graph.second,
					connection_to_phase_graph);
}
/*
template<T>
inline bool CheckIfVectorHaveSameSize(vector<T> v1, vector<T> v2){
	return v1.size() == v2.size();
}
*/

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

/*
vector<StateChange> createStateChangeVectorFromOrbitAndPhase(vector<vector<int>> orbit,
							     vector<vector<int>> phase){
	
}

vector<StateChange> createStateChangeVectorFromOrbitAndPhase(vector<int> orbit,
							     vector<vector<int>> phase){
	
}

vector<StateChange> createStateChangeVectorFromOrbitAndPhase(vector<vector<int>> orbit,
							     vector<int> phase){
	
}
*/


int main(){//example
	vector<vector<int>> onesMatrixVector = GenereteOneMatrixVector(5);
	vector<int> zeroVector = GenereteZeroVector(3);
	viennamath::variable one(0);
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
	vector<int> oneZero(2);;//[0,1]
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
	try {
		MCQSGraph startGraph_OneFlow_OneOrbit_TwoPhase_WithExuction = createBattery(incomingFlowStateChange,
			incomingFlow,
			fullPhaseChange,
			q, &one);
		for (int i = 0; i < 6; i++)
		{
			cout << startGraph_OneFlow_OneOrbit_TwoPhase_WithExuction[boost::vertex(i, 
				startGraph_OneFlow_OneOrbit_TwoPhase_WithExuction)] << endl;
		}

		typedef boost::property_map<MCQSGraph, boost::edge_weight_t>::type WeightMap;

		WeightMap weights = boost::get(boost::edge_weight_t(), startGraph_OneFlow_OneOrbit_TwoPhase_WithExuction);

		for (MCQSGraph::edge_descriptor edge : 
				boost::make_iterator_range(boost::edges(startGraph_OneFlow_OneOrbit_TwoPhase_WithExuction))) {
			std::cout << boost::get(weights, edge) << " " << edge << "   ";
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
	}
	//создал граф

	return 0;
}
