/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    List of interger elements implementation.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/02/15 - Creation
**/

#pragma once
#ifndef _H_LISTMC
#define _H_LISTMC

#include "list.h"

using namespace std;

/**
 *  @class      IntList
 *
 *  @brief      Maximum clique list.
 *
 *  @details    This is the list for solving maximum clique problem.
**/
class IntList : public List
{
public:

    IntList(int32_t b_size, int32_t list_size, int32_t b, int32_t num_t, bool is_ub, int num_elem, bool *is_enumerate=NULL);
    ~IntList();

    void add(int64_t pos, int32_t buck_id, int num_code, int *encode, int ins_id)

    void get(int64_t pos, int32_t buck_id, int *encode, int *number, int ins_id)
    {
    }

    void reset_num()
    {
    }

    void prepare_parallel_list(int buck_id);
    int  copy_zero(int buck_id);
    void copy(List *other, int buck_id, int size);
    void print_bucket(int buck_id);
};

#endif
