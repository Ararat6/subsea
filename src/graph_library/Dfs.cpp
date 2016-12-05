#include "Dfs.hpp"

void Dfs::set_target_graph(graph* c_graph, const std::string& c_vertex)
{
	target_graph = c_graph;
	target_vertex =  c_vertex;

}

std::vector<vertex*>* Dfs::get_traversal_path()
{
	return &m_travers;
}

void Dfs::show_traversal()
{
	std::vector<vertex*>::iterator it_begin = m_travers.begin();
	std::vector<vertex*>::iterator it_end = m_travers.end();

	for(; it_begin != it_end; ++it_begin){
		std::cout << (*it_begin)->get_name() << " ";
	}

	std::cout <<"\n";
}

void Dfs::traverse()
{
	vertex* current_vertex = target_graph->get_vertex_by_name(target_vertex);
	std::stack<vertex*> m_stack;
	m_stack.push(current_vertex);

	while(!m_stack.empty()){
		current_vertex = m_stack.top();
		m_stack.pop();
		current_vertex->set_visited(true);
		m_travers.push_back(current_vertex);

		std::vector<base_edge*>::const_iterator it_begin = current_vertex->get_edges()->begin();
		std::vector<base_edge*>::const_iterator it_end = current_vertex->get_edges()->end();

		for(; it_begin != it_end; ++it_begin){
			if((*it_begin)->get_source_vertex() == current_vertex 
					&& (*it_begin)->get_destination_vertex()->get_visited() == false){
				m_stack.push((*it_begin)->get_destination_vertex());
				(*it_begin)->get_destination_vertex()->set_visited(true);

			} else if((*it_begin)->get_source_vertex()->get_visited() == false){
				m_stack.push((*it_begin)->get_source_vertex());
				(*it_begin)->get_source_vertex()->set_visited(true);
			}
		}
	}
}
