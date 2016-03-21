/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of graph utilies.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/20/16 - When compiling boost::graphviz with gtest, 
 *                         there will be shared_ptr issues, we addressed this isue
 *                         by printing edges.
 *  stplaydog   03/16/16 - Add boost graph test code.
 *  stplaydog   08/10/15 - Add validation code Success.
 *  stplaydog   08/09/15 - Creation
**/

#include <gtest/gtest.h>
#include "bgl.h"
#include "test_util.h" 

using namespace boost;


/**
 * @brief   Test a small graph one color for janc graph
**/
TEST(BGLInitGraph_1, Success)
{
    BGL g("../data/MC/janc.gr");
    ofstream writer ("bgl_janc.dot");
    g.print_dependencies<Adj>(writer,  g.m_adj);
    g.print_dependencies<Adj1>(writer, g.m_adj1);
    g.print_udependencies<Udir>(writer, g.m_udir);
    writer.close();

    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/bgl/bgl_janc.dot", "./bgl_janc.dot"),
              TstUtil::OPTKIT_TEST_PASS);

    std::remove("./bgl_janc.dot");
}

