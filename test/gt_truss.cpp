/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of truss decomposition utilities 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   01/10/16 - Validate all results in janc graph  
 *  stplaydog   01/04/16 - Fixed some bugs 
 *  stplaydog   12/15/15 - simplified the test procedure 
 *  stplaydog   12/14/15 - Add InitTrussTest_1, ComputeSupTest_1,
 *                         SupEOprTest_1, TrussDecompositionTest_1. 
 *  stplaydog   12/14/15 - Creation
**/

#include <gtest/gtest.h>
#include "truss.h"
#include "test_util.h" 

/**
 * @brief   Test a small graph one color
 *
**/
TEST(InitTrussTest_1, Success)
{
    google::InitGoogleLogging("OPTKIT_TEST");

    /* Some basic setup */
    CSR g("../data/MC/janc.gr");
    Truss t(g.get_num_e(), g.get_num_c());

    /* Test some basic graph properties */
    ASSERT_EQ(t.get_num_c(), 1);
    ASSERT_EQ(t.get_num_e(), 26);

    t.print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_init.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./sup.txt");
}

/**
 * @brief   test compute_sup  
 *
**/
TEST(ComputeSupTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");
    Truss t(g.get_num_e(), g.get_num_c());

    t.compute_sup(g);

    t.print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_compt.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./sup.txt");
}

/**
 * @brief   test sup_e_opr 
 *
**/
TEST(ReduceOneETest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");
    Truss t(g.get_num_e(), g.get_num_c());

    t.compute_sup(g);
    t.reduce_one_edge(g, 0, 1);

    t.print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_reduce_e.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./sup.txt");
}

/**
 * @brief   test sup_e_opr 
 *
**/
TEST(SupEOprTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");
    Truss t(g.get_num_e(), g.get_num_c());

    t.compute_sup(g);
    bool ret = t.sup_e_opr(g, 3);

    ASSERT_EQ(ret, true);

    g.visualize();
    ASSERT_EQ(g.get_num_e(), 20);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/csr_e_opr.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 

    t.print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_e_opr.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./sup.txt");
    std::remove("./csr.dot");
}

/**
 * @brief   test truss decomposition 
 *
**/
TEST(TrussDecompositionTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");
    Truss t(g.get_num_e(), g.get_num_c());

    t.truss_decomosition(g, "truss.txt", 5);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/truss_alg1.txt", "./truss.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./truss.txt");
}
