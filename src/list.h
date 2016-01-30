/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Basic list implementation.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/02/15 - Creation
**/


#pragma once


#ifndef _LIST_H
#define _LIST_H

#include <cstdio>
#include <cstdlib>
#include "omp.h"
#include "instance.h"
#include <vector>
#include <assert.h>
//#include "timer.h"
#define MODE_SEQ 1
#define MODE_PAR 2
#define MODE_TPAR 3
#define LIST_SIZE 1000000
#define CACHE_FILL 64

using namespace std;

template <class T>
class List
{
public:
    time_list t;           ///<

    T   **content;         ///< The real content that stores the encode info.
    int **c_idx;           ///< Iontent index indicate start and end position.
    int *c_pos;            ///< Indicate how many position have been filled.

    int32_t **count;       ///< number of element in thread i of bucket j
    int32_t **nei_score;   ///<
    int32_t **start;       ///<
    int32_t **end;         ///<
    int32_t **idx_sum;     ///<
    bool    **eliminate;   ///<
    int32_t *elim_idx;     ///<

    int64_t *num;          ///<

    int64_t read_num;      ///<
    int64_t write_num;     ///<
    int64_t read_cnt;      ///<
    int64_t write_cnt;     ///<

    int32_t upper_bound;   ///<
    int32_t lower_bound;   ///<
    int32_t num_threads;   ///<
    int32_t buck_size;     ///< 
    int32_t base;          ///<
    int32_t max_val;       ///<
    int32_t min_val;       ///<
    int32_t search_space;  ///<
    int32_t parallel_base; ///<

    bool is_ub;            ///<
    bool is_enumerate_all; ///<
    bool is_parallel;      ///<
    bool lk_terminate;     ///<
    bool is_lk_max;        ///<
    bool is_lk;            ///<

    //this for debug purpose only
#ifdef USE_DEBUG
    int32_t **g_count_list;
    int32_t *g_count_idx;
#endif

public:
    /* main functions */
    List(int32_t buck_size, int32_t list_size, 
         int32_t base,      int32_t num_t, 
         bool is_ub,        bool is_enumerate_all = false);

    virtual ~List() {};

    bool compute_partition(int32_t buck_id, Instance** ins);
    void reorder_list(int32_t buck_id, Instance** ins);
    void bnb_parallel_bucket(Instance** ins);
    void bnb(Instance** ins, int32_t ins_id);
    void expand_ub(Instance **ins, int32_t tid, int32_t buck_id, omp_lock_t writelock);
    void expand_lb(Instance **ins, int32_t tid, int32_t buck_id, omp_lock_t writelock);
    void print_buck();

    //lin kernighan algorithm implementation
    void lk(Instance** ins, int32_t heu_level, int32_t term_move, bool is_opt);
    bool add_child_combinations(Instance **ins, int32_t current_level, int32_t use_heu);
    bool add_child_max(Instance **ins, int32_t current_level, int32_t use_heu);
    void reset_list();
    void add_g_count_list(int32_t pos, int32_t g_count);

    /**
     * Add one element into the list.
     *
     * @param[in]       pos         which position to insert
     * @param[in]       buck_id     which bucket to insert
     * @param[in]       num_code    size of the encode
     * @param[in]       encode      the encode to be stored
     * @param[in]       ins_id      which instance
     *
     * @return      N/A
    **/
    void add(int64_t pos,      int32_t buck_id, 
             int32_t num_code, T       *encode, 
             int32_t ins_id) 
    {
        int stt = pos == 0 ? 0 : c_idx[buck_id][pos-1];
        for(int i=0; i<num_code; i++)
        {
            content[buck_id][stt++] = encode[i];
        }

        c_idx[buck_id][pos] =stt;
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
             T       *encode, int32_t *num, 
             int32_t ins_id)
    {
        int start = pos == 0 ? 0 : c_idx[buck_id][pos-1];
        int end   = c_idx[buck_id][pos];
        for(int i=0, j=start; j<end; i++,j++)
        {
            encode[i] = content[buck_id][j];
        }

        *number = (end-start);
    }

    /**
     * Reset the number in the list, which means cleaning.
     *
     * @return      N/A
    **/
    void reset_num()
    {
        for(int i=lower_bound; i<upper_bound; i++)
        {
            if(start[0][i-base] < end[num_threads-1][i-base])
            {
                num[i-base] = end[num_threads-1][i-base];
            }
        }
    }

    void    prepare_parallel_list(int32_t buck_id) = 0;

    int32_t copy_zero(int32_t buck_id) = 0;

    void    copy(List *other, int32_t buck_id, int32_t size) = 0;

    void    print_bucket(int32_t buck_id) = 0;
};

#endif
