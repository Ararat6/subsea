#include "Dijkstra.hpp"

void Dijkstra::set_distance(int dist)
{
    m_distance = dist;
}

vertex* Dijkstra::find_vertex(const std::string target_vertex)
{
    return m_graph->get_vertex_by_name(target_vertex);
}

bool Dijkstra::short_path_to_map(base_edge* current_edge, 
								 std::map<vertex*,int>& v_map)
{
	vertex* d_vertex = current_edge->get_destination_vertex();
	vertex* s_vertex = current_edge->get_source_vertex();
	std::vector<vertex*>* s_path = s_vertex->get_shortest_path();
    int first_weight = v_map[d_vertex];
    int new_weight = current_edge->get_weight() + v_map[s_vertex];
	if (first_weight == 0 || 
		(first_weight > new_weight)) {
		v_map[d_vertex] = new_weight;
		d_vertex->set_shortest_path(s_path);
		return true;
	}
	return false;
}

bool Dijkstra::short_path_to_map_un(base_edge* current_edge, 
		   							std::map<vertex*,int>& v_map)
{
	vertex* d_vertex = current_edge->get_destination_vertex();
	vertex* s_vertex = current_edge->get_source_vertex();
	std::vector<vertex*>* d_path = d_vertex->get_shortest_path();
	int first_weight = v_map[s_vertex];
	int new_weight = current_edge->get_weight() + v_map[d_vertex];
	if(!s_vertex->get_visited()){
		if(first_weight == 0 || first_weight > new_weight){
			v_map[s_vertex] = new_weight;
			s_vertex->set_shortest_path(d_path);
			return true;
		}   
	}     
	return false;
} 

void Dijkstra::find_distance()
{
	std::cout << "source = " <<  source_vertex->get_name() <<"\n";//
	std::cout << "destinatioan = " << destination_vertex->get_name()<<"\n";//
	vertex* curr_vertex;
	std::queue<vertex*> que;
	que.push(source_vertex); 
	std::map<vertex*, int> v_map;

	while(!que.empty()){
		curr_vertex = que.front();
		que.pop();
		std::vector<base_edge*>::const_iterator it = curr_vertex->get_edges()->begin();
		std::vector<base_edge*>::const_iterator end = curr_vertex->get_edges()->end();
		bool check = true;
		for(; it != end; ++it){
			base_edge* current_edge = (*it);
		   	vertex* s_vertex = current_edge->get_source_vertex();
			vertex* d_vertex = current_edge->get_destination_vertex();
			if(s_vertex == curr_vertex){
				check = short_path_to_map(current_edge, v_map);
				if(check == true){
					check = false;
					que.push(d_vertex);
				} 
			} else if(m_graph->get_direction() == undirected) {
				check = short_path_to_map_un(current_edge, v_map);
				if(check == true) {
					que.push(s_vertex);
					check = false;
				}
			}
		}
	}
	set_distance(v_map[destination_vertex]);
	show_shortest_path();
}

void Dijkstra::set_target_graph(graph* c_graph, 
		 						const std::string& source,
							   	const std::string& destination)
{
    m_graph = c_graph;
    source_vertex = find_vertex(source);
	source_vertex->set_visited(true);
    destination_vertex = find_vertex(destination);
}

void Dijkstra::show_shortest_path()
{
	std::vector<vertex*>* path = destination_vertex->get_shortest_path();
	std::vector<vertex*>::iterator it = path->begin();
	std::vector<vertex*>::iterator end = path->end();
	std::cout << "Shortest path = ";
	if(0 == path->size()) {
		std::cout << "0 : Not path betwen source and destination ";
	}
	for(;it != end ; ++it) {
		std::cout << (*it)->get_name() << " " ;
	}
	std::cout << "\n";
}

int  Dijkstra::short_distance()
{
    find_distance();
    return m_distance;
}

Dijkstra::Dijkstra()
    				:m_distance(0)
{
}
