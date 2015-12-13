/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 *  @brief    Unittest of CSR graph structure. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   12/10/15 - Creation
**/

#include <gtest/gtest.h>
#include "csr.h"
#include "test_util.h" 

/**
 * @brief   Test the allocate_data_structure 
 *
**/
TEST(AllocateDataStructureTest_1, Success)
{
}

/**
 * @brief   Test a small graph one color
 *
**/
TEST(InitGraphTest_1, Success)
{
    /* Some basic setup */
    char file[OPTKIT_FILE_SIZE];
    snprintf(file, OPTKIT_FILE_SIZE, "%s", 
            "../data/MC/janc.gr");
    CSR g(file);

    /* Test some basic graph properties */
    ASSERT_EQ(g.get_num_v(), 8);
    ASSERT_EQ(g.get_num_e(), 1);
    ASSERT_EQ(g.get_num_c(), 26);

    /* Test the content of the graph */
    g.visualize();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/MC/csr.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 
}

/**
 * @brief   Test a small graph multiple color, equal size of each color
 *
**/
TEST(InitGraphTest_2, Success)
{
}

/**
 * @brief   Test a small graph multiple color, varied size of each color
 *
**/
TEST(InitGraphTest_3, Success)
{
}

/**
 * @brief   Test a large graph one color
 *
**/
TEST(InitGraphTest_4, Success)
{
    /* Some basic setup */
    char file[OPTKIT_FILE_SIZE];
    snprintf(file, OPTKIT_FILE_SIZE, "%s", 
            "../data/CC/graphs/crimepair_0");
    CSR g(file);

    /* Test some basic graph properties */
    ASSERT_EQ(g.get_num_v(), 903);
    ASSERT_EQ(g.get_num_e(), 903);
    ASSERT_EQ(g.get_num_c(), 903);

    /* Test the content of the graph */
}

/**
 * @brief   Test a large graph multiple color, equal size of each color
 *
**/
TEST(InitGraphTest_5, Success)
{
}

/**
 * @brief   Test a large graph multiple color, varied size of each color
 *
**/
TEST(InitGraphTest_6, Success)
{
}

/**
 * @brief   Negative initialization tests.
 *
**/
TEST(InitGraphTest_7, Success)
{
}

/**
 * @brief   test compute_num_edge_intersect
 *
**/
TEST(ComputeNumEdgeIntersectTest_1, Success)
{
}

/**
 * @brief   test reconstruct  
 *
**/
TEST(ReconstructTest_1, Success)
{
}

/**
 * @brief   test output_all_CC 
 *
**/
TEST(OutputAllCCTest_1, Success)
{
}
