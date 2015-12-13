/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This is the class for test common usages. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   12/13/15 - Creation
 *
 *
**/

#pragma once
#ifndef _H_TEST_UTIL
#define _H_TEST_UTIL

using namespace std; 

#include "utils.h"

/**
 * @class CSR 
 *
 * This class defines a CSR, compressed sparse row; 
 * and provides basic operations on CSR.
 *
**/
class TstUtil 
{
public:

    enum OPTKIT_TST
    {
        OPTKIT_TEST_PASS = 1,
        OPTKIT_TEST_FAIL = 0
    };

    /**
     * @brief   Test if the content of two files are exactly the same.
     *
     *
    **/
    static int compareFile(const char* f1, const char* f2)
    {
        FILE *file_compared;
        if((file_compared = fopen(f1, "r")) == NULL)
        {
            printf("the file %s you input does not exist!\n", f1);
            ERROR_PRINT();
        }

        FILE *file_checked;
        if((file_checked = fopen(f2, "r")) == NULL)
        {
            printf("the file %s you input does not exist!\n", f2);
            ERROR_PRINT();
        }

        bool diff = false;
        char* b1 = (char*) calloc (1, OPTKIT_GTEST_SIZE);
        char* b2 = (char*) calloc (1, OPTKIT_GTEST_SIZE);
        size_t s1, s2;

        do 
        {
            s1 = fread(b1, 1, OPTKIT_GTEST_SIZE, file_compared);
            s2 = fread(b2, 1, OPTKIT_GTEST_SIZE, file_checked);

            if (s1 != s2 || memcmp(b1, b2, s1)) {
                diff = 1;
                break;
            }
        } while (!feof(file_compared) || !feof(file_checked));

        free(b1);
        free(b2);

        if (diff) return OPTKIT_TEST_FAIL;
        else return OPTKIT_TEST_PASS;
    }
};

#endif
