/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/11/16 - add query_list     
 *  stplaydog   02/10/16 - CSV read and RTree creation/query 
 *  stplaydog   02/09/16 - Creation
 *
**/

#include <string>
#include "CSVparser.h" 
#include "CrimeSTModel.h" 

/**
 * @brief       build graph from ny crime data
**/
void CrimeSTModel::read_data()
{
    csv::Parser file = csv::Parser(in_file.c_str());
    struct tm tm;

    for(int32_t i=0; i<file.rowCount(); i++)
    {
        Node n;

        n.id = serial_num++;
        strptime(file[i][0].c_str(),"%Y/%m/%d", &tm); 
        n.min[2] = n.max[2] = tm.tm_mon * 30 + tm.tm_mday;
        n.min[0] = n.max[0] = stoi(file[i][1]);
        n.min[1] = n.max[1] = stoi(file[i][2]);
        n.freq = stoi(file[i][3]);
        n.type = file[i][4];

        nodes.push_back(n);
    }
}

/**
 * @brief       build graph from ny crime data
**/
void CrimeSTModel::build_model()
{
    for(int32_t i=0; i<nodes.size(); i++)
    {
        rt.Insert(nodes[i].min, nodes[i].max, &(nodes[i]));
    } 
}

/**
 * @brief       given a range, return node ids in that range
 *
 * @param[in]       min         the min range
 * @param[in]       max         the max range
 *
 * @reurn       list of ids
**/
vector<int32_t> CrimeSTModel::query_list(int32_t min[3], int32_t max[3])
{
    vector<int32_t> ret;
    rt.Search(min, max, value_callback, &ret);
    return ret;
}

/**
 * @brief       given a range, return # nodes 
 *
 * @param[in]       min         the min range
 * @param[in]       max         the max range
 *
 * @reurn      # of nodes 
**/
int32_t CrimeSTModel::query_cont(int32_t min[3], int32_t max[3])
{
    int32_t nhits = rt.Search(min, max, search_callback, NULL);
    return nhits;
}

/**
 * @brief       serialize model into file, for test purpose
**/
void CrimeSTModel::serialize()
{
    FILE *writer = fopen("./crime_data.txt", "w");
    fprintf(writer, "%s %d\n", in_file.c_str(), serial_num);
    for(int i=0; i<nodes.size(); i++)
    {
        fprintf(writer, "%d %d|%d|%d %d|%d|%d %d %s\n", nodes[i].id, 
                nodes[i].min[0], nodes[i].min[1], nodes[i].min[2],
                nodes[i].max[0], nodes[i].max[1], nodes[i].max[2],
                nodes[i].freq, nodes[i].type.c_str());
    }
    fclose(writer);
}
