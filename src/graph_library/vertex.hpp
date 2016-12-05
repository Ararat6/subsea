#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_
#include "base_edge.hpp"
#include <vector>
#include <string>
//class base_edge;

/** 
  * @brief
  * Class for all vertices
  */
class vertex
{
private:
    /** Vector of neighbour vertices edges, 
      * which shows destination for this vertex
      */
    std::vector<base_edge*> m_edges;
    std::string m_name;
	int m_degree;
	bool m_is_visited;
	std::vector<vertex*> m_shortest_path;
public:
    /** For adding edge in vertex */
    void add_edge(base_edge* node_edge);
    /** For getting edges of vertex */
	const std::vector<base_edge*>* get_edges() const;
    /** For getting vertex degree */
    int get_degree() const;
	void add_degree();
    /** For getting vertex name */
    std::string get_name() const;
	std::vector<vertex*>* get_shortest_path();
	void set_shortest_path(std::vector<vertex*>*);

	void set_visited(const bool is_visited);
	bool get_visited() const;
public:
    /** Constructor */
    vertex(const std::string& name);
    /** Destructor */
    ~vertex();
};
#endif  //_VERTEX_HPP_
