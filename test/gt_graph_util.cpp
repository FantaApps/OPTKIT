/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 *  @brief    Unittest of graph utilies.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/09/15 - Creation
**/

#include <gtest/gtest.h>
#include "graph_util.h"
#include "utils.h"

using namespace boost;

TEST(InitGraphTest, Success)
{
    /* Some basic setup */
    char file[OPTKIT_FILE_SIZE];
    snprintf(file, OPTKIT_FILE_SIZE, "%s", 
            "/Users/zhaomingyin/gitlocal/OPTKIT/data/CC/graphs/crimepair_0");
    Graph g;
    GraphUtils::init_graph(file, g);

    /* Test some basic graph properties */
}

