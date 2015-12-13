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

using namespace boost;

TEST(InitGraphTest, Success)
{
    /* Some basic setup */
    char file[OPTKIT_FILE_SIZE];
    snprintf(file, OPTKIT_FILE_SIZE, "%s", 
            "../data/CC/graphs/crimepair_0");
    Adj g;
    GraphUtils::init_adj(file, g);

    /* Test some basic graph properties */
    ASSERT_EQ(num_edges(g), 903);
}

TEST(ConnectedCompTest, Success)
{
    // This can be an ofstream as well or any other ostream
    std::stringstream buffer;

    // Save cout's buffer here
    std::streambuf *sbuf = std::cout.rdbuf();

    // Redirect cout to our stringstream buffer or any other ostream
    std::cout.rdbuf(buffer.rdbuf());


    // When done redirect cout to its old self
    std::cout.rdbuf(sbuf);


    /* Some basic setup */
    // char file[OPTKIT_FILE_SIZE];
    // snprintf(file, OPTKIT_FILE_SIZE, "%s", 
    //        "../data/CC/graphs/crimepair_0");
    // GraphUtils::connected_comps(file, "aaa");

    // snprintf(file, OPTKIT_FILE_SIZE, "%s",
    //        "../QA/testcase/rfc_logs/crimepair_0.log");
    //std::ifstream t(file);
    //std::stringstream buffer1;
    //buffer1 << t.rdbuf();
}

