/**
 * Copy right YMSys, 2015, Zhaoming Yin
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

using namespace boost;

typedef adjacency_list <vecS, vecS, undirectedS> Graph;

/**
 * @class   GraphUtils
 *
 * @brief   A set of functions to copmute different graph properties.
**/
class GraphUtils 
{
public:
    static void init_graph(const char* file, Graph& g);
    static void connected_comps(const char* file, const char* output_dir);
    static void adjacency_list_to_file(const char* file);
    static void k_truss(const char* file, const char* output_dir);
};

#endif
