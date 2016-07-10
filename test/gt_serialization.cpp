/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of CSR graph structure. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   07/03/16 - Creation
**/

#include <../src/Config.h>
#include <../src/Stats.h>
#include <gtest/gtest.h>
#include <fstream>

using namespace std;
using boost::archive::text_oarchive;
using boost::archive::text_iarchive;
using boost::archive::archive_exception;

/**
 * @brief   Test a small graph one color
 *
**/
TEST(ConfigSerializationTest_1, Success)
{
    Config::instance()->clear();

    {
        ofstream ofs("./filename");
        text_oarchive oa(ofs);
        string key = "key1";
        string val = "val1";
        Config::instance()->set(key, val);

        key = "key2";
        val = "val2";
        Config::instance()->set(key, val);

        oa<<*Config::instance();

        Config::instance()->clear();
    }

    {
        ifstream ifs("./filename");
        text_iarchive ia(ifs);
        ia>>*Config::instance();

        string key = "key1";
        ASSERT_EQ(Config::instance()->get(key) == "val1", true);
        key = "key2";
        ASSERT_EQ(Config::instance()->get(key) == "val2", true);
    }

    std::remove("./filename");
}

/**
 * @brief   Test a small graph one color
 *
**/
TEST(StatsSerializationTest_1, Success)
{
    Stats::instance()->clear();

    {
        ofstream ofs("./filename");
        text_oarchive oa(ofs);
        Stats::instance()->m_application = "stmodel";
        Stats::instance()->m_outFile     = "file1";
        Stats::instance()->m_time        = "time1";
        Stats::instance()->m_dataName    = "dataName1";
        Stats::instance()->m_range       = {1, 2, 3};
        Stats::instance()->m_gProperty.m_numCC         = 1234;
        Stats::instance()->m_gProperty.m_numV          = {1, 2, 3, 4, 5, 6};
        Stats::instance()->m_gProperty.m_numE          = {1, 2, 3, 4, 5, 6};
        Stats::instance()->m_gProperty.m_diameter      = {1, 2, 3, 4, 5, 6};
        Stats::instance()->m_gProperty.m_girth         = {1, 2, 3, 4, 5, 6};
        Stats::instance()->m_gProperty.m_clusterCoeff  = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
        Stats::instance()->m_gProperty.m_betweenCentrl = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
        Stats::instance()->m_gProperty.m_numTruss      = {{{1,2}, {3,4}},{{5,6},{7,8}}};
        Stats::instance()->m_gProperty.m_numClique     = {{{1,2}, {3,4}},{{5,6},{7,8}}};

        oa<<*Stats::instance();

        Stats::instance()->clear();
    }

    {
        ifstream ifs("./filename");
        text_iarchive ia(ifs);
        ia>>*Stats::instance();

        ASSERT_EQ((Stats::instance()->m_application               == "stmodel"),                          true);
        ASSERT_EQ((Stats::instance()->m_outFile                   == "file1"),                            true);
        ASSERT_EQ((Stats::instance()->m_time                      == "time1"),                            true);
        ASSERT_EQ((Stats::instance()->m_dataName                  == "dataName1"),                        true);
        ASSERT_EQ((Stats::instance()->m_range                     == {1, 2, 3}),                          true);
        ASSERT_EQ((Stats::instance()->m_gProperty.m_numCC         == 1234),                               true);
        ASSERT_EQ((Stats::instance()->m_gProperty.m_numV          == {1, 2, 3, 4, 5, 6}),                 true);
        ASSERT_EQ((Stats::instance()->m_gProperty.m_numE          == {1, 2, 3, 4, 5, 6}),                 true);
        ASSERT_EQ((Stats::instance()->m_gProperty.m_diameter      == {1, 2, 3, 4, 5, 6}),                 true);
        ASSERT_EQ((Stats::instance()->m_gProperty.m_girth         == {1, 2, 3, 4, 5, 6}),                 true);
        ASSERT_EQ((Stats::instance()->m_gProperty.m_clusterCoeff  == {1.0, 2.0, 3.0, 4.0, 5.0, 6.0}),     true);
        ASSERT_EQ((Stats::instance()->m_gProperty.m_betweenCentrl == {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}}), true);
        ASSERT_EQ((Stats::instance()->m_gProperty.m_numTruss      == {{{1,2}, {3,4}},{{5,6},{7,8}}}),     true);
        ASSERT_EQ((Stats::instance()->m_gProperty.m_numClique     == {{{1,2}, {3,4}},{{5,6},{7,8}}}),     true);
    }

    std::remove("./filename");
}

/**
 * @brief   Test a small graph one color
 *
**/
TEST(CrimeSTModelSerializationTest_1, Success)
{
    string input_file = "../data/truss/ny_crime.csv"; 
    CrimeSTModel stm(input_file);

    {
        ofstream ofs("./filename");
        text_oarchive oa(ofs);
        oa<<stm;
    }

    {
        CrimeSTModel stm1();
        ifstream ifs("./filename");
        text_iarchive ia(ifs);
        ia>>stm1;
        ASSERT_EQ
    }
}

/**
 * @brief   Test a small graph one color
 *
**/
TEST(EdgeListSerializationTest_1, Success)
{
}
