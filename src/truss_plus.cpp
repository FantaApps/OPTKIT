/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the header for truss decomposition. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/14/16 - Creation
 *
**/

#include "truss_plus.h"
#include "Config.h"

void TrussPlus::print_sup()
{
    FILE *writer = fopen("sup.txt", "w");

    for(auto iter = m_pos.begin(); iter != m_pos.end(); ++iter)
    {
        fprintf(writer, "%d ", m_sortSupE[*iter].m_eSup);
    }
    fprintf(writer, "\n");

    for(auto iter = m_sortSupE.begin(); iter != m_sortSupE.end(); ++iter)
    {
        fprintf(writer, "%d %d %d\n", iter->m_vFrom, iter->m_vTo, iter->m_eSup);
    }

    for(auto iter = m_bin.begin(); iter != m_bin.end(); ++iter)
    {
        fprintf(writer, "%d ", *iter);
    }
    fprintf(writer, "\n");

    fclose(writer);
}

void TrussPlus::compute_sup(CSR &g, int32_t c)
{
    for(int32_t i=0; i<g.get_num_v(); ++i)
    {
        pair<int32_t, int32_t> rg1 = g.get_e_range(i);
        for(int32_t j = rg1.first; j<rg1.second; ++j)
        {
            int32_t to = g.get_to_v(j);
            pair<int32_t, int32_t> rg2 = g.get_e_range(to);
            SortedSup s(i, to, g.compute_num_edge_intersect(rg1, rg2), j);
            m_sortSupE.push_back(s);
        }
    }
    sort(m_sortSupE.begin(),
         m_sortSupE.end(),
         [] (const SortedSup & a, const SortedSup & b) -> bool 
            { return a.m_eSup < b.m_eSup;} );

    // compute bin
    int32_t max_sup = m_sortSupE.back().m_eSup;
    m_bin.resize(max_sup+1);
    for(int32_t i=0; i<=max_sup; ++i)
    {
        m_bin[i] = (lower_bound(m_sortSupE.begin(), m_sortSupE.end(), SortedSup(i),
                   [] (const SortedSup & a, const SortedSup & b) -> bool
                      {return a.m_eSup < b.m_eSup;} ) - m_sortSupE.begin()); 
        if(m_sortSupE[m_bin[i]].m_eSup != i)
        {
            m_bin[i] = i==0 ? 0 : m_bin[i-1];
        }
    }

    // build edge index
    m_pos.resize(m_sortSupE.size(), 0);
    for (auto iter = m_sortSupE.begin(); iter != m_sortSupE.end(); ++iter)
    {
        m_pos[iter->m_eIdx] = iter - m_sortSupE.begin();
    }
}

bool TrussPlus::sup_e_opr(CSR &g, int32_t k, int32_t c)
{
    bool ret  = false;
    int start = m_bin[1];
    int end   = m_bin[k-1];
    while(end > start)
    {
        reduce_one_edge(g, m_sortSupE[start].m_vFrom, m_sortSupE[start].m_vTo);
        g.remove_e_by_v(m_sortSupE[start].m_vFrom, m_sortSupE[start].m_vTo);
        start++;
        end = m_bin[k-1];
        ret = true;
    }
    return ret;
}

void TrussPlus::reduce_one_edge(CSR & g, int32_t u, int32_t v, int32_t c)
{
    assert(u>=0 && u<g.get_num_v());
    assert(v>=0 && v<g.get_num_v());

    vector<int32_t> W = g.get_intersect_edges(u, v); 

    for(vector<int32_t>::iterator it = W.begin(); it != W.end(); ++it)
    {
        m_sortSupE[m_pos[*it]].m_eSup--;
    }

    pair<int32_t, int32_t> rg1 = g.get_e_range(u);
    for(int i=rg1.first; i<rg1.second; i++)
    {
        if(g.get_to_v(i) == v)
        {
            m_sortSupE[m_pos[i]].m_eSup = -1;
            break;
        }
    }

    pair<int32_t, int32_t> rg2 = g.get_e_range(v);
    for(int i=rg2.first; i<rg2.second; i++)
    {
        if(g.get_to_v(i) == u)
        {
            m_sortSupE[m_pos[i]].m_eSup = -1;
            break;
        }
    }
}
