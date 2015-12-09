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
        g.compute_sup();
        while(g.get_num_e() > 0)
        {
            while(g.has_sup_k(k))
            {
                sup_e_opr(k);
            }
            reconstruct();
            output_trusses(writer);
            ++k;
        }

        fclose(writer);
    }
};

#endif
