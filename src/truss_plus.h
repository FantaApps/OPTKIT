/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the header for enhanced truss decomposition. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/14/16 - Creation
 *
**/

#pragma once
#ifndef _H_TRUSS_PLUS
#define _H_TRUSS_PLUS

#include "truss.h"
#include <iostream>
#include "gtest/gtest_prod.h"

using namespace std;

/**
 * @class TrussPlus 
 *
 * @brief  This class calculate the truss decomposition 
 *         with the enhanced algorithm
**/
class TrussPlus : public Truss {
public:

    TrussPlus()          {}
    virtual ~TrussPlus() {}

    /**
     * @struct      SortedSup
     *
     * @brief       used to sort edges based on support
    **/
    struct SortedSup 
    {
        int32_t m_vFrom;  ///< from vertex
        int32_t m_vTo;    ///< to vertex
        int32_t m_eSup;   ///< edge support
        int32_t m_eIdx;   ///< original edge position

        SortedSup(int32_t vFrom, int32_t vTo, int32_t eSup, int32_t eIdx)
            : m_vFrom(vFrom), m_vTo(vTo), m_eSup(eSup), m_eIdx(eIdx)
        {}
        SortedSup(int32_t eSup)
            : m_vFrom(0), m_vTo(0), m_eSup(eSup), m_eIdx(0)
        {}
    };

protected:

    virtual void print_sup      ();
    virtual void compute_sup    (CSR &g, int32_t c = 0);
    virtual bool sup_e_opr      (CSR &g, int32_t k, int32_t c = 0);
    virtual void reduce_one_edge(CSR &g, int32_t u, int32_t v, int32_t c=0);

private:

    vector<SortedSup> m_sortSupE; ///< sorted edge supports
    vector<int32_t>   m_bin;      ///< store the start position of 
                                  ///< each support
    vector<int32_t>   m_pos;      ///< index of each edge


    // These are google test related
    FRIEND_TEST(BuildSortedSupETest_1,    Success);
    FRIEND_TEST(TrussDecompositionTest_3, Success);
    FRIEND_TEST(ReduceOneETest_3,         Success);
};
#endif
