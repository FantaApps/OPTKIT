/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of core decomposition utilities 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   09/01/16 - Creation
**/

#include <gtest/gtest.h>
#include <stdlib.h>
#include "core.h"
#include "test_util.h" 
#include <stdlib.h>

using namespace std;

/**
 * @brief   Test a small graph one color for janc graph
**/
TEST(InitCoreTest_1, Success)
{
    /* Some basic setup for janc graph*/
    CSR g("../data/MC/janc.gr");
    Core c(g.get_num_v(), g.get_num_c());

    /* Test some basic graph properties */
    ASSERT_EQ(c.get_num_c(), 1);
    ASSERT_EQ(c.get_num_v(), 8);

    c.print_deg();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/deg_init.txt", "./deg.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./deg.txt");
}

/**
 * @brief   Test a small graph one color for jwang graph
**/
TEST(InitCoreTest_2, Success)
{
    /* Some basic setup for jwang graph*/
    CSR g("../data/MC/jwang.gr");
    Core c(g.get_num_v(), g.get_num_c());

    /* Test some basic graph properties */
    ASSERT_EQ(c.get_num_c(), 1);
    ASSERT_EQ(c.get_num_v(), 21);

    c.print_deg();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/deg_init1.txt", "./deg.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./deg.txt");
}

/**
 * @brief   test compute_deg for janc graph 
**/
TEST(ComputeDegTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");
    Core c(g.get_num_v(), g.get_num_c());

    c.compute_deg(g);

    c.print_deg();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/deg_compt.txt", "./deg.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./deg.txt");
}

/**
 * @brief   test compute_deg for jwang graph 
**/
TEST(ComputeDegTest_2, Success)
{
    /* Some basic setup */
    CSR  g("../data/MC/jwang.gr");
    Core c(g.get_num_v(), g.get_num_c());

    c.compute_deg(g);

    c.print_deg();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/deg_compt1.txt", "./deg.txt"), 
              TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./deg.txt");
}

/**
 * @brief   test deg_e_opr 
**/
TEST(ReduceOneVTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");
    Core c(g.get_num_v(), g.get_num_c());

    c.compute_deg(g);
    c.reduce_one_vet(g, 0);

    c.print_deg();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/deg_reduce_v.txt", "./deg.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./deg.txt");
}

/**
 * @brief   test deg_e_opr 
**/
TEST(ReduceOneVTest_2, Success)
{
    /* Some basic setup */
    CSR  g("../data/MC/jwang.gr");
    Core c(g.get_num_v(), g.get_num_c());

    c.compute_deg(g);
    c.reduce_one_vet(g, 3);
    c.reduce_one_vet(g, 5);

    c.print_deg();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/deg_reduce_v1.txt", "./deg.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 


    std::remove("./deg.txt");
}


/**
 * @brief   test deg_v_opr 
**/
TEST(DegVOprTest_1, Success)
{
    /* Some basic setup */
    CSR  g("../data/MC/janc.gr");
    Core c(g.get_num_v(), g.get_num_c());

    c.compute_deg(g);
    bool ret = c.deg_v_opr(g, 3);

    ASSERT_EQ(ret, true);

    g.visualize();
    ASSERT_EQ(g.get_num_e(), 20);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/csr_v_opr.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 

    c.print_deg();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/deg_v_opr.txt", "./deg.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 


    std::remove("./deg.txt");
    std::remove("./csr.dot");
}

/**
 * @brief   test deg_e_opr 
**/
TEST(DegEOprTest_2, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Core c(g.get_num_v(), g.get_num_c());

    c.compute_deg(g);
    bool ret = c.deg_v_opr(g, 3);

    ASSERT_EQ(ret, true);

    g.visualize();
    //ASSERT_EQ(g.get_num_e(), 84);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/csr_e_opr1.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 


    c.print_deg();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/deg_v_opr1.txt", "./deg.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./deg.txt");
    std::remove("./csr.dot");
}

/**
 * @brief   test core decomposition 
**/
TEST(CoreDecompositionTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");
    Core c(g.get_num_v(), g.get_num_c());

    c.k_core(g, "core.txt", 5);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/core_alg1.txt", "./core.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./core.txt");
}

/**
 * @brief   test core decomposition in J. Wang's paper example 
**/
TEST(CoreDecompositionTest_2, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Core c(g.get_num_v(), g.get_num_c());

    c.k_core(g, "core.txt", 5);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/core/jwang_core_alg1.txt", "./core.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 
    std::remove("./core.txt");
}
