#ifndef _ALGORITHM_HPP_
#define _ALGORITHM_HPP_

#include "search.hpp"
#include "shortest_path.hpp"
#include "Dfs.hpp"
#include "Bfs.hpp"
#include "Dijkstra.hpp"




class algorithm
{

private:
	search* m_search;
	shortest_path* m_shortest_path;
      
public:
	/**Setting type of serarching  algorithm*/
	void set_search_type(search* );
	/**Setting type of  shortest path algorithm*/
	void set_shortest_path_type(shortest_path* ); 
	/**       */
	void traverse();
	int get_shortest_path(); 
public:
	algorithm(); 

};


#endif//_ALGORITHM_H_
