/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the header for k-core computation. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   09/02/16 - Creation
 *
**/

#include "dbscan.h"
#include "Config.h"

/**
 * @brief   Find an edge of specific degport requirement, and 
 *          perform some operations on it.
 *
 * @param[in]       g       graph of CSR format
 * @param[in]       k       degport value
 *
 * @return  N/A
**/
bool DBSCAN::deg_v_opr(CSR &g, int32_t k, int32_t c)
{
    bool ret = false;
    for(int32_t i=0; i<g.get_num_v(); ++i)
    {
        if(v_deg[c][i] < k )
        {
            if(!check_in_cluster(g, i, k))
            {
                if(v_deg[c][i] > 0)
                {
                    reduce_one_vet(g, i);
                    ret = true;
                }
                g.remove_v(i, c);
            }
        }
    }
    reconstruct(g);
    return ret;
}

bool DBSCAN::check_in_cluster(CSR & g, int32_t v, int k, int32_t c)
{
    bool ret = false;
    pair<int32_t, int32_t> rg1 = g.get_e_range(v);
    for(int i=rg1.first; i<rg1.second; i++)
    {
        int32_t to = g.get_to_v(i);
        if(v_deg[c][to] >=k)
        {
            ret = true;
            break;
        }
    }
    return ret;
}
