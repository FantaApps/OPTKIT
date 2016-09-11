/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for keeping the program running stats
 *           The result could be serialized to a json file.  
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/08/16 - Add serialization 
 *  stplaydog   03/06/16 - Creation
 *
**/

#pragma once
#ifndef __H_STATS__
#define __H_STATS__

#include <fstream>
#include "utils.h"
#include "Config.h"
#include "gtest/gtest_prod.h"
#include <json_spirit/json_spirit.h>
#include <boost/serialization/vector.hpp>


using namespace std;

typedef vector<int32_t>                         int_feature_l;
typedef vector<double>                          double_feature_l;
typedef vector<double_feature_l>                double_feature_ll;
typedef vector<pair<int32_t, int32_t>>          int_pair_feature_l;
typedef vector<vector<pair<int32_t, int32_t>>>  int_pair_feature_ll;

/**
 * @class Stats
 *
 * @note  This is class for serializing the experiment stats of an application
 *        to a json file.
 *
 *        The format is:
 *
 *        {
 *           'time'        : "...",
 *           'application' : "...",
 *           'content'     : "..."
 *        } 
 *
 *        The content can be a much more complicated structure.
**/
class Stats 
{
public:

    enum options
    {
        RANGE = 0,
        DATANAME,
        NUMCC,
        NUMV,
        NUME,
        DIAMETER,
        GIRTH,
        CLUSTERCOEFF,
        BETWEENCENTRL,
        TRUSS,
        CLIQUE,
        CORE,
        DBSCAN
    };

    struct GraphProperty
    {
        int32_t               m_numCC;           ///< native code
        int_feature_l         m_numV;            ///< native code
        int_feature_l         m_numE;            ///< native code
        int_feature_l         m_diameter;        ///< boost
        int_feature_l         m_girth;           ///< native
        double_feature_l      m_clusterCoeff;    ///< boost
        double_feature_ll     m_betweenCentrl;   ///< boost
        int_pair_feature_ll   m_numTruss;        ///< native
        int_pair_feature_ll   m_numClique;       ///< boost
        int_pair_feature_ll   m_numCore;         ///< boost
        int_pair_feature_ll   m_numDBSCAN;       ///< boost

        GraphProperty() : m_numCC(0)
        {}

        void clear()
        {
            m_numCC = 0;
            m_numV.clear();
            m_numE.clear();
            m_diameter.clear();
            m_girth.clear();
            m_clusterCoeff.clear();
            m_betweenCentrl.clear();
            m_numTruss.clear();
            m_numClique.clear();
            m_numCore.clear();
            m_numDBSCAN.clear();
        }

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & m_numCC;
            ar & m_numV;
            ar & m_numE;
            ar & m_diameter;
            ar & m_girth;
            ar & m_clusterCoeff;
            ar & m_betweenCentrl;
            ar & m_numTruss;
            ar & m_numClique;
        }
    };

    static Stats *instance()
    {
        if (!m_instance)
        {
            m_instance = new Stats(Config::instance()->get("outfile"));
        }
        return m_instance;
    }

    ~Stats() {};

    void serialize()
    {
        if(m_application == "stmodel")
        {
            serialize_stmodel();
        }
    }

    void write_content(int32_t option, string &content)
    {
        if(m_application == "stmodel")
        {
            write_content_stmodel(option, content);
        }
    }

    string get_content(int32_t option)
    {
        string ret;
        if(m_application == "stmodel")
        {
            ret = get_content_stmodel(option);
        }
        return ret;
    }

    void   add_one_CC();

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_outFile;
        ar & m_time;
        ar & m_application;
        ar & m_dataName;
        ar & m_range;
        ar & m_gProperty;
    }

    void clear()
    {
        m_outFile     = "";
        m_time        = "";
        m_application = "";
        m_dataName    = "";
        m_range.clear();
        m_gProperty.clear();
    }

private:

    Stats(string outFile); 
    Stats(); 
    void   serialize_stmodel();
    void   write_content_stmodel(int32_t option, string &content);
    string get_content_stmodel(int32_t option);

    static Stats*   m_instance;

    string          m_outFile;      ///< output json to this file
    string          m_time;         ///< the creation time
    string          m_application;  ///< the application name

    string          m_dataName;     ///< data source name
    vector<int32_t> m_range;        ///< x,y and time
    GraphProperty   m_gProperty;    ///< graph properties

    FRIEND_TEST(StatsTest_1,              Success);
    FRIEND_TEST(BGLGraphProperty_1,       Success);
    FRIEND_TEST(BGLGraphProperty_2,       Success);
    FRIEND_TEST(BGLSTModel_1,             Success);
    FRIEND_TEST(BGLInitGraph_2,           Success);
    FRIEND_TEST(StatsSerializationTest_1, Success);
    FRIEND_TEST(BGLConnectedComponent_1,  Success);
};

#endif // __H_STATS__ 
