#include "weighted_edge.hpp"

int weighted_edge::get_weight() 
{
	return m_weight;
}

weighted_edge::weighted_edge(const int weight):base_edge()
											  ,m_weight(weight)   
{}
	 
weighted_edge::~weighted_edge() {}
