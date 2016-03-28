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
#include "STModel.h"
#include "CrimeSTModel.h" 
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

/**
 * @brief   Test a small graph one color for janc graph
**/
TEST(BGLGraphProperty_1, Success)
{
    BGL g("../data/MC/janc.gr");

    Stats::instance()->m_application = "stmodel";    

    g.floyd_warshall();
    g.clustering_coeff();
    g.betweeness_centrality();
    g.all_cliques();

    ASSERT_EQ(Stats::instance()->get_content(Stats::DIAMETER), "3");
    ASSERT_EQ(Stats::instance()->get_content(Stats::CLUSTERCOEFF), "0.311508");
    ASSERT_EQ(Stats::instance()->get_content(Stats::BETWEENCENTRL), 
            "2.166667,3.500000,0.333333,4.833333,1.000000,0.666667,4.000000,1.500000");
    ASSERT_EQ(Stats::instance()->get_content(Stats::CLIQUE), 
            "2,3\n3,5");
}

/**
 * @brief   Test a small graph one color for janc graph
**/
TEST(BGLInitGraph_2, Success)
{
    BGL g("../data/MC/jwang.gr");
    ofstream writer ("bgl_jwang.dot");
    g.print_dependencies<Adj>(writer,  g.m_adj);
    g.print_dependencies<Adj1>(writer, g.m_adj1);
    g.print_udependencies<Udir>(writer, g.m_udir);
    writer.close();

    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/bgl/bgl_jwang.dot", "./bgl_jwang.dot"),
              TstUtil::OPTKIT_TEST_PASS);

    std::remove("./bgl_jwang.dot");
}

/**
 * @brief   Test a small graph one color for janc graph
**/
TEST(BGLGraphProperty_2, Success)
{
    BGL g("../data/MC/jwang.gr");

    Stats::instance()->m_application = "stmodel";    

    g.floyd_warshall();
    g.clustering_coeff();
    g.betweeness_centrality();
    g.all_cliques();

    ASSERT_EQ(Stats::instance()->get_content(Stats::DIAMETER), "3");
    ASSERT_EQ(Stats::instance()->get_content(Stats::CLUSTERCOEFF), "0.447373");
    ASSERT_EQ(Stats::instance()->get_content(Stats::BETWEENCENTRL), 
            "2.166667,3.500000,0.333333,4.833333,1.000000,0.666667,4.000000,1.500000,0.533333,0.000000,0.900000,9.433333,1.000000,0.000000,26.266667,0.900000,0.000000,9.233333,0.000000,0.000000,0.000000,0.000000,1.000000,0.333333,2.700000,97.300000,0.333333,2.033333,57.033333");
    ASSERT_EQ(Stats::instance()->get_content(Stats::CLIQUE), 
            "2,3\n3,5\n2,3\n3,12\n4,5");
}

/**
 * Analyze shootings in Philadelphia and find 
 * an elevated risk of near-repeat shootings 
 * occurring within 2 weeks and within one city 
 * block of previous incidents
 *
 * 100 meter, 200 meter, 400 meter
**/

TEST(BGLSTModel_1, Success)
{
    string input_file = "../data/truss/ny_crime.csv"; 
    CrimeSTModel stm(input_file);
}
