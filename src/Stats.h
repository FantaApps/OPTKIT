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

using namespace std;


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
        NUMV,
        NUME,
        NUMCC,
        DIAMETER,
        GIRTH,
        CLUSTERCOEFF,
        BETWEENCENTRL,
        TRUSS,
        CLIQUE
    };

    struct GraphProperty
    {
        int32_t                          m_numV;            ///< native code
        int32_t                          m_numE;            ///< native code
        int32_t                          m_numCC;           ///< native code
        int32_t                          m_diameter;        ///< boost 
        int32_t                          m_girth;           ///< boost
        double                           m_clusterCoeff;    ///< boost
        double                           m_betweenCentrl;   ///< boost
        vector<pair<int32_t, int32_t>>   m_numTruss;        ///< native
        vector<pair<int32_t, int32_t>>   m_numClique;       ///< boost

        GraphProperty() : m_numV(0), 
                          m_numE(0),
                          m_numCC(0),
                          m_diameter(0),
                          m_girth(0),
                          m_clusterCoeff(0.0),
                          m_betweenCentrl(0.0)
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

private:

    Stats(string outFile); 
    Stats(); 
    void serialize_stmodel();
    void write_content_stmodel(int32_t option, string &content);

    static Stats*   m_instance;

    string          m_outFile;      ///< output json to this file
    string          m_time;         ///< the creation time
    string          m_application;  ///< the application name

    string          m_dataName;     ///< data source name
    vector<int32_t> m_range;        ///< x,y and time
    GraphProperty   m_gProperty;    ///< graph properties

    FRIEND_TEST(StatsTest_1,  Success);
};

#endif // __H_STATS__ 
