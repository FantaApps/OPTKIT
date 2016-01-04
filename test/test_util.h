/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
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
 * @class TstUtil 
 *
 * This class give some basic funtions for testing
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
     * @param[in]       f1      first file to be compared
     * @param[in]       f2      second file to be compared
     *
    **/
    static int compareFile(const char* f1, const char* f2, bool is_wildcard=false)
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

            if(is_wildcard)
            {
                if(!isMatch(b1, b2))
                {
                    diff = 1;
                    break;
                }
            }
            else if (s1 != s2 || memcmp(b1, b2, s1)) 
            {
                diff = 1;
                break;
            }
        } while (!feof(file_compared) || !feof(file_checked));

        free(b1);
        free(b2);

        if (diff) return OPTKIT_TEST_FAIL;
        else return OPTKIT_TEST_PASS;
    }

    static bool isMatch(const char *s, const char *p) {
        const char* star=NULL;
        const char* ss=s;

        while (*s){
            //advancing both pointers when (both characters match) or ('?' found in pattern)
            //note that *p will not advance beyond its length 
            if ((*p=='.')||(*p==*s))
            {
                s++;
                p++;
                continue;
            } 

            // * found in pattern, track index of *, only advancing pattern pointer 
            if (*p=='*')
            {
                star=p++; 
                ss=s;
                continue;
            } 

            //current characters didn't match, last pattern pointer was *, current pattern pointer is not *
            //only advancing pattern pointer
            if (star)
            { 
                p = star+1; 
                s=++ss;
                continue;
            } 

            //current pattern pointer is not star, last patter pointer was not *
            //characters do not match
            return false;
        }

        //check for remaining characters in pattern
        while (*p=='*')
        {
            p++;
        }

        return !*p;  
    }

};

#endif
