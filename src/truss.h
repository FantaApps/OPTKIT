/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the header for truss decomposition. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/14/16 - Separate enhanced truss logic, 
 *                         set neccessary function as virtual 
 *  stplaydog   01/10/16 - Some bug fixing works. 
 *  stplaydog   01/04/16 - Some bug fixing works. 
 *  stplaydog   12/14/15 - Add constructor/destructor 
 *  stplaydog   12/10/15 - Fix build bugs
 *  stplaydog   12/08/15 - Add the basic truss decomposition algorithm. 
 *  stplaydog   09/03/15 - Creation
 *
**/

#pragma once
#ifndef _H_TRUSS
#define _H_TRUSS

#include "csr.h"
#include <iostream>
#include "gtest/gtest_prod.h"
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

/**
 * @class Truss 
 *
 * @brief  This class calculate the truss decomposition 
**/
class Truss {
public:

    Truss() {};
    Truss(int32_t e_num, int32_t c_num);
    virtual ~Truss();
    void truss_decomosition(CSR &g, const char* outfile, 
                            int32_t k_max, int32_t c = 0);

 protected:
    virtual void print_sup();
    virtual void compute_sup(CSR &g, int32_t c = 0);
    virtual bool sup_e_opr(CSR &g, int32_t k, int32_t c = 0);
    virtual void reduce_one_edge(CSR & g, int32_t u, int32_t v, int32_t c = 0);

private:

    int32_t num_e;   ///< total number of edges
    int32_t num_c;   ///< number of colors 
                     ///< (different edges have differen colors)
    int32_t **e_sup; ///< edge support, for truss decomposition only

    int32_t get_num_e();
    int32_t get_num_c();
    void    reconstruct(CSR &g, int32_t c=0);


    // These are google test related
    FRIEND_TEST(InitTrussTest_1,          Success);
    FRIEND_TEST(ReduceOneETest_1,         Success);
    FRIEND_TEST(ComputeSupTest_1,         Success);
    FRIEND_TEST(SupEOprTest_1,            Success);
    FRIEND_TEST(InitTrussTest_2,          Success);
    FRIEND_TEST(ReduceOneETest_2,         Success);
    FRIEND_TEST(ReduceOneETest_3,         Success);
    FRIEND_TEST(ComputeSupTest_2,         Success);
    FRIEND_TEST(BuildSortedSupETest_1,    Success);
    FRIEND_TEST(TrussDecompositionTest_3, Success);
    FRIEND_TEST(SupEOprTest_2,            Success);
    FRIEND_TEST(SupEOprTest_3,            Success);
};
#endif
