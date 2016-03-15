/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for BGL using boost graph library. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/14/16 - Add all pairs shortest path 
 *  stplaydog   03/13/16 - Creation
 *
**/

#pragma once
#ifndef _H_BGL
#define _H_BGL

#include "utils.h"
#include <algorithm>
#include <map>
#include "gtest/gtest_prod.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/exterior_property.hpp>
#include <boost/graph/clustering_coefficient.hpp>

using namespace boost;
using namespace std; 

// The Actor type stores the name of each vertex in the graph.
struct Actor
{
    string name;
};

typedef double                                      t_weight;
typedef property<edge_weight_t, double>             EdgeWeightProperty;
typedef adjacency_list<vecS, vecS, 
                       undirectedS, no_property, 
                       EdgeWeightProperty>          Adj;
typedef property_map<Adj, edge_weight_t>::type      WeightMap;
typedef exterior_vertex_property<Adj, t_weight>     DistanceProperty;
typedef DistanceProperty::matrix_type               DistanceMatrix;
typedef DistanceProperty::matrix_map_type           DistanceMatrixMap;
//typedef undirected_graph<Actor>                     Udir;
//typedef graph_traits<Udir>::vertex_descriptor       UVertex;
//typedef graph_traits<Udir>::edge_descriptor         Edge;
//typedef property_map<Udir, string Actor::*>::type   NameMap;
//typedef unsigned long                               t_indx;
//typedef exterior_vertex_property<Udir, float>       ClusteringProperty;
//typedef ClusteringProperty::container_type          ClusteringContainer;
//typedef ClusteringProperty::map_type                ClusteringMap;


/**
 * @class BGL 
 *
 * This class defines a BGL, using boost graph library to process some data; 
 *
**/
class BGL
{

    public:

        BGL(const char *in_file);

        BGL(vector<pair<int32_t, int32_t>> &edges)
        {
            for(auto it = edges.begin(); it != edges.end(); ++it)
            {
                add_edge(it->first, it->second, 1.0, m_adj);
                //add_edge(it->first, it->second, 1, m_udir);
            }
        }

        BGL() {};


        ~BGL() {};

    private:

        void floyd_warshall()
        {
            WeightMap weight_pmap = boost::get(boost::edge_weight, m_adj);

            DistanceMatrix    distances(num_vertices(m_adj));
            DistanceMatrixMap dm(distances, m_adj);

            bool valid = floyd_warshall_all_pairs_shortest_paths(m_adj,     dm, 
                                                                 weight_map(weight_pmap));
            if (!valid) 
            {
                ERROR_PRINT();
            }

        }

        //void clustering_coeff()
        //{
        //    // Create the graph and a name map that provides access to
        //    // then actor names.
        //    NameMap nm(get(&Actor::name, m_udir));

        //    ClusteringContainer coefs(num_vertices(m_udir));
        //    ClusteringMap cm(coefs, m_udir);
        //    float cc = all_clustering_coefficients(m_udir, cm);
        //    Stats::instance->set(CC, cc);
        //}

        //std::map<Vertex, std::map<Vertex, int> >     matrix;
        Adj                                          m_adj;
        //Udir                                         m_udir;

        FRIEND_TEST(InitGraphTest_2, Success);
};

#endif
