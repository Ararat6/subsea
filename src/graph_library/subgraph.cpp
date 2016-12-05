#include "subgraph.hpp"
#include <cassert>

void subgraph::set_target_graphs(graph* big_graph, graph* small_graph)
{
	m_big_graph = big_graph;
	assert(NULL != m_big_graph);
	m_small_graph = small_graph;
	assert(NULL != m_small_graph);
}

bool subgraph::is_contain_subgraph()
{
	if(m_big_graph->get_vertices_count() 
			< m_small_graph->get_vertices_count()) {
		return false;
	}
	assert(NULL != m_big_graph);
	assert(NULL != m_small_graph);

	std::vector<vertex*> vertices_big = BFS(m_big_graph);
	std::vector<vertex*> vertices_small = BFS(m_small_graph);

	if(min_bisection(vertices_big, vertices_small)) {
		return true;
	} else {
		return false;
	}
}

bool subgraph::min_bisection(std::vector<vertex*>& vertices_big,
		std::vector<vertex*>& vertices_small)
{
	std::vector<vertex*> half1;
	std::vector<vertex*> half2;
	unsigned int SIZE = vertices_big.size();
	for(unsigned i = 0; i < SIZE; ++i) {
		if(i < (SIZE/2  + SIZE%2)){
			half1.push_back(vertices_big[i]);
		} else {
			half2.push_back(vertices_big[i]);
		}
	}


	for(int i = half1.size() - 1; i >= 0; i--) {
		std::vector<base_edge*>::const_iterator it = half1[i]->get_edges()->begin();
		std::vector<base_edge*>::const_iterator end = half1[i]->get_edges()->end();

		for( ; it != end; it++) {
			for(unsigned  j = 0; j < half2.size(); j++) {
				if((*it)->get_destination_vertex()->get_name() == half2[j]->get_name()
						|| (*it)->get_source_vertex()->get_name() == half2[j]->get_name() ) {

					if(match(half1[i], vertices_small)) {
						return true;

					}                 
				}
			}
		}
	}

	return false;
}

bool subgraph::match(vertex* c_vertex, std::vector<vertex *>& vertices_small) 
{
	for(unsigned i = 0; i < vertices_small.size(); i++) {
		if(!vertices_small[i]->get_visited() && equal_vertices(c_vertex, vertices_small[i])) {
			c_vertex->set_visited(true);
			vertices_small[i]->set_visited(true);

			if(search_sub_graph(c_vertex, vertices_small[i], vertices_small)){
				return true;
			}
			for(unsigned k = 0; k < vertices_small.size(); k++) {
				vertices_small[k]->set_visited(false);
			}
		}
	}
	return false;
}


bool subgraph::search_sub_graph(vertex* vertex_big, vertex* vertex_small, std::vector<vertex*>& vertices_small) {

	std::queue<vertex *> queue_small;
	std::queue<vertex *> queue_big;

	queue_small.push(vertex_small);
	queue_big.push(vertex_big);
	vertex_small->set_visited(true);

	while(!queue_small.empty()) {
		vertex * currNode = queue_small.front();
		vertex * bigcurrNode = queue_big.front();
		queue_small.pop();
		queue_big.pop();

		std::vector<base_edge*>::const_iterator it_small_vertex = currNode->get_edges()->begin();
		std::vector<base_edge*>::const_iterator end_small_vertex = currNode->get_edges()->end();
		std::vector<base_edge*>::const_iterator it_big_vertex = bigcurrNode->get_edges()->begin();
		std::vector<base_edge*>::const_iterator end_big_vertex = bigcurrNode->get_edges()->end();

		for(; it_small_vertex != end_small_vertex; ++it_small_vertex) {
			for(; it_big_vertex != end_big_vertex; ++it_big_vertex) {
				if((*it_small_vertex)->get_source_vertex() == currNode
						&& equal_vertices((*it_small_vertex)->get_destination_vertex()
							, (*it_big_vertex)->get_destination_vertex())
						&& !(*it_small_vertex)->get_destination_vertex()->get_visited()
						&& !(*it_big_vertex)->get_destination_vertex()->get_visited()) {

					(*it_small_vertex)->get_destination_vertex()->set_visited(true);
					(*it_big_vertex)->get_destination_vertex()->set_visited(true);
					queue_small.push((*it_small_vertex)->get_destination_vertex());
					queue_big.push((*it_big_vertex)->get_destination_vertex());
					break;

				} else if (equal_vertices((*it_small_vertex)->get_source_vertex()
							, (*it_big_vertex)->get_source_vertex())
						&& !(*it_small_vertex)->get_source_vertex()->get_visited()
						&& !(*it_big_vertex)->get_source_vertex()->get_visited()) {

					(*it_small_vertex)->get_source_vertex()->set_visited(true);
					(*it_big_vertex)->get_source_vertex()->set_visited(true);
					queue_small.push((*it_small_vertex)->get_source_vertex());
					queue_big.push((*it_big_vertex)->get_source_vertex());
					break;
				}
			}
		}

		for(; it_small_vertex != end_small_vertex; ++it_small_vertex) {
			if((*it_small_vertex)->get_source_vertex()->get_visited()) {
				return false;
			}
		}
	}



	for(unsigned i = 0; i < vertices_small.size(); i++) {
		if(!vertices_small[i]->get_visited()) {
			return false;
		}
	}

	return true;
}

vertex* subgraph::get_lowest_vertex(graph* current_graph)
{
	std::map<std::string, vertex*>::const_iterator it = current_graph->get_vertices()->begin();
	std::map<std::string, vertex*>::const_iterator end = current_graph->get_vertices()->end();

	int degree = it->second->get_degree();
	vertex* lowest_vertex = it->second;
	for(; it != end; ++it) {
		if(degree > it->second->get_degree()){
			degree = it->second->get_degree();
			lowest_vertex = it->second;
		}
	}
	return lowest_vertex;


}

bool subgraph::equal_vertices (vertex* v1, vertex* v2) {
	return (v1->get_name() == v2->get_name());
}

std::vector<vertex*> subgraph::BFS (graph* current_graph)
{

	vertex* c_vertex = get_lowest_vertex(current_graph);
	current_graph->set_unvisited();
	std::queue<vertex*> m_queue;
	m_queue.push(c_vertex);
	std::vector<vertex*> m_travers;
	m_travers.push_back(c_vertex);

	std::cout <<std::endl;
	while(!m_queue.empty()){
		vertex* current_vertex = m_queue.front();
		m_queue.pop();
		current_vertex->set_visited(true);
		std::cout <<  current_vertex->get_name() <<std::endl;

		std::vector<base_edge*>::const_iterator it_begin = current_vertex->get_edges()->begin();
		std::vector<base_edge*>::const_iterator it_end = current_vertex->get_edges()->end();

		for(; it_begin != it_end; ++it_begin){
			if((*it_begin)->get_source_vertex() == current_vertex
					&& (*it_begin)->get_destination_vertex()->get_visited() == false){
				m_queue.push((*it_begin)->get_destination_vertex());
				m_travers.push_back((*it_begin)->get_destination_vertex());
				(*it_begin)->get_destination_vertex()->set_visited(true);

			} else if ((*it_begin)->get_source_vertex()->get_visited() == false) {
				m_queue.push((*it_begin)->get_source_vertex());
				m_travers.push_back((*it_begin)->get_source_vertex());
				(*it_begin)->get_source_vertex()->set_visited(true);
			}
		}
	}
	current_graph->set_unvisited();
	return m_travers;
}

	subgraph::subgraph() :m_big_graph(NULL)
			      ,m_small_graph(NULL)
{
}
