#ifndef _BFS_HPP_
#define _BFS_HPP_

#include "graph.hpp"
#include "search.hpp"
#include "vertex.hpp"
#include <string>
#include <queue>

class Bfs: public search
{
	graph* target_graph;
	std::string target_vertex;
	std::vector<vertex*> m_travers;
public:
	void set_target_graph(graph* , const std::string& );
	std::vector<vertex*>* get_traversal_path();
	void show_traversal();
	void traverse();

};

#endif //_BFS_HPP_
