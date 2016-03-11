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

    static Stats *instance()
    {
        if (!m_instance)
        {
            //if(truss.isSet())
            //{
            //    m_instance = new TrussStats;
            //}
            //else if(truss.isSet())
            //{
            //    m_instance = new STModelStats;
            //}
        }
        return m_instance;
    }

    ~Stats() {};

    virtual void serialize() = 0;
    virtual void write_content(int32_t option, string &content) = 0;

protected:
    Stats(string outFile) 
    { 
        m_outFile     = outFile; 
        //if(truss.isSet())
        //{
        //    m_application = "truss";
        //    m_time        = currentDateTime();
        //}
        //else if(stmodel.isSet())
        //{
        //    m_application = "stmodel";
        //    m_time        = currentDateTime();
        //}
        //else
        //{
        //    m_application = "OPTKIT";
        //    m_time        = "1000";
        //}
    };


    static Stats *m_instance;


    string m_outFile;       ///< output json to this file
    string m_time;          ///< the creation time
    string m_application;   ///< the application name
};

class TrussStats : public Stats
{
};

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

    STModelStats(string outFile) : Stats(outFile) { };

    ~STModelStats() {};

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
    };

    void serialize()
    {
        ofstream writer (m_outFile);

        writer<<"{"<<endl;

        writer<<"   \"time\""<<" : "<<m_time<<","<<endl;
        writer<<"   \"application\""<<" : "<<"\""<<m_application<<"\","<<endl;
        writer<<"   \"content\""<<" : {"<<endl;
        writer<<"        \"data name\""<<" : "<<"\""<<m_dataName<<"\","<<endl;
        writer<<"        \"range\""<<" : "<<"[\n"
              <<"             "<<m_range[0]<<",\n"
              <<"             "<<m_range[1]<<",\n"
              <<"             "<<m_range[2]<<"\n"
              <<"        ],"<<endl;
        writer<<"        \"graph property\""<<" : "<<"[\n"
              <<"             \"numV\" : "<<m_gProperty.m_numV<<",\n"
              <<"             \"numE\" : "<<m_gProperty.m_numE<<",\n"
              <<"             \"numCC\" : "<<m_gProperty.m_numCC<<",\n"
              <<"             \"diameter\" : "<<m_gProperty.m_diameter<<",\n"
              <<"             \"girth\" : "<<m_gProperty.m_girth<<",\n"
              <<"             \"clusterCoeff\" : "<<m_gProperty.m_clusterCoeff<<",\n"
              <<"             \"betweenCentrl\" : "<<m_gProperty.m_betweenCentrl<<",\n"
              <<"             \"truss\" : "<<"[\n";
        for(size_t i=0; i<m_gProperty.m_numTruss.size(); i++)
        {
            writer<<"                  "<<m_gProperty.m_numTruss[i].first<<" : "<<m_gProperty.m_numTruss[i].second;
            if(i!=m_gProperty.m_numTruss.size()-1)
                writer<<",";
            writer<<endl;
        }
        writer<<"             ]\n        ]\n";

        writer<<"    }"<<endl;
        writer<<"}"<<endl;

        writer.close();
    }
    
    /**
     * @brief       To fill the content of a specific experiemnt
     *
     * @param[in]       option      which field to fill with
     * @param[in]       content     value of the field
     *
     * @return      N/A
    **/
    void write_content(int32_t option, string &content)
    {
        switch (option)
        {
            case RANGE :
            {
                vector<string> val = Utils::split(content, ',');
                m_range.push_back(stoi(val[0]));
                m_range.push_back(stoi(val[1]));
                m_range.push_back(stoi(val[2]));
                break;
            } 
            case DATANAME :
            {
                m_dataName = content;
                break;
            }
            case NUMV:
            {
                m_gProperty.m_numV = stoi(content);
                break;
            }
            case NUME:
            {
                m_gProperty.m_numE = stoi(content);
                break;
            }
            case NUMCC:
            {
                m_gProperty.m_numCC = stoi(content);
                break;
            }
            case DIAMETER:
            {
                m_gProperty.m_diameter = stoi(content);
                break;
            }
            case GIRTH:
            {
                m_gProperty.m_girth = stoi(content);
                break;
            }
            case CLUSTERCOEFF:
            {
                m_gProperty.m_clusterCoeff = stod(content);
                break;
            }
            case BETWEENCENTRL:
            {
                m_gProperty.m_betweenCentrl = stod(content);
                break;
            }
            case TRUSS:
            {
                vector<string> val = Utils::split(content, ',');
                m_gProperty.m_numTruss.push_back(pair<int, int>(stoi(val[0]), stoi(val[1])));
                break;
            }
        }
    }

    string                           m_dataName;  ///< data source name
    vector<int32_t>                  m_range;     ///< x,y and time
    GraphProperty                    m_gProperty; ///< graph properties

    FRIEND_TEST(StatsTest_1,  Success);
};

#endif // __H_STATS__ 
