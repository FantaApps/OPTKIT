/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This is the header of DCJ distance methods. 
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

    /**
     * @brief   Compute the support number of each edge
     *
     * @return  N/A
    **/
    void compute_sup()
    {
        for(int i=0; i<num_v; i++)
        {
            int start1 = i==0 ? 0 : v_idx[0][i-1];
            int end1   = v_idx[0][i];

            for(int j=start1; j<end1; j++)
            {
                int to = e_idx[0][j];
                int start2 = to==0 ? 0 : v_idx[0][to-1];
                int end2   = v_idx[0][to];
               
                // Using std to find intersection.
                // TODO, optimizing using O(1) space 
                vector<int> v((end1+end2)-(start1+start2));
                vector<int>::iterator it;
                it=std::set_intersection (e_idx[0]+start1, e_idx[0]+end1, 
                                          e_idx[0]+start2, e_idx[0]+end2, 
                                          v.begin());
                
                // Update the support value
                e_sup[0][j] = it-v.begin();
            }
        }
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

    /**
     * @brief   Get the termination condition for computing k -truss
     *
     * @return  true if not stop, else false.
    **/
    bool has_sup_k(int k)
    {
        for(int i=0; i<num_e; i++)
        {
            if(e_sup[0][i] > (k - 2))
            {
                return true;
            }
        }
        return false;
    }

    void sup_e_opr(int k)
    {
    }

    void reconstruct()
    {
    }
            
    
    void output_trusses(FILE *writer)
    {
    }

};

#endif
