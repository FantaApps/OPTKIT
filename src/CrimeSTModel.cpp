/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/12/16 - add build_edges 
 *  stplaydog   02/11/16 - add query_list     
 *  stplaydog   02/10/16 - CSV read and RTree creation/query 
 *  stplaydog   02/09/16 - Creation
 *
**/

#include <string>
#include "../libs/CSVparser.h" 
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
        n.coord[2] = tm.tm_mon * 30 + tm.tm_mday;
        n.coord[0] = stoi(file[i][1]);
        n.coord[1] = stoi(file[i][2]);
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
        rt.Insert(nodes[i].coord, nodes[i].coord, &(nodes[i]));
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
    ASSERT(min && max);

    vector<int32_t> ret;
    rt.Search(min, max, list_callback, &ret);
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
    ASSERT(min && max);

    int32_t nhits = rt.Search(min, max, cont_callback, NULL);
    return nhits;
}

/**
 * @brief       given model biult and the specified range, build edges based on the range relationship
 *              for example, given a vertex and a range, each vertex in that range will have an egde
 *              between this vertex.
 *
 * @param[in]       x_gap       range in x coordinate
 * @param[in]       y_gap       range in y coordinate
 * @param[in]       z_gap       range in z coordinate
 *
 * @return      a list of egdes
**/
vector<pair<int32_t, int32_t>> CrimeSTModel::build_edges(int32_t x_gap, int32_t y_gap, int32_t z_gap)
{
    ASSERT(x_gap>=0 && y_gap>=0 && z_gap>=0);

    int32_t min[3];
    int32_t max[3];
    vector<pair<int32_t, int32_t>> ret;

    for(auto n : nodes)
    {
        min[0] = n.coord[0] - x_gap; min[1] = n.coord[1] - y_gap; min[2] = n.coord[2] - z_gap;
        max[0] = n.coord[0] + x_gap; max[1] = n.coord[1] + y_gap; max[2] = n.coord[2] + z_gap;

        vector<int32_t> v = query_list(min, max);

        for(auto i = v.begin(); i != v.end(); ++i)
        {
            if(*i > n.id)
            {
                ret.push_back(pair<int32_t, int32_t> (n.id, *i));
                ret.push_back(pair<int32_t, int32_t> (*i, n.id));
            }
        }
    }

    sort(ret.begin(), ret.end(), smaller);
    return ret;
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
        fprintf(writer, "%d %d|%d|%d %d %s\n", nodes[i].id, 
                nodes[i].coord[0], nodes[i].coord[1], nodes[i].coord[2],
                nodes[i].freq, nodes[i].type.c_str());
    }
    fclose(writer);
}

/**
 * @brief       serialize edges into file, for test purpose
**/
void CrimeSTModel::serialize_edges(vector<pair<int32_t, int32_t>> &edges)
{
    FILE *writer = fopen("crime_edges.txt", "w");
    for(auto e : edges)
    {
        fprintf(writer, "%d %d\n", e.first, e.second);
    }
    fclose(writer);
}
