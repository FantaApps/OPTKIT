/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the header for dbscan computation. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   09/01/16 - Creation
 *
**/

#pragma once
#ifndef _H_DBSCAN
#define _H_DBSCAN

#include "csr.h"
#include "core.h"
#include <iostream>
#include "gtest/gtest_prod.h"

using namespace std;

/**
 * @class DBSCAN 
 *
 * @brief  This class calculate the k-core 
**/
class DBSCAN : public Core {
public:

    DBSCAN() {};
    DBSCAN(int32_t v_num, int32_t c_num) : Core(v_num, c_num) {}
    virtual ~DBSCAN() {}

 protected:
    virtual bool deg_v_opr(CSR & g, int32_t v, int32_t c = 0);
    bool check_in_cluster(CSR & g, int32_t v, int k, int32_t c = 0);

    // These are google test related
    FRIEND_TEST(CheckInCluster_1, Success);
    FRIEND_TEST(CheckInCluster_2, Success);
    FRIEND_TEST(DegVOprTest_3,    Success);
    FRIEND_TEST(DegVOprTest_4,    Success);
};
#endif
