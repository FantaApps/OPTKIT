/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This is the header for truss decomposition. 
 *
 *  MODIFIED   (MM/DD/YY)
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

/**
 * @class Truss 
 *
 * This class calculate the truss decomposition 
 *
**/
class Truss {
public:

    /**
     * @brief Constructor
     *
     * @param[in]       e_num       number of edges
     * @param[in]       c_num       number of colors 
     *
    **/
    Truss(int32_t e_num, int32_t c_num)
    {
        num_e = e_num;
        num_c = c_num;

        e_sup = new int32_t*[num_c];
        for(int32_t c=0; c<num_c; c++)
        {
            e_sup[c] = new int32_t[num_e];
            memset(e_sup[c], 0, num_e * sizeof(int32_t));
        }
    }

    /**
     * @brief   Destructor
     *
    **/
    ~Truss()
    {
        for(int32_t c =0; c<num_c; c++)
        {
            delete [] e_sup[c]; 
        }
        delete [] e_sup;
    }

    /**
     * @brief J.Wang Truss Decomposition in Massive Networks, Algorithm 1.
     *
     * @param[in]   
     *
    **/
    void truss_decomosition(CSR &g, const char* outfile, int32_t k_max, int32_t c = 0)
    {
        FILE *writer = fopen(outfile, "w");

        int32_t k = 3;

        compute_sup(g, c);

        while(g.get_num_e() > 0)
        {
            while(sup_e_opr(g, k));

            g.reconstruct();

            g.output_all_CC(writer);

            ++k;
        }

        fclose(writer);
    }

    /**
     * @brief   get number of edges 
     *
     * @return  number of edges 
    **/
    int32_t get_num_e()
    {
        return num_e;
    }

    /**
     * @brief   get number of colors 
     *
     * @return  number of colors 
    **/
    int32_t get_num_c()
    {
        return num_c;
    }


private:
    int32_t num_e;   ///< total number of edges
    int32_t num_c;   ///< number of colors 
                     ///< (different edges have differen colors)
    int32_t **e_sup; ///< edge support, for truss decomposition only

    /**
     * @brief   Compute the support number of each edge
     *
     * @return  N/A
    **/
    void compute_sup(CSR &g, int32_t c = 0)
    {
        for(int32_t i=0; i<g.get_num_v(); i++)
        {
            pair<int32_t, int32_t> rg1 = g.get_e_range(i);
            for(int32_t j=rg1.first; j<rg1.second; j++)
            {
                pair<int32_t, int32_t> rg2 = g.get_e_range(g.get_to_v(j));

                /* Update the support value */
                e_sup[c][j] = g.compute_num_edge_intersect(rg1, rg2);
            }
        }
    }

    /**
     * @brief   Find an edge of specific support requirement, and 
     *          perform some operations on it.
     *
     * @return  N/A
    **/
    bool sup_e_opr(CSR &g, int32_t k, int32_t c = 0)
    {
        bool ret = false;
        for(int32_t i=0; i<g.get_num_v(); ++i)
        {
            pair<int32_t, int32_t> rg = g.get_e_range(i);

            for(int32_t j=rg.first; j<rg.second; ++j)
            {
                if(e_sup[c][j] > (k - 2))
                {
                    reduce_one_edge(g, i);
                    reduce_one_edge(g, g.get_to_v(j));

                    g.set_rmvd(j);
                    e_sup[c][j] = 0;

                    ret = true;
                }
            }
        }

        return ret;
    }


    /**
     * @brief   Reduce the support number of every edge connected to v by 1.
     *
     * @param[in]       v       vertex id
     *
     * @return      N/A
    **/
    void reduce_one_edge(CSR & g, int32_t v, int32_t c=0)
    {
        pair<int32_t, int32_t> rg = g.get_e_range(v);

        for(int32_t i=rg.first; i<rg.second; i++)
        {
            --e_sup[c][i];
        }
    }

};

#endif
