/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Unittest of CSR graph structure. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/01/16 - Creation
**/

#include <gtest/gtest.h>
#include "csr.h"
#include "test_util.h" 


/**
 * @brief   Test a small graph one color
 *
**/
TEST(NYCrimeDataTest_1, Success)
{
    struct Rect
    {
        Rect()  {}

        Rect(int a_minX, int a_minY, int a_maxX, int a_maxY)
        {
            min[0] = a_minX;
            min[1] = a_minY;

            max[0] = a_maxX;
            max[1] = a_maxY;
        }


        int min[2];
        int max[2];
    };
}

