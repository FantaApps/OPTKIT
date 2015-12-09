/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This is the header for truss decomposition. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   12/08/15 - Add the basic truss decomposition algorithm. 
 *  stplaydog   09/03/15 - Creation
 *
**/

#pragma once
#ifndef _H_TRUSS
#define _H_TRUSS



/**
 * @class Truss 
 *
 * This class calculate the truss decomposition 
 *
**/
class Truss {
public:

    /**
     *
     *
    **/
    void truss_decomosition(CSR &g, const char* outfile, int k_max)
    {
        FILE *writer = fopen(outfile, "w");

        int k = 3;

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


private:
    int32_t num_e;   ///< total number of edges
    int32_t num_c;   ///< number of colors 
                     ///< (different edges have differen colors)
    int32_t **e_sup; ///< edge support, for truss decomposition only

    /**
     * @brief   Find an edge of specific support requirement, and 
     *          perform some operations on it.
     *
     * @return  N/A
    **/
    bool sup_e_opr(CSR &g, int k, int c = 0)
    {
        bool ret = false;
        for(int i=0; i<g.get_num_v(); ++i)
        {
            pair<int32_t, int32_t> rg = g.get_e_range(i);

            for(int j=rg.first; j<rg.second; ++j)
            {
                if(e_sup[c][j] > (k - 2))
                {
                    reduce_one_edge(i);
                    reduce_one_edge(get_to_v(j));

                    set_rmvd(j);
                    e_sup[c][j] = 0;

                    ret = true;
                }
            }
        }

        return ret;
    }

    /**
     * @brief   Compute the support number of each edge
     *
     * @return  N/A
    **/
    void compute_sup(CSR &g, int c = 0)
    {
        for(int i=0; i<num_v; i++)
        {
            pair<int32_t, int32_t> rg1 = g.get_e_range(i);
            for(int j=start1; j<end1; j++)
            {
                pair<int32_t, int32_t> rg2 = g.get_e_range(g.e_idx[c][j]);

                /* Update the support value */
                g.e_sup[c][j] = g.compute_num_edge_intersect(rg1, rg2);
            }
        }
    }

    /**
     * @brief   Reduce the support number of every edge connected to v by 1.
     *
     * @param[in]       v       vertex id
     *
     * @return      N/A
    **/
    void reduce_one_edge(int v, int c=0)
    {
        pair<int32_t, int32_t> rg = g.get_e_range(v);

        for(int i=rg.first; i<rg.second; i++)
        {
            --e_sup[c][i];
        }
    }

};

#endif
