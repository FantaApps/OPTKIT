/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the header for k-core computation. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   09/01/16 - Creation
 *
**/

#pragma once
#ifndef _H_TRUSS
#define _H_TRUSS

#include "csr.h"
#include <iostream>
#include "gtest/gtest_prod.h"

using namespace std;

/**
 * @class Core 
 *
 * @brief  This class calculate the k-core 
**/
class Core {
public:

    Core() {};
    Core(int32_t v_num, int32_t c_num);
    virtual ~Core();
    void k_core(CSR &g, const char* outfile, 
                int32_t k_max, int32_t c = 0);

 protected:
    virtual void print_deg();
    virtual void compute_deg(CSR &g, int32_t c = 0);
    virtual bool deg_v_opr(CSR &g, int32_t k, int32_t c = 0);
    virtual void reduce_one_vet(CSR & g, int32_t v, int32_t c = 0);

private:

    int32_t num_v;      ///< total number of edges
    int32_t num_free_v; ///< total number of edges
    int32_t num_c;      ///< number of colors 
                        ///< (different edges have differen colors)
    int32_t **v_deg;    ///< edge support, for truss decomposition only

    int32_t get_num_v();
    int32_t get_num_c();
    void    reconstruct(CSR &g, int32_t c=0);


    // These are google test related
    FRIEND_TEST(InitCoreTest_1,   Success);
    FRIEND_TEST(InitCoreTest_2,   Success);
    FRIEND_TEST(ComputeDegTest_1, Success);
    FRIEND_TEST(ComputeDegTest_2, Success);
    FRIEND_TEST(ReduceOneVTest_1, Success);
    FRIEND_TEST(ReduceOneVTest_2, Success);
    FRIEND_TEST(DegVOprTest_1,    Success);
    FRIEND_TEST(DegEOprTest_2,    Success);
};
#endif
