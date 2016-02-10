/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
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

    for(int i=0; i<file.rowCount(); i++)
    {
        Node n;

        n.id = serial_num++;
        strptime(file[i][0].c_str(),"%Y/%m/%d", &tm); 
        n.min[2] = n.max[2] = tm.tm_mon;
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
    RTree<void*, int, 3, float> rt;

    for(int i=0; i<nodes.size(); i++)
    {
        rt.Insert(nodes[i].min, nodes[i].max, &(nodes[i]));
    } 
}

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

vector<int32_t> query(int32_t max[3], int32_t min[3])
{
}

