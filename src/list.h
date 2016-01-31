/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Basic list implementation.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/02/15 - Creation
**/


#pragma once


#ifndef __LIST_H__
#define __LIST_H__

#include <cstdio>
#include <cstdlib>
#include <map>
#include "omp.h"
#include <assert.h>
#include "node.h"

using namespace std;

template <class T>
class List
{
public:

    enum status
    {
        NOFILL = -1,
        DEFAULT_DATA_SIZE = 1024,
        DEFAULT_IDX_SIZE = 32,
    };

    struct list_arr
    {
        T*       data;
        int32_t* idx;
        int32_t  num_filled;
        int32_t  size;

        list_arr()
        {
        }

        ~list_arr()
        {
        }

        bool resize(int32_t factor = 2)
        {
        }
    };


    List() 
    {
    }

    ~List()
    {
    }

    bool check()
    {
    }

    /**
     * Add one element into the list.
     * This insertion should be thread safe,
     * therefore, the allocation / resize work wo
     * uld be done outside of
     * this loop.
     *
     * @param[in]       score       which position to insert
     * @param[in]       node        which bucket to insert
     * @param[in]       node_id     which instance
     *
     * @return      N/A
    **/
    void add(int32_t score, Node*  node, 
             int32_t node_id = -1) 
    {
        assert(node);

        list_arr *tmp = m_arr[score];

        int start_idx  = -1;
        if(node_id == -1)
        {
            start_idx  = tmp->num_filled ? 0 : tmp->idx[tmp->num_filled-1];
        }
        else
        {
            start_idx  = node_id == 0 ? 0 : tmp->idx[node_id-1];
        }

        T *buf = tmp->data + start_idx; 

        tmp->idx[node_id] = start_idx; 

        node->serialize(buf, tmp->idx[node_id]);
        
        if(!node_id)
        {
            ++tmp->num_filled;
        }
    }

    /**
     * Add one element into the list.
     *
     * @param[in]       pos         which position to insert
     * @param[in]       buck_id     which bucket to insert
     * @param[in]       encode      the encode to be stored
     * @param[in]       size        size of the encode
     * @param[in]       ins_id      which instance
     *
     * @return      N/A
    **/
    void get(int64_t pos,     int32_t buck_id, 
             T       *encode, int32_t &number, 
             int32_t ins_id)
    {
    }

protected:
    map<int32_t, list_arr*> m_arr;         ///< The real content that stores the encode info.
};

#endif
