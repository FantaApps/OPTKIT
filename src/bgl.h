/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for BGL using boost graph library. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/15/16 - Add clustering coefficient, betweeness centrality,
 *                         and all cliques algorithms. 
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
#include "Stats.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/exterior_property.hpp>
#include <boost/graph/clustering_coefficient.hpp>

#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/exterior_property.hpp>
#include <boost/graph/clustering_coefficient.hpp>
#include "../libs/helper.hpp"

#include <boost/graph/bc_clustering.hpp>
#include <boost/graph/iteration_macros.hpp>

#include <boost/graph/bron_kerbosch_all_cliques.hpp>

using namespace boost;
using namespace std; 


typedef double                                      t_weight;
typedef property<edge_weight_t, double>             EdgeWeightProperty;
typedef adjacency_list<vecS, vecS, 
                       undirectedS, no_property, 
                       EdgeWeightProperty>          Adj;
typedef property_map<Adj, edge_weight_t>::type      WeightMap;
typedef exterior_vertex_property<Adj, t_weight>     DistanceProperty;
typedef DistanceProperty::matrix_type               DistanceMatrix;
typedef DistanceProperty::matrix_map_type           DistanceMatrixMap;


struct Actor
{
    string name;
};
typedef undirected_graph<Actor>                     Udir;
typedef graph_traits<Udir>::vertex_descriptor       UVertex;
typedef graph_traits<Udir>::edge_descriptor         Edge;
typedef property_map<Udir, string Actor::*>::type   NameMap;
typedef unsigned long                               t_indx;
typedef exterior_vertex_property<Udir, float>       ClusteringProperty;
typedef ClusteringProperty::container_type          ClusteringContainer;
typedef ClusteringProperty::map_type                ClusteringMap;

struct EdgeProperties
{
      int weight;
};
typedef adjacency_list< setS, vecS, 
                        undirectedS, no_property, 
                        EdgeProperties >            Adj1;
typedef Adj1::vertex_descriptor                     Vertex1;
typedef Adj1::edge_descriptor                       Edge1;
typedef std::map<Edge1, int>                        StdEdgeIndexMap;
typedef associative_property_map< StdEdgeIndexMap > EdgeIndexMap;
typedef property_map< Adj1, vertex_index_t>::type   VertexIndexMap;
 

/**
 * @class BGL 
 *
 * This class defines a BGL, using boost graph library to process some data; 
 *
**/
class BGL
{
    template <typename OutputStream>
    struct clique_printer
    {
        clique_printer(OutputStream& stream)
            : os(stream)
        { }

        template <typename Clique, typename Graph>
            void clique(const Clique& c, const Graph& g)
            {
                typename Clique::const_iterator i, end = c.end();
                for(i = c.begin(); i != end; ++i) {
                    os << g[*i].name << ",";
                }
                os << endl;
            }
        OutputStream& os;
    };

    public:

        BGL(const char *in_file)
        {
        }

        BGL(vector<pair<int32_t, int32_t>> &edges)
        {
            NameMap nm(get(&Actor::name, m_udir));
            std::map<std::string, UVertex> verts;

            for(auto it = edges.begin(); it != edges.end(); ++it)
            {
                add_edge(it->first, it->second, 1.0, m_adj);

                string name1 = to_string(it->first);
                string name2 = to_string(it->second);
                if(verts.find(name1) == verts.end())
                {
                    add_named_vertex(m_udir, nm, name1, verts);
                }
                if(verts.find(name2) == verts.end())
                {
                    add_named_vertex(m_udir, nm, name2, verts);
                }

                add_edge(verts[name1], verts[name2], m_udir);

                add_edge(it->first, it->second, m_adj1);

            }
        }

        /**
         * @brief       Constructor and Destructor
         *
        **/
        BGL() {};
        ~BGL() {};

    private:

        /**
         *
         *
        **/
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

        /**
         *
         *
        **/
        void clustering_coeff()
        {
            ClusteringContainer coefs(num_vertices(m_udir));
            ClusteringMap cm(coefs, m_udir);
            float cc = all_clustering_coefficients(m_udir, cm);
           
            string val = to_string(cc); 
            Stats::instance()->write_content(Stats::CLUSTERCOEFF, val);
        }

        /**
         *
         *
        **/
        void betweeness_centrality()
        {
            StdEdgeIndexMap              my_e_index;
            EdgeIndexMap                 e_index(my_e_index);

            int i = 0;
            BGL_FORALL_EDGES(edge, m_adj1, Adj1)
            {
                my_e_index.insert(pair< Edge1, int >( edge, i));
                ++i;
            }

            vector< double > e_centrality_vec(num_edges(m_adj1), 0.0);
            iterator_property_map <vector<double>::iterator, EdgeIndexMap>
                                  e_centrality_map(e_centrality_vec.begin(), e_index);

            VertexIndexMap        v_index = get(vertex_index, m_adj1);
            vector<double>        v_centrality_vec(num_vertices(m_adj1), 0.0);
            iterator_property_map <vector< double >::iterator, VertexIndexMap >
                                  v_centrality_map(v_centrality_vec.begin(), v_index);

            brandes_betweenness_centrality( m_adj1, v_centrality_map, e_centrality_map );
        }

        /**
         *
         *
        **/
        void all_cliques()
        {
            clique_printer<ostream> vis(cout);
            bron_kerbosch_all_cliques(m_udir, vis);
        }

        Adj  m_adj;     ///<
        Adj1 m_adj1;    ///<
        Udir m_udir;    ///<

        FRIEND_TEST(InitGraphTest_2, Success);
};

#endif
