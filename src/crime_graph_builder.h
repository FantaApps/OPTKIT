
/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/01/16 - Creation
 *
**/

#pragma once
#ifndef __H_SPATIAL_TEMPROAL_GRAPH_BUILDER__
#define __H_SPATIAL_TEMPROAL_GRAPH_BUILDER__

#include "STModel.h"

/**
 * @class SpatialTemporalGraphBuilder
 *
 * @note  This is the wrapper class that uses RTree to build 
 *        spatial temporal based graph.
**/
class CrimeSTModel 
{
    /**
     * @struct
     *
    **/
    struct Node 
    {
        Node()  {}

        Node(int32_t x, int32_t y, int32_t z, time_t tt)
        {
            min[0] = x;
            min[1] = y;
            min[2] = z;

            max[0] = x;
            max[1] = y;
            max[2] = z;

            ts = tt;
        }

        int32_t id;
        time_t  ts;
        int32_t min[3];
        int32_t max[3];
        int32_t freq;
        string  type;
    };

    SpatialTemporalGraphBuilder(const string &input_file, 
                                const string &output_file)
    {
        serial_num = 0;
    }

    ~SpatialTemporalGraphBuilder(){}
    
    void build_graph()
    {
        RTree<void*, int, 3, float> rt;

        for(int i=0; i<nodes.size(); i++)
        {
            rt.Insert(nodes[i].min, nodes[i].max, &(nodes[i]));
        } 
    }
    
    /**
     * @brief       build graph from ny crime data
    **/
    void read_data()
    {
        ifstream reader(input_file);
        struct tm tm;
        string line;

        while(getline(reader, line))
        {
            Node n;
            n.id = serial_num++;

            isstringstream iss(line);

            string token;

            getline(iss, token, ',');
            strptime(token.c_str(),"%Y/%M/%D", &tm); 
            n.ts = mktime(tm);

            getline(iss, token, ',');
            n.xx[0] = n.xx[1] = stoi(token);

            getline(iss, token, ',');
            n.yy[0] = n.yy[1] = stoi(token);

            getline(iss, token, ',');
            n.freq = stoi(token);

            getline(iss, n.type, ',');

            nodes.push_back(n);
        }
    }


protected:
    vector<Node>     nodes;
    map<string, int> v_map;
    string           in_file;
    string           ou_file;
    int32_t          dist_limit;
    int32_t          time_limit;
    int32_t          serial_num;

private:
    void to_graph(Node &source, vector<pair<int, int>> nodes, 
                  ostream &os)
    {
    }
};

#endif // SPATIAL_TEMPROAL_GRAPH_BUILDER__
