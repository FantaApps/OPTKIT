/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/12/16 - change min[3] max[3] to coord[3] to save space.
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
        int32_t id;         ///< id of the node
        int32_t coord[3];   ///< coordinate of the node in spatial time space
        int32_t freq;       ///< frequency of this crime
        string  type;       ///< crime type

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & id;
            ar & coord;
            ar & freq;
            ar & type;
        }
        bool operator!= (const Node & node)
        {
            bool ret = true;
            if(id == node.id && freq == node.freq && type == node.type)
            {
                ret = false;
            }
            if(ret && (coord[0] == node.coord[0] &&
                       coord[1] == node.coord[1] &&
                       coord[2] == node.coord[2]))
            {
                ret = false;
            }
            return ret;
        }
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
       in_file(input_file),
       serial_num(0)
    {
        LOG(INFO) << "Reading data..";

        read_data();

        LOG(INFO) << "Building model..";

        build_model();
    }

    CrimeSTModel(){};
    ~CrimeSTModel(){}

    bool operator== (const CrimeSTModel & stm)
    {
        bool ret = true;
        if(&stm != this)
        {
            if(serial_num != stm.serial_num)
            {
                ret = false;
            }
            if(ret && in_file != stm.in_file)
            {
                ret = false;
            }
            if(ret)
            {
                for(size_t i=0; i<stm.nodes.size(); i++)
                {
                    if(nodes[i] != stm.nodes[i])
                    {
                        ret = false;
                        break;
                    }
                }
            }
        }
        return ret;
    }

    virtual vector<int32_t> query_list(int32_t min[3], int32_t max[3]);
    virtual int32_t         query_cont(int32_t min[3], int32_t max[3]);
    virtual edge_list       build_edges(int32_t x_gap, int32_t y_gap, int32_t z_gap);
    virtual edge_list_CC    build_edge_list_CC(int32_t x_gap, int32_t y_gap, int32_t z_gap);

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & nodes;
        ar & in_file;
        ar & serial_num;
    }

    void clear()
    {
        // we do not clear 
        nodes.clear();
        in_file    = "";
        serial_num = 0 ;
    }

protected:
    vector<Node>                    nodes;      ///< nodes read from CSV file
    RTree<void*, int32_t, 3, float> rt;         ///< rtree built
    string                          in_file;    ///< file to read the spatial temporal data
    int32_t                         serial_num; ///< keep the id

private:
    void        read_data();
    void        build_model();
    
    /**
     * @brief       callback for count query
     *
     * @param[in]       in          one value hit
     * @param[in]       arg         nothing
     *
     * @return      true if continue
    **/
    static bool cont_callback(void* in, void* arg) { return true; }

    /**
     * @brief       callback for list query, every hit will be added to a vector
     *
     * @param[in]       in          one value hit
     * @param[out]       arg         the output vector list
     *
     * @return      true if continue
    **/
    static bool list_callback(void* in, void* arg) 
    { 
        vector<int32_t> *v = (vector<int32_t> *) arg;
        Node *n = (Node*) in;
        v->push_back(n->id);
        return true; 
    }
    

    void serialize();
    void serialize_edges(edge_list &edges);
    void interpret_CC(const char *fIn, const char *fOut);

    void    union_find(const edge_list &el, vector<int32_t> &parent);
    int32_t find(const vector<int32_t> &parent, int32_t pos);

    FRIEND_TEST(SmallCrimeDataTest_1, Success);
    FRIEND_TEST(NYCrimeDataTest_1,    Success);
    FRIEND_TEST(NYCrimeDataTest_2,    Success);
};

#endif // SPATIAL_TEMPROAL_GRAPH_BUILDER__
