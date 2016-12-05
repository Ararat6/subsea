#ifndef _WEIGHTED_EDGE_HPP_
#define _WEIGHTED_EDGE_HPP_

#include "base_edge.hpp"

/**
  * @brief
  * param_egde abstract class for weighted edges of graph  
  */
class weighted_edge: public base_edge
{
private:
    /** Edge weight */
    int m_weight;
public:
    /** Getting the weight of edge*/
    int get_weight();
public:
	//* Constructor */ 
	weighted_edge(const int weigth);
	//* Desstructor */ 
	~weighted_edge();
	
};
#endif  //_WEIGHTED_EDGE_HPP_
