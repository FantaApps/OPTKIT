/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Basic list implementation.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   01/31/16 - First version of refactory 
 *  stplaydog   08/02/15 - Creation
**/


#pragma once


#ifndef __LIST_H__
#define __LIST_H__

#include <cstdlib>
#include <map>
#include <vector>
#include <assert.h>

#include "node.h"

using namespace std;

/**
 * @class List
 *
 * @brief This is the core data structure to store
 *        status data.
**/
template <class T>
class List
{
public:

    /**
     * status    some of the constant definitions.
     *
    **/
    enum status
    {
        NOFILL = -1,
        DEFAULT_DATA_SIZE = 1024,
        DEFAULT_IDX_SIZE = 32,
    };

    /**
     * @struct      list_arr
     *
     * @brief       one list have multiple dimensions of a specific score
     *              This is uesed to store one dimensional array.
    **/
    struct list_arr
    {
        vector<T>       data;       ///< core ds
        vector<int32_t> idx;        ///< store the index of a chunk of data
        int32_t         num_filled; ///< total number of items being filled

        /**
         * @brief       constructor
         *
        **/
        list_arr()
        {
            data.resize(DEFAULT_DATA_SIZE);
            idx.resize(DEFAULT_IDX_SIZE);
            num_filled = 0;
        }

        /**
         * @brief   destructor
         *
        **/
        ~list_arr()
        {
        }

        /**
         * @brief   once the number of data buffer or idx buffer is not enough
         *          enlarge the buffer by a multiply factor.
         *
         * @param[in]       factor      the resize multiplier 
        **/
        void resize(int32_t factor = 2)
        {
            data.resize(data.size()*factor);
            idx.resize(data.size()*factor);
        }
    };

    List() {}

    ~List(){}
    
    /**
     * @brief       check the array size
     *
     * @note        this function should be thread safe
    **/
    bool check(Node<T> *node, int32_t node_id = -1)
    {
        int32_t required = node->get_encode_size();
        return true;
    }

    /**
     * Add one element into the list.
     * This insertion should be thread safe,
     * therefore, the allocation / resize work wo
     * uld be done outside of
     * this loop.
     *
     * if specified node_id, write to that node_id
     * else write to back
     *
     * @param[in]       score       which position to insert
     * @param[in]       node        which bucket to insert
     * @param[in]       node_id     which instance
     *
     * @return      N/A
    **/
    void add(int32_t score, Node<T>*  node, 
             int32_t node_id = -1) 
    {
        assert(node);

        list_arr *tmp = &m_arr[score];
        
        T* buf; 
        tmp->idx[node_id] = get_buf(tmp, node_id, buf); 

        node->serialize(buf, tmp->idx[node_id]);
        
        if(!node_id)
        {
            ++tmp->num_filled;
        }
    }

    /**
     * @brief       Get one from the list. 
     *
     * @param[in]       score       which position to insert
     * @param[in]       node        which bucket to insert
     * @param[in]       node_id     which instance
     *
     * @return      N/A
    **/
    void get(int32_t score,     Node<T>* node, 
             int32_t node_id = -1)
    {
        assert(node);

        list_arr *tmp = &m_arr[score];

        T* buf;
        get_buf(tmp, node_id, buf); 

        node->deserialize(buf, tmp->idx[node_id]);
        
        if(!node_id)
        {
            --tmp->num_filled;
        }
    }

protected:
    map<int32_t, list_arr> m_arr;         ///< The real content that stores the encode info.

private:
    /**
     * @ get the start buffer of a specific pos
     *
     * @param[in]       tmp     the array
     * @param[out]      buf     the pointer of the accoridng buffer 
     * @param[in]       node_id the accoridng node. 
     *
     * @return      start idx of the buffer
     *
    **/
    int32_t get_buf(list_arr* tmp, T* buf, int32_t node_id = -1)
    {
        assert(tmp && buf);
        
        int start_idx  = -1;
        if(!node_id)
        {
            start_idx  = tmp->num_filled ? 0 : tmp->idx[tmp->num_filled-1];
        }
        else
        {
            start_idx  = node_id == 0 ? 0 : tmp->idx[node_id-1];
        }

        buf = tmp->data.data() + start_idx; 

        return start_idx;
    }
};
#endif // __LIST_H__

