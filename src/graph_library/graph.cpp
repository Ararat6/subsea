#include "graph.hpp"
#include <iostream>

vertex* graph::add_vertex(const std::string& name)
{
	vertex* current_vertex = NULL;
	current_vertex = m_vertices[name];
	if(NULL != current_vertex) {
		return current_vertex;
	}
	current_vertex = new vertex(name);
	if(NULL != current_vertex) {
		m_vertices[name] = current_vertex;
		return current_vertex;
	} else {
		//TODO exception CANNOT create vertex";
	}
	return current_vertex;
}

vertex* graph::get_vertex_by_name(const std::string& name) 
{
	vertex* vertex_by_name = m_vertices[name];
    return vertex_by_name;
}

void graph::add_edge(vertex* source, vertex* destination)
{
	base_edge* b_edge = new edge();
	b_edge->set_source_vertex(source);
	b_edge->set_destination_vertex(destination);
	source->add_edge(b_edge);
	source->add_degree();
	if(get_direction() == undirected) {
		destination->add_edge(b_edge);
		destination->add_degree();
	}

}

void graph::add_edge(vertex* source, vertex* destination, int weight)
{
	base_edge* b_edge = new weighted_edge(weight);
	b_edge->set_source_vertex(source);
	b_edge->set_destination_vertex(destination);
	source->add_edge(b_edge);
	source->add_degree();
	if(get_direction() == undirected) {
		destination->add_edge(b_edge);
		destination->add_degree();
	}
}

direction graph::get_direction() const
{
    return m_direction;
}
void graph::set_direction(direction dir)
{
	m_direction = dir;
}

edge_weight graph::get_edge_weight() const
{
	return m_edge_weight;
}

void graph::set_edge_weight(edge_weight weight)
{
	m_edge_weight = weight;
}

int graph::get_vertices_count() const
{
	return m_vertices.size();
}

const std::map<std::string, vertex*>* graph::get_vertices() const
{
    return &m_vertices;
}

void graph::set_unvisited()
{
	std::map<std::string, vertex*>::iterator it = m_vertices.begin();
	std::map<std::string, vertex*>::iterator end = m_vertices.end();

	for(; it != end; ++it) {
        it->second->set_visited(false);
    }
    
}

void graph::show_graph() 
{
	std::map<std::string, vertex*>::iterator it = m_vertices.begin();
	std::map<std::string, vertex*>::iterator end = m_vertices.end();
	for(; it != end; ++it) {
		std::vector<base_edge*>::const_iterator _it = it->second->get_edges()->begin();
		std::vector<base_edge*>::const_iterator _end = it->second->get_edges()->end();
//		system("Color 4D");
		const std::string col("\033[1;92m");
		const std::string cole("\033[0m");
		std::cout << col << "Vertex Name = " << it->first << cole;
		std::cout <<"\nv_degree = " << it->second->get_degree() ;
		for( ; _it != _end; ++_it){
			std::cout << "\n    |s_vertex = " << (*_it)->get_source_vertex()->get_name() << "|"
				<< "      |d_vertex = " << (*_it)->get_destination_vertex()->get_name() << "|"
				<< "      |weight edge = " << (*_it)->get_weight()  << "|"  ;
		}
		std::cout << "\n\n";
	}
	
}

graph::graph()
{}

graph::~graph()
{
	std::map<std::string, vertex*>::iterator it = m_vertices.begin();
	std::map<std::string, vertex*>::iterator end = m_vertices.end();
	for(; it != end; ++it) {
		delete it->second;
	}
}

