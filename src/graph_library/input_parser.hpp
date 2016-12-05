#ifndef _INPUT_PARSER_HPP_
#define _INPUT_PARSER_HPP_

#include "vertex.hpp"
#include "graph.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

class input_parser
{
private:    
	int m_line; 
	int m_vertices_count;
    std::map <std::string , graph* > m_graphs;   
private:
	bool parse_graph(std::stringstream& buffer, graph* _graph);
	bool set_graph_type(const std::string first_line, graph* _graph);
	void read_file(const std::string& path, std::stringstream& buffer);
	bool set_graph_direction_type(std::istringstream&, graph*);
	bool set_graph_vertices_count(std::istringstream&);
	bool set_graph_weighted_type(std::istringstream&, graph*);
	bool check_first_line(std::stringstream&, graph*);
	bool parsing(std::stringstream&, graph*);
public:
    graph* create_graph(const std::string& file_path);
};
#endif  //_INPUT_PARSER_HPP_
