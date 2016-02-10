/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/09/16 - Some refactor work 
 *  stplaydog   02/01/16 - Creation
 *
**/

#pragma once
#ifndef __H_CRIME_ST_MODEL__
#define __H_CRIME_ST_MODEL__

#include "STModel.h"

/**
 * @class SpatialTemporalGraphBuilder
 *
 * @note  This is the wrapper class that uses RTree to build 
 *        spatial temporal based graph.
**/
class CrimeSTModel : public STModel 
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

    CrimeSTModel(const string &input_file) :
       dist_limit(200),
       serial_num(0),
       time_limit(10)
    {
        read_data();

        build_model();
    }

    ~CrimeSTModel(){}

    virtual vector<int32_t> query(int32_t max[2], int32_t min[2], time_t ts[2]);

    virtual vector<int32_t> query(int32_t x, int32_t y, time_t ts, 
                                  int32_t cord_range, time_t time_range);

protected:
    vector<Node>     nodes;
    map<string, int> v_map;
    string           in_file;
    int32_t          dist_limit;
    int32_t          time_limit;
    int32_t          serial_num;

private:
    void read_data();
    void build_model();
};

#endif // SPATIAL_TEMPROAL_GRAPH_BUILDER__
