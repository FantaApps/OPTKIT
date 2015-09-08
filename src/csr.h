/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This is the header of DCJ distance methods. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   09/03/15 - Creation
 *
**/

#pragma once
#ifndef _H_CSR
#define _H_CSR



/**
 * @class Truss 
 *
 * This class calculate the DCJ distance between two genomes
 * with unequal contents.
 *
**/
class CSR{
    struct edge
    {
        int from;
        int to;
    };
public:
    int32_t num_v;
    int32_t num_e;
    int32_t num_c;
    int32_t **v_idx;
    int32_t **e_idx;
    int32_t **e_sup; ///< for truss decomposition only

    void compute_sup();
    int32_t get_num_v();
    int32_t get_num_e();
    vector<int> get_intersect(int u, int w); 
};

#endif
