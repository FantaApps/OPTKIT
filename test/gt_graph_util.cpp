/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 *  @brief    Unittest of graph utilies.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/10/15 - Add validation code Success.
 *  stplaydog   08/09/15 - Creation
**/

#include <gtest/gtest.h>
#include "graph_util.h"
#include "utils.h"

#include <boost/config.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

TEST(InitGraphTest, Success)
{
    /* Some basic setup */
    char file[OPTKIT_FILE_SIZE];
    snprintf(file, OPTKIT_FILE_SIZE, "%s", 
            "../data/CC/graphs/crimepair_0");
    Graph g;
    GraphUtils::init_graph(file, g);

    /* Test some basic graph properties */
    ASSERT_EQ(num_edges(g), 903);
}

