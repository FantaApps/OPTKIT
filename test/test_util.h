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
#include "csr.h"

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

    /**
     * @brief       read graph file into edge list
     *
     * @param[in]       file        graph file
     *
     * @return      edge list
    **/
    static vector<pair<int32_t, int32_t>> read_edge_list(const char *file)
    {
        vector<pair<int32_t, int32_t>> edges;
        FILE *reader = fopen(file, "r");
        int32_t num_v, num_e, num_c, v_from, v_to, c;
        fscanf(reader, "%d %d %d\n", &num_v, &num_c, &num_e);
        for(int i=0; i<num_e; i++)
        {
            fscanf(reader, "%d %d %d\n", &v_from, &v_to, &c);
            edges.push_back(pair<int32_t, int32_t>(v_from, v_to));
        }
        fclose(reader);
        return edges;
    }

    /**
     * @brief       This is a common entry for testing edge intersects
    **/
    static void compute_num_edge_intersect(CSR &g)
    {
        /* Test some basic graph properties */
        vector<pair<int32_t, int32_t> > v_rg;
        for(int i=0; i<g.get_num_v(); i++)
        {
            v_rg.push_back(g.get_e_range(i));
        }

        /* Compare the correctness of intersection */
        FILE *writer = fopen("./intersect.txt", "w"); 
        for(int i=0; i<g.get_num_v(); i++)
        {
            for(int j=i+1; j<g.get_num_v(); j++)
            {
                fprintf(writer, "%d %d %d\n", 
                        i, j, g.compute_num_edge_intersect(v_rg[i], v_rg[j]));
            }
        }
        fclose(writer);
    }

};

#endif
