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
#include <glog/logging.h>

/**
 * @class SpatialTemporalGraphBuilder
 *
 * @note  This is the wrapper class that uses RTree to build 
 *        spatial temporal based graph.
**/
class CrimeSTModel : public STModel 
{
public:
    /**
     * @struct
     *
    **/
    struct Node 
    {
        int32_t id;
        int32_t min[3];
        int32_t max[3];
        int32_t freq;
        string  type;
    };

    CrimeSTModel(const string &input_file) :
       serial_num(0),
       in_file(input_file)
    {
        LOG(INFO) << "Reading data...";

        read_data();

        LOG(INFO) << "Finished reading data...";

        DLOG(INFO) << "Building model...";

        build_model();

        DLOG(INFO) << "Finished building model...";
    }

    ~CrimeSTModel(){}

    vector<int32_t> query_list(int32_t max[3], int32_t min[3]);
    int32_t         query_cont(int32_t max[3], int32_t min[3]);
    void            serialize();

protected:
    vector<Node>     nodes;
    string           in_file;
    int32_t          serial_num;

private:
    void read_data();
    void build_model();
};

#endif // SPATIAL_TEMPROAL_GRAPH_BUILDER__
