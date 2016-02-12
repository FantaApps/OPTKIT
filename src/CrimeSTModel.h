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

#include "gtest/gtest_prod.h"

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
        int32_t coord[3];
        int32_t freq;
        string  type;
    };

    /**
     * @brief       build the spatial temporal model following two steps
     *              1) read the data
     *              2) build RTree
     *
     * @param[in]       input_file      the file input of the CSV format
     *
    **/
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

    virtual vector<int32_t>                query_list(int32_t min[3], int32_t max[3]);
    virtual int32_t                        query_cont(int32_t min[3], int32_t max[3]);
    virtual vector<pair<int32_t, int32_t>> build_edges(int32_t x_gap, int32_t y_gap, 
                                               int32_t z_gap);

protected:
    vector<Node>                    nodes;      ///< nodes read from CSV file
    RTree<void*, int32_t, 3, float> rt;         ///< rtree built
    string                          in_file;    ///< file to read the spatial temporal data
    int32_t                         serial_num; ///< keep the id

private:
    void        read_data();
    void        build_model();

    static bool search_callback(void* in, void* arg) { return true; }

    static bool value_callback(void* in, void* arg) 
    { 
        vector<int32_t> *v = (vector<int32_t> *) arg;
        Node *n = (Node*) in;
        v->push_back(n->id);
        return true; 
    }

    static bool smaller(pair<int32_t, int32_t> e1, pair<int32_t, int32_t> e2)
    {
        if(e1.first < e2.first)
        {
            return true;
        }
        else if(e1.first == e2.first && e1.second <= e2.second)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void serialize();
    void serialize_edges(vector<pair<int32_t, int32_t>> &edges);

    FRIEND_TEST(SmallCrimeDataTest_1, Success);
    FRIEND_TEST(NYCrimeDataTest_1, Success);
};

#endif // SPATIAL_TEMPROAL_GRAPH_BUILDER__
