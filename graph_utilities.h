#include <utility>

#include "boost/graph/copy.hpp"

//Соединяет два графа между собой ребром со значением заданной переменной
//Выдаёт новый граф, не изменяя данные ему
namespace mcqsgraphutils{
	template <class Graph, class EdgeProperty>
		Graph ConnectTwoGraphsWithEdge(const Graph &g, const Graph::vertex_descriptor connect_from,
					       const Graph &j, const Graph::vertex_descriptor connect_to,
					       const EdgeProperty const &edge_value){
		typedef std::map<Graph::vertex_descriptor, Graph::vertex_descriptor> GraphVertexMap;//этот тип позволяет сделать соответствие 
		graph_vertex_map vertex_map_g, vertex_map_j; //из номера вершины в старом графе в номеро вершины в новом графе
		boost::associative_property_map<GraphVertexMap> map_g(vertex_map_g);//инициализация
		boost::associative_property_map<GraphVertexMap> map_j(vertex_map_j);//инициализация
		Graph result_graph;
		boost::copy_graph(g, result_graph, boost::orig_to_copy(map_g));//копирование графа
		boost::copy_graph(j, result_graph, boost::orig_to_copy(map_j));//с запонимаем под каким новым номером существует старая вершина 
		typename Graph::vertex_descriptor from_g = map_g[connect_from];//смотрим номер вершины от которой хотим провести ребро
		typename Graph::vertex_descriptor to_j = map_j[connect_to];//смотрим номер вершины в которую хотим провести ребро
		boost::add_edge(from_g, to_j, edge_value, result_graph);//создаём ребро
		return result_graph;
	}

	template<T>
		inline bool CheckIfVectorHaveSameSize(vector<T> v1, vector<T> v2){
		return v1.size() == v2.size();
	}

	template<Graph, CollectionType1, CollectionType2>
		std::pair<Graph, Graph::vertex_descriptor>	
		CreatePompon(const CollectionType1 const &incoming_vertex_value, 
			     const CollectionType2 const &incoming_edge_value,
			     const CollectionType1 const &outcoming_vertex_value, 
			     const CollectionType2 const &outcoming_edge_value){
		if (CheckIfVectorHaveSameSize(incoming_vertex_value, incoming_edge_value) &&
		    CheckIfVectorHaveSameSize(outcoming_vertex_value, outcoming_edge_value)) {
			typedef CollectionType1::value_type VertexValue;
			typedef CollectionType2::value_type EdgeValue;
			Graph result_graph;
			typename Graph::vertex_descriptor main_vertex = boost::add_vertex(result_graph);
			typename Graph::vertex_descriptor temp_vertex;
			BOOST_FOREACH(boost::tuple<const VertexValue const&, const EdgeValue const&> v,
				      boost::combine(incoming_vertex_value, incoming_edge_value)){
				temp_vertex = boost::add_vertex(v.get<0>(), result_graph);
				boost::add_edge(temp_vertex, main_vertex, v.get<1>(), result_graph); 
			}
			BOOST_FOREACH(boost::tuple<const VertexValue const&, const EdgeValue const&> v,
				      boost::combine(incoming_vertex_value, incoming_edge_value)){
				temp_vertex = boost::add_vertex(v.get<0>(), result_graph);
				boost::add_edge(main_vertex, temp_vertex, v.get<1>(), result_graph); 
			}
			return std::make_pair(result_graph, main_vertex);
		} else {
			throw std::invalid_argument("different sizes of edge and vertex value vectors");;
		}
	}
}
