#include "input_parser.hpp"
#include "graph_exception.hpp"
#include <stdlib.h>

graph* input_parser::create_graph(const std::string &file_path)
{
    m_line = 0;
	m_vertices_count = 0;
	std::stringstream buffer;
	
	graph* current_graph = m_graphs[file_path];
	if(NULL == current_graph) {
		current_graph = new graph();
		m_graphs[file_path] = current_graph;
	} else {
		return current_graph;
	}

	read_file(file_path, buffer);

	if(!check_first_line(buffer, current_graph)){
		return NULL;
	}

	if(!parsing(buffer, current_graph)){
		return NULL;
	} else {
		return current_graph;
	}
}

void input_parser::read_file(const std::string& file_path, std::stringstream& buffer)
{
	std::fstream input_file;
	input_file.open(file_path.c_str());
	if(input_file) {
		buffer << input_file.rdbuf();
		input_file.close();
	} 
}

bool input_parser::check_first_line(std::stringstream& buffer, graph* current_graph)
{
	std::string line;
	if(getline( buffer, line )) { 
		std::istringstream iss(line);
		++m_line;
		if(! set_graph_type(line, current_graph)) {
			//TODO generate exp
			return false;
		}
	} else {
		throw graph_exception("Buferr read exception, not input file or empty file");
		return false;
	}
	return true;
}


bool input_parser::parsing(std::stringstream& buffer, graph* current_graph)
{
	if(parse_graph(buffer, current_graph)) {
		if( m_vertices_count != current_graph->get_vertices_count()) {
			throw graph_exception("Exception graph  creation, set correct count of vertices", m_line);
			return false; 
		} else {
			return true;
		}
	} else {
		throw graph_exception("Exception graph  creation", m_line);
		return false;
	}
}


bool input_parser::set_graph_type(const std::string first_line, graph* current_graph)
{
	std::istringstream iss(first_line);

	if(!set_graph_direction_type(iss, current_graph)){
		return false;
	}
	if(!set_graph_vertices_count(iss)){
		return false;
	}
	if(!set_graph_weighted_type(iss, current_graph)){
		return false;
	}
	std::string word;
	if(iss >> word){
		throw graph_exception("Don't input more arguments in line of about your graph", m_line); 
		return false;
	}
	return true;
}		

bool input_parser::set_graph_direction_type(std::istringstream& iss, graph* current_graph) 
{
	
	std::string str_direction;
	if (iss >> str_direction) {
		if ( 0 == str_direction.compare("0") ) {
			current_graph->set_direction(undirected);
		}
		else if	( 0 == str_direction.compare("1") ) {
			//int direction = atoi(str_directi on.c_str());
			current_graph->set_direction(directed);
		} else {
			throw graph_exception("Incorrect input format, for directon set (1) or (0)", m_line);
			return false;
		}
	} else {
		throw graph_exception("Incorrect input format, set graph type", m_line);
		return false;
	}
	return true;

}


bool input_parser::set_graph_vertices_count(std::istringstream& iss)
{
	std::string str_vertex_count;
	if(iss >> str_vertex_count) {
		int int_vertex_count;
		int_vertex_count = atoi(str_vertex_count.c_str());
		if(int_vertex_count > 1) {
			m_vertices_count = int_vertex_count;
		} else {
			throw graph_exception("Incorrect input format, for count", m_line);
			return false;
		}
	} else {
		throw graph_exception("Incorrect input format, for count", m_line);
		return false;
	}

	return true;

}


bool input_parser::set_graph_weighted_type(std::istringstream& iss, graph* current_graph)
{

	std::string str_weight;
	if(iss >> str_weight) {
		if ( 0 == str_weight.compare("1") ) {
			current_graph->set_edge_weight(weighted);
		}
		else if	( 0 == str_weight.compare("0") ) {
			current_graph->set_edge_weight(unweighted);
		} else {
			throw graph_exception("Incorrect input format, for edge weight set (1) or (0)", m_line);
			return false;
		}
	} else {
		throw graph_exception("Incorrect input format, for edge weight set (1) or (0)", m_line);
		return false;
	}

	return true;

}



bool input_parser::parse_graph(std::stringstream& buffer, graph* current_graph)
{
	std::string line;
	int weight;
	bool is_weighted = false;
	int words_count = 2;
	if(current_graph->get_edge_weight() == weighted) {
		words_count = 3;
	    is_weighted = true;
	}

	while(getline(buffer, line)) {
		std::istringstream iss(line);
		std::string word = "";
		weight = 0;
        ++m_line;
		vertex* source = NULL; 
		vertex* destination = NULL;
		
		int i = 1;
		while(i <= words_count && iss >> word ) {
			if(NULL == destination) {
				if(NULL == source) {
					source = current_graph->add_vertex(word);
				}
				else { 
					destination = current_graph->add_vertex(word); 
				}
			}
		   	else {
				weight = atoi(word.c_str()); 
				if(0 >= weight && (0 != word.compare("0"))){ 
					throw graph_exception("Enter weight positive integer", m_line);
					return false;
				}	
			}
			++i;
		}
		if(iss >> word){
			throw graph_exception("Don't input more arguments", m_line);
			return false;
		}

		if( NULL == destination) {
			throw graph_exception("Input correct pair of vertices", m_line);
			return false;
		}
		if(is_weighted){
			current_graph->add_edge(source, destination, weight);
		} else {
			current_graph->add_edge(source, destination);
		}
	}
	return true;
}

