/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of graph utilies.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/16/16 - Add boost graph test code.
 *  stplaydog   08/10/15 - Add validation code Success.
 *  stplaydog   08/09/15 - Creation
**/

#include "bgl.h"
#include "test_util.h" 
#include <boost/graph/graphviz.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost;

/**
 * @brief   Test a small graph one color for janc graph
**/
BOOST_AUTO_TEST_CASE(BGLInitGraph_1)
{
    //BGL g("../data/MC/janc.gr");
    //ofstream writer ("bgl_janc.dot");
    //write_graphviz(writer, g.get_adj());
    //write_graphviz(writer, g.get_adj1());
    //write_graphviz(writer, g.get_udir());
    //writer.close();

    //BOOST_CHECK(TstUtil::compareFile("../QA/unittest/bgl/bgl_janc.dot", "./bgl_janc.dot") ==
    //          TstUtil::OPTKIT_TEST_PASS);

    //std::remove("./bgl_janc.dot");
}

