/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for BGL using boost graph library. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/16/16 - Add code to initialize graph from file. 
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

#include <boost/algorithm/string.hpp>

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
                typename Clique::const_iterator i, cur, end = c.end();
                for(i = c.begin(); i != end; ) {
                    cur = i++;
                    if(i != end)
                    {
                        os << g[*cur].name << ",";
                    }
                    else
                    {
                        os << g[*cur].name; 
                    }
                }
                os << endl;
            }
        OutputStream& os;
    };

public:


    BGL(const char *in_file)
    {
        int32_t v_num = OPTKIT_NULL;
        int32_t e_num = OPTKIT_NULL;
        int32_t c_num = OPTKIT_NULL;
        int32_t v_id  = OPTKIT_NULL;
        int32_t v_to  = OPTKIT_NULL;
        int32_t color = OPTKIT_NULL;

        DLOG(INFO) << "Initiating BGL...";

        /* Read the head information, 
           and allocate according variables */
        FILE *reader;
        if((reader = fopen(in_file, "r")) == NULL)
        {
            printf("the file %s you input does not exist!\n", in_file);
            ERROR_PRINT();
        }
        else if(fscanf(reader, "%d %d %d\n", &v_num, &c_num, &e_num)==EOF)
        {
            ERROR_PRINT();
        }

        NameMap                   nm(get(&Actor::name, m_udir));
        map<std::string, UVertex> verts;
        /* Scan the real content */
        for(int32_t i=0;i<e_num;i++)
        {
            if(fscanf(reader, "%d %d %d\n",&v_id , &v_to, &color)==EOF)
            {
                ERROR_PRINT();
            }
            add_one_edge(v_id, v_to, nm, verts);
        }
    }

    BGL(const edge_list &edges)
    {
        NameMap                   nm(get(&Actor::name, m_udir));
        map<std::string, UVertex> verts;

        for(auto it = edges.begin(); it != edges.end(); ++it)
        {
            add_one_edge(it->first, it->second, nm, verts);
        }
    }

    /**
     * @brief       Constructor and Destructor
     *
    **/
    BGL() {};
    ~BGL() {};

    Adj  get_adj() {return m_adj;}     ///< Adjacency graph
    Adj1 get_adj1() {return m_adj1;}    ///< Another adj graph
    Udir get_udir() {return m_udir;}    ///< undirected graph

private:

    void add_one_edge(int32_t v_from, int32_t v_to, NameMap &nm, map<std::string, UVertex> &verts)
    {
        add_edge(v_from, v_to, 1.0, m_adj);

        string name1 = to_string(v_from);
        string name2 = to_string(v_to);
        if(verts.find(name1) == verts.end())
        {
            add_named_vertex(m_udir, nm, name1, verts);
        }
        if(verts.find(name2) == verts.end())
        {
            add_named_vertex(m_udir, nm, name2, verts);
        }

        add_edge(verts[name1], verts[name2], m_udir);

        add_edge(v_from, v_to, m_adj1);
    }

    /**
     * @brief       This function is used to calculate all pairs shortest path
     *              Which is used for calculating diameter of a graph.
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

        int32_t diameter = 0;
        for (size_t i = 0; i < num_vertices(m_adj); ++i) 
        {
            for (size_t j = i; j < num_vertices(m_adj); ++j) 
            {
                diameter = max(diameter, (int32_t)distances[i][j]);
            }
        }
        string val = to_string(diameter);
        Stats::instance()->write_content(Stats::DIAMETER, val);
    }

    /**
     * @brief       This function is used to calculate clustering coefficient.
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
     * @brief       This function is used to calculate betweeness centrality.
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
        
        string val;
        Utils::vec_to_string<double>(v_centrality_vec, val);
        Stats::instance()->write_content(Stats::BETWEENCENTRL, val);
    }

    /**
     * @brief       This function is used to list all cliques.
    **/
    void all_cliques()
    {
        stringstream ss;
        clique_printer<stringstream> vis(ss);
        bron_kerbosch_all_cliques(m_udir, vis);
        string val = ss.str();
        trim_right(val);
        vector<string> strs;
        split(strs, val, is_any_of("\n"));
        map<int, int> count;

        for(auto lit = strs.begin(); lit != strs.end(); lit++)
        {
            vector<string> vets;
            split(vets, *lit, is_any_of(","));
            count[vets.size()]++;
        }

        for(auto it = count.begin(); it != count.end(); ++it)
        {
            string one_val = to_string(it->first) + "," + to_string(it->second);
            Stats::instance()->write_content(Stats::CLIQUE, one_val);
        }
    }

    template < typename Graph> 
    void print_dependencies(ostream & out, const Graph & g)
    {
        out<<"graph{"<<endl;
        typename graph_traits < Graph >::edge_iterator ei, ei_end;
        for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        {
            out << source(*ei, g) << " -> "
                << target(*ei, g) << ";"<< endl;
        }
        out << "}" <<endl;
    }

    template < typename Graph> void
    print_udependencies(std::ostream & out, const Graph & g)
    {
        out<<"graph{"<<endl;
        NameMap  nm(get(&Actor::name, m_udir));
        typename graph_traits < Graph >::edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        {
            out << get(nm, source(*ei, g)) << " -> "
                << get(nm, target(*ei, g)) <<";" <<endl;
        }
        out << "}" <<endl;
    }

    Adj  m_adj;     ///< Adjacency graph
    Adj1 m_adj1;    ///< Another adj graph
    Udir m_udir;    ///< undirected graph

    FRIEND_TEST(BGLInitGraph_1,     Success);
    FRIEND_TEST(BGLGraphProperty_1, Success);
    FRIEND_TEST(BGLInitGraph_2,     Success);
    FRIEND_TEST(BGLGraphProperty_2, Success);
    FRIEND_TEST(BGLSTModel_1,       Success);
};

#endif
