/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for keeping the program running stats
 *           The result could be serialized to a json file.  
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/20/16 - write function get_content_stmodel. 
 *  stplaydog   03/10/16 - Creation
 *
**/

#include "Stats.h"
#include "utils.h"
#include <boost/algorithm/string.hpp>

using namespace boost;

Stats *Stats::m_instance = 0;

Stats::Stats() {};

Stats::Stats(string outFile) 
{ 
    m_outFile     = outFile; 
    if(Config::instance()->get("application") == "truss")
    {
        m_application = "truss";
        m_time        = Utils::currentDateTime();
    }
    else if(Config::instance()->get("application") == "stmodel")
    {
        m_application = "stmodel";
        m_time        = Utils::currentDateTime();
    }
    else
    {
        m_application = "OPTKIT";
        m_time        = "1000";
    }
};

/**
 * @brief       To fill the content of a specific experiemnt
 *
 * @param[in]       option      which field to fill with
 * @param[in]       content     value of the field
 *
 * @return      N/A
 **/
void Stats::write_content_stmodel(int32_t option, string &content)
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
                Utils::string_to_vec<double>(content, m_gProperty.m_betweenCentrl);
                break;
            }
        case TRUSS:
            {
                vector<string> val = Utils::split(content, ',');
                m_gProperty.m_numTruss.push_back(pair<int, int>(stoi(val[0]), stoi(val[1])));
                break;
            }
        case CLIQUE:
            {
                vector<string> val;
                split(val, content, is_any_of(",")); 
                m_gProperty.m_numClique.push_back(pair<int, int>(stoi(val[0]), stoi(val[1])));
                break;
            }
    }
}

/**
 * @brief       To get the content of a specific experiemnt
 *
 * @param[in]       option      which field to fill with
 *
 * @return      N/A
 **/
string Stats::get_content_stmodel(int32_t option)
{
    string ret;
    switch (option)
    {
        case RANGE :
            {
                Utils::vec_to_string<int>(m_range, ret);
                break;
            } 
        case DATANAME :
            {
                ret = m_dataName;
                break;
            }
        case NUMV:
            {
                ret = to_string(m_gProperty.m_numV);
                break;
            }
        case NUME:
            {
                ret = to_string(m_gProperty.m_numE);
                break;
            }
        case NUMCC:
            {
                ret = to_string(m_gProperty.m_numCC); 
                break;
            }
        case DIAMETER:
            {
                ret = to_string(m_gProperty.m_diameter);
                break;
            }
        case GIRTH:
            {
                ret = to_string(m_gProperty.m_girth);
                break;
            }
        case CLUSTERCOEFF:
            {
                ret = to_string(m_gProperty.m_clusterCoeff);
                break;
            }
        case BETWEENCENTRL:
            {
                Utils::vec_to_string<double>(m_gProperty.m_betweenCentrl, ret);
                break;
            }
        case TRUSS:
            {
                Utils::vec_pair_to_string<int, int>(m_gProperty.m_numTruss, ret);
                break;
            }
        case CLIQUE:
            {
                Utils::vec_pair_to_string<int, int>(m_gProperty.m_numClique, ret);
                break;
            }
    }
    return ret;
}

void Stats::serialize_stmodel()
{

    using namespace json_spirit;

    ofstream writer (m_outFile);
    Object stm;
    stm["time"] = m_time;
    stm["application"] = m_application;


    Object content;
    content["data name"] = m_dataName;
    string range;
    Utils::vec_to_string<int>(m_range, range);
    content["range"] = range;

    Object gp;
    gp["numV"] = m_gProperty.m_numV;
    gp["numE"] = m_gProperty.m_numE;
    gp["numCC"] = m_gProperty.m_numCC;
    gp["diameter"] = m_gProperty.m_diameter;
    gp["girth"] = m_gProperty.m_girth;
    gp["clusterCoeff"] = m_gProperty.m_clusterCoeff;

    string bc;
    Utils::vec_to_string<double>(m_gProperty.m_betweenCentrl, bc);
    gp["betweenCentrl"] = bc;

    string allCC;
    Utils::vec_pair_to_string<int, int>(m_gProperty.m_numClique, allCC);
    gp["clique"] = allCC;

    string truss;
    Utils::vec_pair_to_string<int, int>(m_gProperty.m_numTruss, truss);
    gp["truss"] = truss;

    content["graph property"] = gp;
    
    stm["content"] = content;

    Array arr;
    arr.push_back(stm);
    write_formatted( stm, writer );

    writer.close();
}

