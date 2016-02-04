/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    Declaration of graph utility functions. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/07/15 - Creation
 *
**/

#pragma once
#ifndef _H_GRAPH_UTILS
#define _H_GRAPH_UTILS

#include "utils.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/bron_kerbosch_all_cliques.hpp>
#include <boost/graph/undirected_graph.hpp>

using namespace boost;

typedef adjacency_list <vecS, vecS, undirectedS> Adj;
typedef boost::undirected_graph<boost::no_property> Udi;

/**
 * @class   GraphUtils
 *
 * @brief   A set of functions to copmute different graph properties.
**/
class GraphUtils 
{
    // The clique_printer is a visitor that will print the vertices that comprise
    // a clique. Note that the vertices are not given in any specific order.
    template <typename OutputStream>
        struct clique_printer
        {
            clique_printer(OutputStream& stream)
                : os(stream)
            { }

            template <typename Clique, typename Graph>
                void clique(const Clique& c, const Graph& g)
                {
                    // Iterate over the clique and print each vertex within it.
                    typename Clique::const_iterator i, end = c.end();
                    //for(i = c.begin(); i != end; ++i) {
                    //    os << g[*i].name << " ";
                    //}
                    os << endl;
                }
            OutputStream& os;
        };

    public:
    static void init_adj(const char* file, Adj& g);
    static void init_udi(const char* file, Udi& g);
    static void connected_comps(const char* file, const char* output_dir);
    static void all_cliques(const char* file, const char* output_dir);
    static void adjacency_list_to_file(const char* file);
    static void k_truss(const char* file, const char* output_dir);
};

#endif
