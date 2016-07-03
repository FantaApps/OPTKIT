/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the header for truss decomposition. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/14/16 - Fixed a bug to output truss number when dumping. 
 *  stplaydog   01/10/16 - Some bug fixing works. 
 *  stplaydog   01/04/16 - Some bug fixing works. 
 *  stplaydog   12/14/15 - Add constructor/destructor 
 *  stplaydog   12/10/15 - Fix build bugs
 *  stplaydog   12/08/15 - Add the basic truss decomposition algorithm. 
 *  stplaydog   09/03/15 - Creation
 *
**/

#include "truss.h"
#include "Config.h"


/**
 * @brief Constructor
 *
 * @param[in]       e_num       number of edges
 * @param[in]       c_num       number of colors 
**/
Truss::Truss(int32_t e_num, int32_t c_num)
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
**/
Truss::~Truss()
{
    for(int32_t c =0; c<num_c; c++)
    {
        delete [] e_sup[c]; 
    }
    delete [] e_sup;
}

/**
 * @brief       J.Wang Truss Decomposition in Massive Networks, Algorithm 1.
 *
 * @param[in]   
 *
 * @return      N/A
**/
void Truss::truss_decomosition(CSR &g, const char* outfile, int32_t k_max, int32_t c)
{
    FILE *writer = fopen(outfile, "w");

    int32_t k = 3;

    LOG(INFO)<<"Computing initial support..";
    compute_sup(g, c);

    while(g.get_num_e() > 0)
    {
        LOG(INFO)<<"Executing support reduction operation of k="<<k;
        while(sup_e_opr(g, k));

        if(g.get_num_e() > 0)
        {
            fprintf(writer, "%d Truss: \n", k);
            string ktruss = to_string(k)+"truss";
            Config::instance()->set("ktruss", ktruss);
            g.output_all_CC(writer, true);
        }

        ++k;
    }

    fclose(writer);
}

/**
 * @brief   get number of edges 
 *
 * @return  number of edges 
**/
int32_t Truss::get_num_e()
{
    return num_e;
}

/**
 * @brief   get number of colors 
 *
 * @return  number of colors 
**/
int32_t Truss::get_num_c()
{
    return num_c;
}

/**
 * @brief       Dump the content of support
 *
 * @return      N/A
**/
void Truss::print_sup()
{
    FILE *writer = fopen("sup.txt", "w");
    for(int32_t c=0; c<num_c; c++)
    {
        for(int32_t i=0; i<num_e; i++)
        {
            fprintf(writer, "%d ", e_sup[c][i]);
        }
        fprintf(writer, "\n");
    }
    fclose(writer);
}



/**
 * @brief   Compute the support number of each edge
 *
 * @param[in]       g       graph of CSR format
 * @param[in]       c       color
 *
 * @return  N/A
**/
void Truss::compute_sup(CSR &g, int32_t c)
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
 * @param[in]       g       graph of CSR format
 * @param[in]       k       support value
 *
 * @return  N/A
**/
bool Truss::sup_e_opr(CSR &g, int32_t k, int32_t c)
{
    bool ret = false;
    for(int32_t i=0; i<g.get_num_v(); ++i)
    {
        pair<int32_t, int32_t> rg = g.get_e_range(i);

        for(int32_t j=rg.first; j<rg.second; ++j)
        {
            if(e_sup[c][j] < (k - 2))
            {
                int32_t to = g.get_to_v(j);
                if(i < to)
                {
                    reduce_one_edge(g, i, to);
                    g.remove_e(i, to);

                    ret = true;
                }
            }
        }
    }

    LOG(INFO)<<"Reconstructing graph..";
    g.reconstruct();

    LOG(INFO)<<"Reordering support array..";
    /* moving elements in e_sup */
    int32_t cur=0, nxt=0;
    while(nxt < num_e)
    {
        if(e_sup[c][nxt] == -1) 
        {
            ++nxt;
        }
        else
        {
            e_sup[c][cur] = e_sup[c][nxt];
            ++cur;
            ++nxt;
        }
    }
    num_e = cur;

    return ret;
}


/**
 * @brief   Reduce the support number of every edge connected to v by 1.
 *
 * @param[in]       u       one vertex id
 * @param[in]       v       another vertex id
 *
 * @return      N/A
**/
void Truss::reduce_one_edge(CSR & g, int32_t u, int32_t v, int32_t c)
{
    assert(u>=0 && u<g.get_num_v());
    assert(v>=0 && v<g.get_num_v());

    vector<int32_t> W = g.get_intersect_edges(u, v); 

    for(vector<int32_t>::iterator it = W.begin(); it != W.end(); ++it)
    {
        --e_sup[c][*it];
    }

    pair<int32_t, int32_t> rg1 = g.get_e_range(u);
    pair<int32_t, int32_t> rg2 = g.get_e_range(v);

    auto cmp = [](const void* a, const void* b)
    {
        return (int) ((*(int32_t*)a) == (*(int32_t*)b));
    };

    int32_t from_e = *(int32_t*)bsearch(&v, e_sup[c], rg1.second - rg1.first,  
                                  sizeof(int32_t), 
                                   cmp);
    int32_t to_e = *(int32_t*)bsearch(&u, e_sup[c], rg2.second - rg2.first,  
                                  sizeof(int32_t), 
                                   cmp);

    e_sup[c][from_e] = -1;
    e_sup[c][to_e]   = -1;
}
