#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include "vertex.hpp"
#include "weighted_edge.hpp"
#include "edge.hpp"
#include "base_edge.hpp"
#include <string>
#include <map>


/** Definition of types of graph */ 
enum direction { directed, undirected };
enum edge_weight { weighted, unweighted };

/**
  * @brief 
  * A singleton class to represent a graph. 
  * A graph is an vector of vertices.
  */ 
class graph 
{
private:
    /** Vector of all vertices */
    std::map<std::string, vertex*> m_vertices;
    /** Member for fix graph direction type */
    direction m_direction;
	edge_weight m_edge_weight;
public:
	/** Function for add vertex to graph  */
	vertex* add_vertex(const std::string& name);
	/** Function for get vertex from graph by name */
    vertex* get_vertex_by_name(const std::string& name);
	
	void add_edge(vertex* source, vertex* destination);
	void add_edge(vertex* source, vertex* destination, int weight);
    /** Function for get graph direction type */
    direction get_direction() const;
	void set_direction(direction dir);
	edge_weight get_edge_weight() const;
	void set_edge_weight(edge_weight weight);
    void set_unvisited();
	int get_vertices_count() const;
    const std::map<std::string, vertex*>* get_vertices() const;
	void show_graph();
public:
    /** Constructor */
    graph();
    /** Destructor */
    ~graph();    

};

#endif //_GRAPH_HPP_
