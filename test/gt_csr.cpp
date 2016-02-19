/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of CSR graph structure. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/13/16 - validate making graph from edge list
 *                         also have vertex mappings 
 *  stplaydog   01/10/16 - Validate all results in janc graph  
 *  stplaydog   12/15/15 - simplified the test procedure 
 *  stplaydog   12/13/15 - Finished OutputAllCCTest_1, ReconstructTest_1, 
 *                         ComputeNumEdgeIntersectTest_1, InitGraphTest_1 
 *  stplaydog   12/10/15 - Creation
**/

#include <gtest/gtest.h>
#include "csr.h"
#include "test_util.h" 


/**
 * @brief   Test a small graph one color
 *
**/
TEST(InitGraphTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");

    /* Test some basic graph properties */
    ASSERT_EQ(g.get_num_v(), 8);
    ASSERT_EQ(g.get_num_e(), 26);
    ASSERT_EQ(g.get_num_c(), 1);

    /* Test the content of the graph */
    g.visualize();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/CSR/csr.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./csr.dot");
}


/**
 * @brief   Test a small graph using edge list and with vertex mapping 
 *
**/
TEST(InitGraphTest_2, Success)
{
    // test one graph
    vector<pair<int32_t, int32_t>> edges1 = TstUtil::read_edge_list("../data/MC/janc.gr");
    CSR g1(edges1);

    ASSERT_EQ(g1.get_num_v(), 8);
    ASSERT_EQ(g1.get_num_e(), 26);
    ASSERT_EQ(g1.get_num_c(), 1);

    g1.visualize();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/CSR/csr.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./csr.dot");

    // test another graph
    vector<pair<int32_t, int32_t>> edges2 = TstUtil::read_edge_list("../data/MC/janc_origin.gr");
    CSR g2(edges2);

    /* Test some basic graph properties */
    ASSERT_EQ(g2.get_num_v(), 8);
    ASSERT_EQ(g2.get_num_e(), 26);
    ASSERT_EQ(g2.get_num_c(), 1);

    /* Test the content of the graph */
    g2.visualize();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/CSR/csr.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./csr.dot");
}

/**
 * @brief   Test a little bigger graph J. Wang 
 *
**/
TEST(InitGraphTest_3, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");

    /* Test some basic graph properties */
    ASSERT_EQ(g.get_num_v(), 21);
    ASSERT_EQ(g.get_num_e(), 90);
    ASSERT_EQ(g.get_num_c(), 1);

    /* Test the content of the graph */
    g.visualize();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/CSR/csr1.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./csr.dot");
}


/**
 * @brief   test compute_num_edge_intersect for janc graph
 *
**/
TEST(ComputeNumEdgeIntersectTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");

    TstUtil::compute_num_edge_intersect(g);

    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/CSR/intersect.txt", 
                "./intersect.txt"), TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./intersect.txt");
}

/**
 * @brief   test compute_num_edge_intersect for jwang graph
 *
**/
TEST(ComputeNumEdgeIntersectTest_2, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");

    TstUtil::compute_num_edge_intersect(g);

    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/CSR/intersect1.txt", 
                "./intersect.txt"), TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./intersect.txt");
}

/**
 * @brief   test reconstruct, using janc graph
 *          we removed three edges in the graph and
 *          see if the reconstruction goes well or not.  
 *
**/
TEST(ReconstructTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");

    ASSERT_EQ(g.remove_e(0, 6), true);
    ASSERT_EQ(g.remove_e(3, 7), true);
    ASSERT_EQ(g.remove_e(2, 5), true);
    ASSERT_EQ(g.remove_e(2, 5), false);

    g.reconstruct();

    ASSERT_EQ(g.get_num_e(), 20);

    g.visualize();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/CSR/csr_reconstruct.dot", 
                "./csr.dot"), TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./csr.dot");
}

/**
 * @brief   test output_all_CC 
 *
**/
TEST(OutputAllCCTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");

    ASSERT_EQ(g.remove_e(0, 3), true);
    ASSERT_EQ(g.remove_e(0, 6), true);
    ASSERT_EQ(g.remove_e(1, 4), true);
    ASSERT_EQ(g.remove_e(1, 6), true);
    ASSERT_EQ(g.remove_e(2, 5), true);
    ASSERT_EQ(g.remove_e(2, 6), true);

    g.reconstruct();
    ASSERT_EQ(g.get_num_e(), 14);

    FILE *writer = fopen("CC.txt", "w");
    g.output_all_CC(writer);
    fclose(writer);

    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/CSR/CC.txt", 
                "./CC.txt"), TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./CC.txt");
}

/**
 * @brief   test reconstruct, using jwang graph
 *          we removed 9 edges in the graph and
 *          see if the reconstruction goes well or not.  
 *          At the end, we output CCs. 
 *
**/
TEST(ReconstructTest_2, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");

    ASSERT_EQ(g.remove_e(3, 7),   true);
    ASSERT_EQ(g.remove_e(3, 9),   true);
    ASSERT_EQ(g.remove_e(3, 17),  true);
    ASSERT_EQ(g.remove_e(0, 3),   true);

    ASSERT_EQ(g.remove_e(2, 20),  true);
    ASSERT_EQ(g.remove_e(7, 20),  true);
    ASSERT_EQ(g.remove_e(19, 20), true);
    ASSERT_EQ(g.remove_e(17, 20), true);

    ASSERT_EQ(g.remove_e(13, 17), true);

    g.reconstruct();

    ASSERT_EQ(g.get_num_e(), 72);

    g.visualize();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/CSR/csr_reconstruct1.dot", 
                "./csr.dot"), TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./csr.dot");

    FILE *writer = fopen("CC.txt", "w");
    g.output_all_CC(writer);
    fclose(writer);

    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/CSR/CC1.txt", 
                "./CC.txt"), TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./CC.txt");
}
