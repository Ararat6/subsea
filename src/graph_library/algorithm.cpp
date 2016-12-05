#include "algorithm.hpp"

void algorithm::set_search_type(search* c_search)
{
    m_search = c_search;
}

void algorithm::set_shortest_path_type(shortest_path* c_shortest)
{
    m_shortest_path = c_shortest;
}

void algorithm::traverse()
{
	m_search->traverse();
	m_search->show_traversal();
}

int algorithm::get_shortest_path()
{
    return m_shortest_path->short_distance();
}

algorithm::algorithm()
    :m_search(NULL)
    ,m_shortest_path(NULL)
{
}
