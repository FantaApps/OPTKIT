/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This is the class for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   12/08/15 - Implemented compute support 
 *  stplaydog   09/03/15 - Creation
 *
**/

#pragma once
#ifndef _H_CSR
#define _H_CSR

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

    typedef pair<int32_t, int32_t> e_range;

    /**
     *
     * @note    edge list has to be sorted.
    **/
    int32_t compute_num_edge_intersect(int32_t start1, int32_t end1, 
                                       int32_t start2, int32_t end2,
                                       int32_t c = 0)
    {
        int32_t ret = 0;
        int32_t i(start1), j(start2);
        while(i<end1 && j<end2)
        {
            if(e_idx[c][i] == e_idx[c][j])
            {
                ++ret;
            }
            else if(e_idx[c][i] > e_idx[c][j])
            {
                ++j;
            }
            else
            {
                ++i;
            }
        }
        return ret;
    }

    
    /**
     * @return  number of vertices 
    **/
    int32_t get_num_v()
    {
        return num_v;
    }

    /**
     * @return  number of edges 
    **/
    int32_t get_num_e()
    {
        return num_e;
    }

    int32_t get_to_v(int32_t pos, int c = 0)
    {
        return e_idx[c][pos];
    }

    void set_rmvd(int32_t pos, int c = 0)
    {
        e_idx[c][j] = RMVD;
    }

    /**
     * @brief   Reconstruct the graph, because some edges has been removed.
     *
     * @return  N/A
    **/
    void reconstruct(int c = 0)
    {
        assert(c < num_c);

        /* update v_idx */
        int32_t *prefix_sum = new int[num_v];
        int32_t sum = 0; 

        for(int i=0; i<v_idx; i++)
        {
            int32_t start = get_start(i);
            int32_t end   = get_end(i);
            int32_t count = 0;

            for(int32_t j=start; j<end; ++j)
            {
                if(e_idx[c][j] != RMVD)
                {
                    ++count;
                }
            }

            sum += count;

            prefix_sum[i] = sum;
        }

        memcpy(v_idx, prefix_sum, num_v);

        delete [] prefix_sum;

        /* moving elements in e_idx */
        int cur=0, nxt=0;
        while(nxt < num_e)
        {
            if(e_idx[j] == RMVD) 
            {
                ++nxt;
            }
            else
            {
                e_idx[cur] = e_idx[nxt];
                e_sup[cur] = e_sup[nxt];
                ++cur;
                ++nxt;
            }
        }
    }

    /**
     * @brief   output the truss as connected components
     *
     * @param[in]       writer      the file which is going to be written
     *
     * @return      N/A
     **/
    void output_all_CC(FILE *writer, int c = 0)
    {
        assert(c < num_c);
        assert(writer  != NULL);

        int count = 0;
        for(int i=0; i<num_v; i++)
        {
            if(!visited[i])
            {
                fprintf(writer, "Comp [%d] :", count++);
                output_one_CC(writer, i, visited, c);
                fprintf(writer, "\n");
            }
        }
    }

    pair<int32_t, int32_t> get_e_range(int32_t v, int32_t c = 0)
    {
        pair<int32_t, int32_t> ret;
        ret.first  = v == 0 ? 0 : v_idx[c][v-1];
        ret.second = v_idx[c][v];
        return ret;
    }

private:

    int32_t num_v;   ///< total number of vertices 
    int32_t num_e;   ///< total number of edges
    int32_t num_c;   ///< number of colors 
                     ///< (different edges have differen colors)
    int32_t **v_idx; ///< vertex index for CSR
    int32_t **e_idx; ///< edge index for CSR

    /**
     * @recursive algorithm to output a specific CC.
     *
     * @param[in]       writer      the file which is going to be written
     * @param[in]       v           the seed vertex 
     * @param[in]       visited     indicate which vertex has been visited
     *
     * @return      N/A
     **/
    void output_one_CC(FILE *writer, int32_t v, bool *visited, int c = 0)
    {
        assert(c < num_c);
        assert(writer  != NULL);
        assert(visited != NULL);
        assert(v > 0 && v < num_v);

        if(!visited[v])
        {
            fprintf(writer, "%d ", v);
            visited[v] = true;
        }
        else
        {
            return;
        }

        int32_t start = get_start(v);
        int32_t end   = get_end(v);
        for(int i=start; i<end; ++i)
        {
            output_one_CC(writer, e_idx[c][j], visited);
        }
    }
};

#endif
