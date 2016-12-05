#ifndef _DIJKSTRA_HPP_
#define _DIJKSTRA_HPP_

#include "shortest_path.hpp"
#include "algorithm.hpp"
#include "graph.hpp"
#include <vector>
#include <string>
#include <queue>
#include <map>

class Dijkstra: public shortest_path
{ 
    int m_distance;
    graph* m_graph;
    vertex* source_vertex;
    vertex* destination_vertex;

private:
    void set_distance(int);
    bool short_path_to_map(base_edge*, std::map<vertex*,int>& );
    bool short_path_to_map_un(base_edge*, std::map<vertex*,int>& );

private:
    void find_distance();
    vertex* find_vertex(const std::string);

public:
    //	void set_target_graph(graph* , std::string&);
    void set_target_graph(graph* , const std::string&, const std::string&);
	void show_shortest_path();
public:
    int short_distance();

public:
    Dijkstra();

};

#endif //_DIJKSTRA_HPP_
