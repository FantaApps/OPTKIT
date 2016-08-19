/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of truss decomposition utilities 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/19/16 - passes all test cases 
 *  stplaydog   02/17/16 - add test cases for jwang graph 
 *  stplaydog   02/14/16 - add TrussDecompositionTest_2 to test case in J Wang's paper.
 *  stplaydog   01/10/16 - Validate all results in janc graph  
 *  stplaydog   01/04/16 - Fixed some bugs 
 *  stplaydog   12/15/15 - simplified the test procedure 
 *  stplaydog   12/14/15 - Add InitTrussTest_1, ComputeSupTest_1,
 *                         SupEOprTest_1, TrussDecompositionTest_1. 
 *  stplaydog   12/14/15 - Creation
**/

#include <gtest/gtest.h>
#include <stdlib.h>
#include "truss.h"
#include "truss_plus.h"
#include "test_util.h" 
#include <stdlib.h>

using namespace std;
using boost::archive::text_oarchive;
using boost::archive::text_iarchive;
using boost::archive::archive_exception;

/**
 * @brief   Test a small graph one color for janc graph
**/
TEST(InitTrussTest_1, Success)
{
    /* Some basic setup for janc graph*/
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
 * @brief   Test a small graph one color for jwang graph
**/
TEST(InitTrussTest_2, Success)
{
    /* Some basic setup for jwang graph*/
    CSR g("../data/MC/jwang.gr");
    Truss t(g.get_num_e(), g.get_num_c());

    /* Test some basic graph properties */
    ASSERT_EQ(t.get_num_c(), 1);
    ASSERT_EQ(t.get_num_e(), 90);

    t.print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_init1.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./sup.txt");
}

/**
 * @brief   test compute_sup for janc graph 
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
 * @brief   test compute_sup for jwang graph 
**/
TEST(ComputeSupTest_2, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Truss t(g.get_num_e(), g.get_num_c());

    t.compute_sup(g);

    t.print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_compt1.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./sup.txt");
}

/**
 * @brief   test sup_e_opr 
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
**/
TEST(ReduceOneETest_2, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Truss t(g.get_num_e(), g.get_num_c());

    t.compute_sup(g);
    t.reduce_one_edge(g, 0, 3);

    t.print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_reduce_e1.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 


    std::remove("./sup.txt");
}

/**
 * @brief   test sup_e_opr 
**/
TEST(ReduceOneETest_3, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Truss *t = new TrussPlus();

    t->compute_sup(g);
    t->reduce_one_edge(g, 0, 3);

    t->print_sup();
    system("diff ./sup.txt ../QA/unittest/truss/sup_reduce_e2.txt");
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_reduce_e2.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./sup.txt");
}

/**
 * @brief   test sup_e_opr 
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
 * @brief   test sup_e_opr 
**/
TEST(SupEOprTest_2, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Truss t(g.get_num_e(), g.get_num_c());

    t.compute_sup(g);
    bool ret = t.sup_e_opr(g, 3);

    ASSERT_EQ(ret, true);

    g.visualize();
    ASSERT_EQ(g.get_num_e(), 84);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/csr_e_opr1.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 


    t.print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_e_opr1.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./sup.txt");
    std::remove("./csr.dot");
}

/**
 * @brief   test sup_e_opr 
**/
TEST(SupEOprTest_3, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Truss *t = new TrussPlus();

    t->compute_sup(g);

    bool ret = t->sup_e_opr(g, 3);
    ASSERT_EQ(ret, false);
    g.visualize();
    t->print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/csr_e_opr1.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_e_opr2.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    ret = t->sup_e_opr(g, 4);
    ASSERT_EQ(ret, false);
    g.visualize();
    t->print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/csr_e_opr2.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_e_opr3.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    ret = t->sup_e_opr(g, 5);
    ASSERT_EQ(ret, false);
    g.visualize();
    t->print_sup();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/csr_e_opr3.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/sup_e_opr4.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./sup.txt");
    std::remove("./csr.dot");
}

/**
 * @brief   test truss decomposition 
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

/**
 * @brief   test truss decomposition in J. Wang's paper example 
**/
TEST(TrussDecompositionTest_2, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Truss t(g.get_num_e(), g.get_num_c());

    t.truss_decomosition(g, "truss.txt", 5);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/jwang_truss_alg1.txt", "./truss.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 
    std::remove("./truss.txt");
}

/**
 * @brief   test truss decomposition in J. Wang's paper example 
 *          using enhanced truss decomposition algo
**/
TEST(TrussDecompositionTest_3, Success)
{
    /* Some basic setup */
    //CSR g("../data/MC/jwang.gr");
    //Truss t(g.get_num_e(), g.get_num_c());
    //Config::instance()->set(string("truss_algo"), string("algo2"));

    //T.truss_decomosition(g, "truss.txt", 5);
    //ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/jwang_truss_alg1.txt", "./truss.txt"), 
    //        TstUtil::OPTKIT_TEST_PASS); 
    //Exit(1);
    //Std::remove("./truss.txt");
}

/**
 * @brief   test truss decomposition in J. Wang's paper example 
**/
TEST(BuildSortedSupETest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Truss *t = new TrussPlus();
    t->compute_sup(g);

    t->print_sup();

    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/truss/build_sort_sup_e.txt", "./sup.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("sup.txt");
}
