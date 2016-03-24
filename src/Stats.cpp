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
        <<"             \"betweenCentrl\" : "<<get_content_stmodel(BETWEENCENTRL)<<",\n"
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

