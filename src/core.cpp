/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the header for k-core computation. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   09/01/16 - Creation
 *
**/

#include "core.h"
#include "Config.h"

/**
 * @brief Constructor
 *
 * @param[in]       v_num       number of vertices 
 * @param[in]       c_num       number of colors 
**/
Core::Core(int32_t v_num, int32_t c_num)
{
    num_v      = v_num;
    num_free_v = v_num;
    num_c      = c_num;

    v_deg = new int32_t*[num_c];
    for(int32_t c=0; c<num_c; c++)
    {
        v_deg[c] = new int32_t[num_v];
        memset(v_deg[c], 0, num_v * sizeof(int32_t));
    }
}

/**
 * @brief   Destructor
**/
Core::~Core()
{
    for(int32_t c =0; c<num_c; c++)
    {
        delete [] v_deg[c]; 
    }
    delete [] v_deg;
}

/**
 * @brief       J.Wang Core Decomposition in Massive Networks, Algorithm 1.
 *
 * @param[in]   
 *
 * @return      N/A
**/
void Core::k_core(CSR &g, const char* outfile, int32_t k_max, int32_t c)
{
    FILE *writer = fopen(outfile, "w");

    int32_t k = 3;

    LOG(INFO)<<"Computing initial degree..";
    compute_deg(g, c);

    while(get_num_v() > 0)
    {
        LOG(INFO)<<"Executing degport reduction operation of k="<<k;
        while(deg_v_opr(g, k));

        if(get_num_v() > 0)
        {
            fprintf(writer, "%d Core: \n", k);
            string kcore = to_string(k)+"core";
            Config::instance()->set("kcore", kcore);
            g.output_all_CC(writer, true);
        }

        ++k;
    }

    fclose(writer);
}

/**
 * @brief   get number of vertices 
 *
 * @return  number of vertices 
**/
int32_t Core::get_num_v()
{
    return num_free_v;
}

/**
 * @brief   get number of colors 
 *
 * @return  number of colors 
**/
int32_t Core::get_num_c()
{
    return num_c;
}

/**
 * @brief       Dump the content of degport
 *
 * @return      N/A
**/
void Core::print_deg()
{
    FILE *writer = fopen("deg.txt", "w");
    for(int32_t c=0; c<num_c; c++)
    {
        for(int32_t i=0; i<num_v; i++)
        {
            fprintf(writer, "%d ", v_deg[c][i]);
        }
        fprintf(writer, "\n");
    }
    fclose(writer);
}

/**
 * @brief   Compute the degree number of each vertex 
 *
 * @param[in]       g       graph of CSR format
 * @param[in]       c       color
 *
 * @return  N/A
**/
void Core::compute_deg(CSR &g, int32_t c)
{
    for(int32_t i=0; i<g.get_num_v(); i++)
    {
        pair<int32_t, int32_t> rg1 = g.get_e_range(i);

        /* Update the degree value */
        v_deg[c][i] = rg1.second - rg1.first; 
    }
}

/**
 * @brief   Find an edge of specific degport requirement, and 
 *          perform some operations on it.
 *
 * @param[in]       g       graph of CSR format
 * @param[in]       k       degport value
 *
 * @return  N/A
**/
bool Core::deg_v_opr(CSR &g, int32_t k, int32_t c)
{
    bool ret = false;
    for(int32_t i=0; i<g.get_num_v(); ++i)
    {
        if(v_deg[c][i] < k )
        {
            if(v_deg[c][i] > 0)
            {
                reduce_one_vet(g, i);
                ret = true;
            }
            g.remove_v(i, c);
        }
    }
    reconstruct(g);
    return ret;
}

/**
 * @brief      reconstruct the CSR graph and the edge degports
 *
 * @param[in]       g       CSR graph
 * @param[in]       c       color
 *
 * @return  N/A
 *
**/
void Core::reconstruct(CSR &g, int32_t c)
{
    LOG(INFO)<<"Reconstructing graph..";
    g.reconstruct();
}

/**
 * @brief   Reduce the degport number of every edge connected to v by 1.
 *
 * @param[in]       v       another vertex id
 *
 * @return      N/A
**/
void Core::reduce_one_vet(CSR & g, int32_t v, int32_t c)
{
    assert(v>=0 && v<g.get_num_v());

    pair<int32_t, int32_t> rg1 = g.get_e_range(v);
    for(int i=rg1.first; i<rg1.second; i++)
    {
        int32_t to = g.get_to_v(i);
        if(v_deg[c][to] != 0)
        {
            v_deg[c][to]--;
            if(v_deg[c][to] == 0)
            {
                num_free_v--;
            }
        }
    }
    v_deg[c][v] = 0;
    num_free_v--;
}
