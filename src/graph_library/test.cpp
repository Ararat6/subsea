/*#include <graph_library/graph.hpp>
#include <graph_library/input_parser.hpp>
#include <graph_library/algorithm.hpp>
#include <graph_library/search.hpp>
#include <graph_library/Dfs.hpp>
#include <graph_library/Bfs.hpp>
#include <graph_library/graph_exception.hpp>
#include <graph_library/subgraph.hpp>*/
#include "graph.hpp" //
#include "input_parser.hpp"
#include "algorithm.hpp"
#include "search.hpp"
#include "Dfs.hpp"
#include "Bfs.hpp"
#include "graph_exception.hpp"
#include "subgraph.hpp" //
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

int main()
{	
    std::cout << "\n\n\n\n\n";
    
    input_parser parser;

    std::string file_path = "./graph.txt";
    graph* test_graph;
    
    std::string file_path1 = "./small.txt";
    graph* test_graph1;
    
    try {
        test_graph = parser.create_graph(file_path);
        assert(NULL != test_graph);
        if(directed == test_graph->get_direction()){
            std::cout << "\nDirected Graph " << "\n";
        } else {
            std::cout << "\nUndirected Graph " << "\n";
        }
        test_graph->show_graph();

        std::cout << "\n\n\n\n\n";

        test_graph1 = parser.create_graph(file_path1);
        assert(NULL != test_graph1);
        if(directed == test_graph1->get_direction()){
            std::cout << "\nDirected Graph " << "\n";
        } else {
            std::cout << "\nUndirected Graph " << "\n";
        }
        test_graph1->show_graph();
        std::cout << "\n\n\n\n\n";
        //search* alg_search = new Dfs();
        //assert(NULL != alg_search);
        //alg_search->set_target_graph(test_graph, "v1");
        //shortest_path* alg_shortest = new Dijkstra();
        //assert(NULL != alg_shortest);
        //alg_shortest->set_target_graph(test_graph, "v1", "v5");

        //algorithm alg;
        //alg.set_shortest_path_type(alg_shortest);
        //std::cout << "Distance between source and destination = " 
        //				<< alg.get_shortest_path() << std::endl;
        //std::cout << "\n";

        //alg.set_search_type(alg_search);
        //std::cout << "Traverse graph from source vertex = ";
        //alg.traverse();
        //std::cout << "\n";

        //subgraph* sub = new subgraph(test_graph, test_graph1);
        subgraph* sub = new subgraph();
        assert(NULL != sub);
        sub->set_target_graphs(test_graph, test_graph1);
        if(sub->is_contain_subgraph()){
            std::cout << "In first graph contain isomorphic subgrah" << std::endl;
        } else {
            std::cout << "In first graph NOT isomorphic subgrah" << std::endl;
        }



    } catch (graph_exception& e) {
        std::cout << e.what() << "\n\n";	
        return 1;	
    }
return 0;
}

