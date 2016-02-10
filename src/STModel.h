
/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for create a spatial temporal model. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/08/16 - Creation
 *
**/

#pragma once
#ifndef __H_ST_MODEL__
#define __H_ST_MODEL__

#include <iostream>
#include <fstream>
#include "RTree.h"

using namespace std;

/**
 * @class STModel 
 *
 * @note  This is the wrapper class that reads the raw data
 *        and build a RTree based on the raw data.
 *        This data can support two types of queries 
 *
 *        1) given the range of the cube, return all node ids
 *           in that range.
 *        2) given the range of the cube, return count of nodes 
 *           in that range.
 *
 *        This class should be able to convert time_t to a integer
 *        so that a common framework could be utilized to index points
 *        in given time and given place.
**/
class STModel 
{
public:
    STModel() {};

    ~STModel() {};

    vector<int32_t> query_list(int32_t max[3], int32_t min[3]);

    int32_t         query_cont(int32_t max[3], int32_t min[3]);

    void            serialize();
};

#endif // __H_ST_MODEL__ 
