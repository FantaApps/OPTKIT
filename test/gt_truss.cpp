/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 *  @brief    Unittest of truss decomposition utilities 
 *
 *  MODIFIED   (MM/DD/YY)
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
    /* Some basic setup */
    char file[OPTKIT_FILE_SIZE];
    snprintf(file, OPTKIT_FILE_SIZE, "%s", 
            "../data/MC/janc.gr");
    CSR g(file);
    Truss t(g.get_num_e(), g.get_num_c());

    /* Test some basic graph properties */
    ASSERT_EQ(t.get_num_c(), 1);
    ASSERT_EQ(t.get_num_e(), 26);

    t.print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/MC/sup_init.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 
}

/**
 * @brief   test compute_sup  
 *
**/
TEST(ComputeSupTest_1, Success)
{
    /* Some basic setup */
    char file[OPTKIT_FILE_SIZE];
    snprintf(file, OPTKIT_FILE_SIZE, "%s", 
            "../data/MC/janc.gr");
    CSR g(file);
    Truss t(g.get_num_e(), g.get_num_c());

    t.compute_sup(g);

    t.print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/MC/sup_compt.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 
}

/**
 * @brief   test sup_e_opr 
 *
**/
TEST(SupEOprTest_1, Success)
{
}

/**
 * @brief   test reduce_one_edge  
 *
**/
TEST(TrussDecompositionTest_1, Success)
{
}
