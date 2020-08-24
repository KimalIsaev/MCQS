#include "graph_utilities_without_templates.h"



namespace mcqsgraphutils {
	//Соединяет два графа между собой ребром со значением заданной переменной
	//Выдаёт новый граф, не изменяя данные ему
	/*
	MCQSGraph ConnectTwoGraphsWithEdge(const MCQSGraph& g, const MCQSVertex_descriptor connect_from,
				       const MCQSGraph& j, const MCQSVertex_descriptor connect_to,
				       const viennamath::variable* edge_value) {
		typedef std::map<MCQSVertex_descriptor, MCQSVertex_descriptor> GraphVertexMap;//этот тип позволяет сделать соответствие 
		GraphVertexMap vertex_map_g, vertex_map_j; //из номера вершины в старом графе в номеро вершины в новом графе
		boost::associative_property_map<GraphVertexMap> map_g(vertex_map_g);//инициализация
		boost::associative_property_map<GraphVertexMap> map_j(vertex_map_j);//инициализация
		MCQSGraph result_graph;
		boost::copy_graph(g, result_graph, boost::orig_to_copy(map_g));//копирование графа
		boost::copy_graph(j, result_graph, boost::orig_to_copy(map_j));//с запонимаем под каким новым номером существует старая вершина 
		typename MCQSVertex_descriptor from_g = map_g[connect_from];//смотрим номер вершины от которой хотим провести ребро
		typename MCQSVertex_descriptor to_j = map_j[connect_to];//смотрим номер вершины в которую хотим провести ребро
		boost::add_edge(from_g, to_j, edge_value, result_graph);//создаём ребро
		return result_graph;
	}
	*/
	
	std::pair<MCQSGraph, MCQSVertex_descriptor>
	CreatePompon(const vector<map<int, vector<int>>>& incoming_vertex_value,
		     const viennamath::variable* incoming_edge_value,
		     const vector<map<int, vector<int>>>& outcoming_vertex_value,
		     const viennamath::variable* outcoming_edge_value) {
		if (CheckIfVectorHaveSameSize(incoming_vertex_value, incoming_edge_value) &&
		    CheckIfVectorHaveSameSize(outcoming_vertex_value, outcoming_edge_value)) {
			Graph result_graph;
			typename MCQSVertex_descriptor main_vertex = boost::add_vertex(result_graph);
			typename MCQSVertex_descriptor temp_vertex;
			BOOST_FOREACH(boost::tuple<const  map<int, vector<int>>&, const viennamath::variable*> v,
				      boost::combine(incoming_vertex_value, incoming_edge_value)) {
				temp_vertex = boost::add_vertex(v.get<0>(), result_graph);
				boost::add_edge(temp_vertex, main_vertex, v.get<1>(), result_graph);
			}
			BOOST_FOREACH(boost::tuple<const  map<int, vector<int>>&, const viennamath::variable*> v,
				      boost::combine(incoming_vertex_value, incoming_edge_value)) {
				temp_vertex = boost::add_vertex(v.get<0>(), result_graph);
				boost::add_edge(main_vertex, temp_vertex, v.get<1>(), result_graph);
			}
			return std::make_pair(result_graph, main_vertex);
		}
		else {
			throw std::invalid_argument("different sizes of edge and vertex value vectors");;
		}
	}
	/*
	void EndDepthFirstSearch(const MCQSGraph& g, const MCQSVertex_descriptor v,
		std::list<MCQSVertex_descriptor>& all_vertecies_in_current_path,
		std::vector<std::list<MCQSVertex_descriptor>>& all_path) {
		std::pair<boost::graph_traits<MCQSGraph>::out_edge_iterator, boost::graph_traits<MCQSGraph>::out_edge_iterator>
			pair_edge_iterator = boost::out_edges(v, g);
		if (pair_edge_iterator.first != pair_edge_iterator.second) {
			for (auto i = pair_edge_iterator.first; i != pair_edge_iterator.second; i++) {
				all_vertecies_in_current_path.push_front(g[i]);
				EndDepthFirstSearch(g, i, all_vertecies_in_current_path, all_path);
			}
		}
		else {
			all_path.push_back(all_vertecies_in_current_path);
		}
	}
	
        std::vector<std::vector<std::list<MCQSVertex_descriptor>>> AllPath(const MCQSGraph& g) {
		std::list<MCQSVertex_descriptor> verticies_to_start_from;
		int number_of_end_verticies = 0;
		for (int i = 0; i < boost::num_vertices(g); i++) {
			if (!in_degree(i, g)) {
				verticies_to_start_from.push_front(i);
			}
			else if (!out_degree(i, g)) {
				number_of_end_verticies++;
			}
		}
		std::vector<std::vector<std::list<MCQSVertex_descriptor>>> result_tensor(verticies_to_start_from.size());
		BOOST_FOREACH(boost::tuple<const MCQSVertex_descriptor, std::vector<std::list<MCQSVertex_descriptor>>&> v,
			      boost::combine(verticies_to_start_from, result_tensor)) {
			std::list<MCQSVertex_descriptor> temp_path;
			v.get<1>().resize(number_of_end_verticies);
			EndDepthFirstSearch(g, v.get<0>(), temp_path, v.get<1>());
		}
		return result_tensor;
	}
*/
	/*позже допишу
	std::vector<std::pair<viennamath::expr, std::map<int, std::vector<int>>>> AllPathToAllChanges(MCQSGraph g,
												      std::vector<std::vector<std::list<MCQSVertex_descriptor>>> all_changes){
		std::vector<std::pair<viennamath::expr, std::map<int, std::vector<int>>> result(all_changes.size());
		std::pair<viennamath::expr, std::map<int, std::vector<int>>> temp_pair, path_pair;
		for(int i=0; i<all_changes.size();i++){
			temp_pair = std::pair<viennamath::expr, std::map<int, std::vector<int>>>(); //будет складывать результаты проходов по разным путям
			for(int j=0; j<all_changes[i].size();j++){
				path_pair = make_paiviennamath::expr, std::map<int, std::vector<int>>; //будет вычислять результат прохода по одному пути
				
				for (MCQSVertex_descriptor vertex : all_changes[i][j]) {									
					path_pair.first *= *(g[vertex]); 
				}
				
				
			}
		}
	}
	*/
}
