#ifndef _SHORTEST_PATH_HPP_
#define _SHORTEST_PATH_HPP_

#include "graph.hpp"
#include <string>

class shortest_path
{

public:
	/**Setting type of  shortest path  algorithm*/
	virtual int short_distance() = 0;
    virtual void set_target_graph(graph* , const std::string&, const std::string&) = 0;

};


#endif //_SHORTEST_PATH_HPP_
