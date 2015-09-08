/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This is the header of DCJ distance methods. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   09/03/15 - Creation
 *
**/

#pragma once
#ifndef _H_TRUSS
#define _H_TRUSS



/**
 * @class Truss 
 *
 * This class calculate the DCJ distance between two genomes
 * with unequal contents.
 *
**/
class InsDis : public Instance {
public:
    void truss_decomosition(CSR &g)
    {
        g.compute_sup();
        int k = 3;
        while(g.get_num_e()>0)
        {
            ++k;
        }
    }
};

#endif
