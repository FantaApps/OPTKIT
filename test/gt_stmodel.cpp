/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of CSR graph structure. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/08/16 - add code to test STModelStats 
 *  stplaydog   03/03/16 - move test case to new directories 
 *                         add the truss test for ny crime data.
 *  stplaydog   02/10/16 - test build_edges 
 *  stplaydog   02/10/16 - test model creation and RTree creation 
 *  stplaydog   02/01/16 - Creation
**/

#include <gtest/gtest.h>
#include "STModel.h"
#include "CrimeSTModel.h" 
#include "test_util.h" 
#include "csr.h"
#include "truss.h"
#include "Stats.h"

using namespace std;

/**
 * @brief   Test a small graph one color
 *
**/
TEST(SmallCrimeDataTest_1, Success)
{
    google::InitGoogleLogging("OPTKIT_TEST");

    string input_file = "../data/truss/crime_small_st.csv"; 
    CrimeSTModel stm(input_file);

    int min[3] = {0,0,1};
    int max[3] = {1,1,1};
    int max1[3] = {2,2,1};
    int max2[3] = {2,2,2};
    int max3[3] = {2,2,3};
    
    ASSERT_EQ(stm.query_cont(min, max), 4);
    ASSERT_EQ(stm.query_cont(min, max1), 9);
    ASSERT_EQ(stm.query_cont(min, max2), 18);
    ASSERT_EQ(stm.query_cont(min, max3), 27);

    vector<int32_t> v = stm.query_list(min, max);
    sort(v.begin(), v.end());
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(v[1], 1);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);

    vector<pair<int32_t, int32_t>> edges = stm.build_edges(1, 1, 1);
    stm.serialize_edges(edges);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/stmodel/small_crime_edges.txt", "./crime_edges.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 
    std::remove("./crime_edges.txt");
    
    stm.serialize();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/stmodel/small_crime_st.txt", "./crime_data.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 
    std::remove("./crime_data.txt");

    // now test graph generation and truss decomposition
    CSR g(edges);

    Truss t(g.get_num_e(), g.get_num_c());

    t.truss_decomosition(g, "truss.txt", 5);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/stmodel/small_crime_truss_alg1.txt", "./truss.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./truss.txt");
}

/**
 * @brief   Test building graph from edge list, and test vertex mapping 
 *
**/
TEST(NYCrimeDataTest_1, Success)
{
    string input_file = "../data/truss/ny_crime.csv"; 
    CrimeSTModel stm(input_file);

    vector<pair<int32_t, int32_t>> edges = stm.build_edges(1, 1, 1);
    stm.serialize_edges(edges);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/stmodel/ny_crime_edges.txt", "./crime_edges.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 
    std::remove("./crime_edges.txt");
    
    stm.serialize();
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/stmodel/ny_crime_st.txt", "./crime_data.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 
    std::remove("./crime_data.txt");

    // now test graph generation and truss decomposition
    CSR g(edges);

    Truss t(g.get_num_e(), g.get_num_c());

    t.truss_decomosition(g, "truss.txt", 5);
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/stmodel/ny_crime_truss_alg1.txt", "./truss.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    // also do some real data validation
    stm.interpret_CC("./truss.txt", "./truss_stmodel.txt");
    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/stmodel/ny_crime_truss_stmodel.txt", "./truss_stmodel.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./truss.txt");
    std::remove("./truss_stmodel.txt");
}

/**
 * @brief   Test stats to serilize to json file 
 *
**/
TEST(StatsTest_1, Success)
{
    Stats *st = new Stats(string("./stats.txt"));
    
    st->m_application = "stmodel";    

    string tmp = "1,1,1"; st->write_content((int32_t)Stats::RANGE,         tmp);
    tmp = "gtest";        st->write_content((int32_t)Stats::DATANAME,      tmp); 
    tmp = "10";           st->write_content((int32_t)Stats::NUMV,          tmp);
    tmp = "1000";         st->write_content((int32_t)Stats::NUME,          tmp);
    tmp = "5";            st->write_content((int32_t)Stats::NUMCC,         tmp);
    tmp = "3";            st->write_content((int32_t)Stats::DIAMETER,      tmp);
    tmp = "25";           st->write_content((int32_t)Stats::GIRTH,         tmp);
    tmp = "0.58";         st->write_content((int32_t)Stats::CLUSTERCOEFF,  tmp);
    tmp = "0.33";         st->write_content((int32_t)Stats::BETWEENCENTRL, tmp);
    tmp = "3,25";         st->write_content((int32_t)Stats::TRUSS,         tmp);

    st->serialize();

    ASSERT_EQ(TstUtil::compareFile("../QA/unittest/stmodel/simple_stats.txt", "./stats.txt"), 
            TstUtil::OPTKIT_TEST_PASS); 

    std::remove("./stats.txt");
}

