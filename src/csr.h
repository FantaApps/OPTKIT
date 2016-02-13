/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/13/16 - Refactor, separate .h and .cpp files 
 *  stplaydog   01/10/16 - Fix one bug in get_intersect_edges 
 *  stplaydog   01/04/16 - Fix one bug to remove one edge,
 *                         add get_intersect_edges()
 *  stplaydog   12/13/15 - Fixed some bugs 
 *  stplaydog   12/10/15 - Add constructor
 *  stplaydog   12/10/15 - Fix build bugs
 *  stplaydog   12/08/15 - Implemented compute support 
 *  stplaydog   09/03/15 - Creation
 *
**/

#pragma once
#ifndef _H_CSR
#define _H_CSR

#include "utils.h"
#include <algorithm>


using namespace std; 

/**
 * @class CSR 
 *
 * This class defines a CSR, compressed sparse row; 
 * and provides basic operations on CSR.
 *
**/
class CSR
{

public:

    enum DEF
    {
        RMVD = -1
    };

    CSR(const char *in_file);

    ~CSR();

    void allocate_data_structure(const int32_t v_num, 
                                 const int32_t e_num, 
                                 const int32_t c_num);

    int32_t compute_num_edge_intersect(pair<int32_t, int32_t> rg1,
                                       pair<int32_t, int32_t> rg2,
                                       int32_t c = 0);

    vector<int32_t> get_intersect_edges(int32_t u, int32_t v,
                                        int32_t c = 0);

    int32_t get_num_v();

    int32_t get_num_e();

    int32_t get_num_c();

    int32_t get_to_v(int32_t pos, int32_t c = 0);

    pair<int32_t, int32_t> get_e_range(int32_t v, int32_t c = 0);

    bool remove_e(int32_t from, int32_t to, int c = 0);

    void reconstruct(int32_t c = 0);

    void output_all_CC(FILE *writer, bool with_edge = false, int32_t c = 0);

    void visualize();

private:

    int32_t num_v;   ///< total number of vertices 
    int32_t num_e;   ///< total number of edges
    int32_t num_c;   ///< number of colors 
                     ///< (different edges have differen colors)
    int32_t **v_idx; ///< vertex index for CSR
    int32_t **e_idx; ///< edge index for CSR

    void output_one_CC(FILE *writer, int32_t v, 
                       bool *visited, int32_t c = 0);

};

#endif
