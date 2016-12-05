#ifndef _SEARCH_HPP_
#define _SEARCH_HPP_

#include "graph.hpp"
#include <string>

class search 
{

public:
	/**Setting type of searching  algorithm*/
	virtual void traverse() = 0;
	virtual void show_traversal() = 0;
    virtual void set_target_graph(graph* , const std::string&) = 0;
};


#endif //_SEARCH_H_
