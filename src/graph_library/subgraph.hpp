#ifndef _SUBGRAPH_HPP_
#define _SUBGRAPH_HPP_

#include "graph.hpp"
#include "vertex.hpp"
#include <vector>
#include <queue>
#include <iostream>


/**
 * @brief Class for finding isomorphic subgraph in big graph, which is isomorph small graph
 */
class subgraph
{

private:
	graph* m_big_graph;
	graph* m_small_graph;

private:
	/** halve two parts graph vertices vector */
	bool min_bisection(std::vector<vertex*>& vertices_big
			, std::vector<vertex*>& vertices_small);
	/** set target vertex from min_bisection and find appropriate vertex in small graph*/
	bool match(vertex* c_vertex, std::vector<vertex *>& vertices_small);
	/** set two target vertex, from big and small graphs*/
	bool search_sub_graph(vertex* vertex_big, vertex* vertex_small
			, std::vector<vertex*>& vertices_small);
	/** get vertex, which has the lowest degree of*/
	vertex* get_lowest_vertex(graph* current_graph);
	/** return true, if two vertices have the same name*/
	bool equal_vertices (vertex* v1, vertex* v2);
	/** return vertex of vertices from BFS search*/
	std::vector<vertex*> BFS (graph* );

public:
	/** set two graph for search isomorphic subgraph*/
	void set_target_graphs(graph* big_graph, graph* small_graph);
	/** return true if in first input graph have subgraph, which is isomorph second input graph*/
	bool is_contain_subgraph();
public:
	/** constructor*/
	subgraph();

};



#endif //_SUBGRAPH_HPP_
