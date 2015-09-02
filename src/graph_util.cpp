/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 *  @brief    Implementation of graph utilies.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/08/15 - Implement graph read and CC.
 *  stplaydog   08/07/15 - Creation
**/


#include "graph_util.h"
#include <iostream>

/**
 * @brief   Read the graph into an edge list.
 *
 * @param[in]       file        File to read the graph.
 * @param[in]       graph       The edge list representation of the graph.
 *
 * @return      N/A
**/
void GraphUtils::init_adj(const char* file, Adj& g)
{
    int32_t num_v = OPTKIT_ZERO;
    int32_t num_e = OPTKIT_ZERO;
    int32_t num_c = OPTKIT_ZERO;

    int32_t v_from  = OPTKIT_NULL;
    int32_t v_to    = OPTKIT_NULL;
    int32_t e_color = OPTKIT_NULL;

    FILE *reader = fopen(file, "r");
    if(reader == NULL)
    {
        fprintf(stderr, "The file %s does not exsits.");
        ERROR_PRINT();
    }
    
    /* Read the general information of the graph. */
    fscanf(reader, "%d %d %d\n", &num_v, &num_e, &num_c);
    
    /* Read each edge of the graph. */
    for(int i=0; i<num_e; ++i)
    {
        fscanf(reader, "%d %d %d\n", &v_from, &v_to, &e_color);
        add_edge(v_from, v_to, g);
    }

    fclose(reader);
}

/**
 * @brief   Read the graph into an edge list.
 *
 * @param[in]       file        File to read the graph.
 * @param[in]       graph       The edge list representation of the graph.
 *
 * @return      N/A
**/
void GraphUtils::init_udi(const char* file, Udi& g)
{
    int32_t num_v = OPTKIT_ZERO;
    int32_t num_e = OPTKIT_ZERO;
    int32_t num_c = OPTKIT_ZERO;

    int32_t v_from  = OPTKIT_NULL;
    int32_t v_to    = OPTKIT_NULL;
    int32_t e_color = OPTKIT_NULL;

    FILE *reader = fopen(file, "r");
    if(reader == NULL)
    {
        fprintf(stderr, "The file %s does not exsits.");
        ERROR_PRINT();
    }
    
    /* Read the general information of the graph. */
    fscanf(reader, "%d %d %d\n", &num_v, &num_e, &num_c);
    
    /* Read each edge of the graph. */
    for(int i=0; i<num_e; ++i)
    {
        fscanf(reader, "%d %d %d\n", &v_from, &v_to, &e_color);
        //g.add_edge(v_from, v_to, g);
    }

    fclose(reader);
}

/**
 * @brief   a wrapper for connected components.
 *
 * @param[in]       file        file to read graph.
 * @param[in]       output_dir  folder to output components.
 *
 * @return      N/A.
**/
void GraphUtils::connected_comps(const char* file, const char* output_dir)
{
   /* Init graph*/
   Adj g;
   init_adj(file, g);

   /* Compute connected components */
   std::vector<int> component(num_vertices(g));
   int num = connected_components(g, &component[0]);

#ifdef USE_GTEST
   Utils::gtest_log_vector(component);
#endif
   /* Print stats. */

   /* Write to file */
}

/**
 * @brief   a wrapper for listing all cliques.
 *
 * Based on this example:
 * http://www.boost.org/doc/libs/1_55_0/libs/graph/example/bron_kerbosch_print_cliques.cpp
 * http://www.math.ucla.edu/~mbshort/papers/crime2.pdf
 *
**/
void GraphUtils::all_cliques(const char* file, const char* output_dir)
{
    Adj a;
    init_adj(file, a);
    //Udi g(a);
    clique_printer<ostream> vis(std::cout);
//    bron_kerbosch_all_cliques(a, vis);
}

void GraphUtils::adjacency_list_to_file(const char* file)
{
    
}

void GraphUtils::k_truss(const char* file, const char* output_dir)
{

}

