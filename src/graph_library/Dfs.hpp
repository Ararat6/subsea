#ifndef _DFS_HPP_
#define _DFS_HPP_

#include "graph.hpp"
#include "search.hpp"
#include <string>
#include <stack>

class Dfs: public search
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

#endif //_DFS_HPP_
