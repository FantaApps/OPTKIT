/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of core decomposition utilities 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   09/02/16 - Creation
**/

#include <gtest/gtest.h>
#include <stdlib.h>
#include "dbscan.h"
#include "test_util.h" 
#include <stdlib.h>

using namespace std;

TEST(CheckInCluster_1, Success)
{
    CSR  g("../data/MC/janc.gr");
    DBSCAN c(g.get_num_v(), g.get_num_c());
    c.compute_deg(g);
    bool res = c.check_in_cluster(g, 4, 4);
    ASSERT_EQ(res, false);
    res = c.check_in_cluster(g, 4, 3);
    ASSERT_EQ(res, true);
}

TEST(CheckInCluster_2, Success)
{
    CSR  g("../data/MC/jwang.gr");
    DBSCAN c(g.get_num_v(), g.get_num_c());
    c.compute_deg(g);
    bool res = c.check_in_cluster(g, 10, 7);
    ASSERT_EQ(res, false);
    res = c.check_in_cluster(g, 2, 3);
    ASSERT_EQ(res, true);
}

TEST(DegVOprTest_3, Success)
{
    /* Some basic setup */
    CSR  g("../data/MC/janc.gr");
    Core *c = new DBSCAN(g.get_num_v(), g.get_num_c());

    c->compute_deg(g);
    bool ret = c->deg_v_opr(g, 4);

    ASSERT_EQ(ret, true);

    g.visualize();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/dbscan/csr_v_opr.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 

    c->print_deg();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/dbscan/deg_v_opr.txt", "./deg.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 


    std::remove("./deg.txt");
    std::remove("./csr.dot");
}

/**
 * @brief   test deg_e_opr 
**/
TEST(DegVOprTest_4, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Core *c = new DBSCAN(g.get_num_v(), g.get_num_c());

    c->compute_deg(g);
    bool ret = c->deg_v_opr(g, 7);

    ASSERT_EQ(ret, true);

    g.visualize();
    //ASSERT_EQ(g.get_num_e(), 84);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/dbscan/csr_e_opr1.dot", "./csr.dot"), 
            TstUtil::OPTKIT_TEST_PASS); 


    c->print_deg();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/dbscan/deg_v_opr1.txt", "./deg.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./deg.txt");
    std::remove("./csr.dot");
}

/**
 * @brief   test core decomposition 
**/
TEST(DBSCANTest_1, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/janc.gr");
    Core *c = new DBSCAN(g.get_num_v(), g.get_num_c());

    c->k_core(g, "core.txt", 5);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/dbscan/core_alg1.txt", "./core.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./core.txt");
}

/**
 * @brief   test core decomposition in J. Wang's paper example 
**/
TEST(DBSCANTest_2, Success)
{
    /* Some basic setup */
    CSR g("../data/MC/jwang.gr");
    Core *c = new DBSCAN(g.get_num_v(), g.get_num_c());

    c->k_core(g, "core.txt", 5);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/dbscan/jwang_core_alg1.txt", "./core.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 
    std::remove("./core.txt");
}
