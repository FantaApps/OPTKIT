/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for keeping the program running stats
 *           The result could be serialized to a json file.  
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/06/16 - Creation
 *
**/

#pragma once
#ifndef __H_STATS__
#define __H_STATS__

#include "../libs/picojson.h"

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
    Stats(string outFile) { m_outFile = outFile; };

    ~Stats() {};

    virtual void serialize();
    virtual void write_content(int32_t option, string &content);

    string m_outFile;       ///<
    string m_time;          ///<
    string m_application;   ///<
};

class TrussStats : public Stats
{
}

class STModelStats : public Stats
{
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
        TRUSS
    };

public:

    struct GraphProperty
    {
        int32_t                          m_numV;            ///< native code
        int32_t                          m_numE;            ///< native code
        int32_t                          m_numCC;           ///< native code
        int32_t                          m_diameter;        ///< boost 
        int32_t                          m_girth;           ///< boost
        double                           m_cluterCoeff;     ///< boost
        double                           m_betweenCentrl;   ///< boost
        vector<pair<int32_t, int32_t>>   m_numTruss;        ///< native
    };

    void serialize()
    {
    }

    void write_content(int32_t option, string &content)
    {
        switch (option)
        {
            case RANGE :
            {
            } 
            case DATANAME :
            {
            }
            case NUMV:
            {
            }
            case NUME:
            {
            }
            case NUMCC:
            {
            }
            case DIAMETER:
            {
            }
            case GIRTH:
            {
            }
            case CLUSTERCOEFF:
            {
            }
            case BETWEENCENTRL:
            {
            }
            case TRUSS:
            {
            }
        }
    }

    string                           m_dataName;  ///<
    vector<int32_t>                  m_range;     ///<
    GraphProperty                    m_gProperty; ///<
}

#endif // __H_STATS__ 
