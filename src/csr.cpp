/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the implementation for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/04/16 - Fixed a bug that graph does not have a reverse
 *                         mapping. 
 *  stplaydog   02/19/16 - Fixed a bug of uninitialized array (visited) 
 *  stplaydog   02/14/16 - Fixed a bug in allocate_data_structure 
 *  stplaydog   02/13/16 - Creation
 *
**/

#include "csr.h"
#include "Config.h"
#include "Stats.h"
#include "utils.h"
#include "bgl.h"
#include <queue>


/**
 * @brief   This is the constructor
 *
 * @param[in]   in_file         graph file to read 
 *
 * @return      N/A
**/
CSR::CSR(const char *in_file)
{
    int32_t v_num = OPTKIT_NULL;
    int32_t e_num = OPTKIT_NULL;
    int32_t c_num = OPTKIT_NULL;
    int32_t v_id  = OPTKIT_NULL;
    int32_t v_to  = OPTKIT_NULL;
    int32_t color = OPTKIT_NULL;
    int32_t sum   = 0;

    LOG(INFO) << "Initiating CSR...";

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

    int32_t start_read_pos = ftell(reader);

    allocate_data_structure(v_num, e_num, c_num);

    /* Scan the real content */
    for(int32_t i=0;i<e_num;i++)
    {
        if(fscanf(reader, "%d %d %d\n",&v_id , &v_to, &color)==EOF)
        {
            ERROR_PRINT();
        }
        ++v_idx[color][v_id];
    }

    for(int32_t c=0; c<num_c; c++)
    {
        sum = 0;
        for(int32_t i=0; i<v_num; i++)
        {
            sum += v_idx[c][i];
            v_idx[c][i]=sum;
        }
    }

    /* Populate the content */
    fseek (reader, start_read_pos, SEEK_SET);

    /* this is for the start of the different postitions */
    int32_t *idx = new int32_t[num_v+1];

    for(int32_t c=0; c<num_c; c++)
    {
        for(int32_t i=0; i<num_v; i++)
        {
            idx[i] = i == 0 ? 0 : v_idx[c][i-1];
        }

        /* Real read part */
        for(int32_t i=0; i<num_e; i++)
        {
            if(fscanf(reader, "%d %d %d\n",&v_id , &v_to, &color)==EOF)
            {
                ERROR_PRINT();
            }

            int32_t pos = idx[v_id];
            e_idx[c][pos] = v_to;
            ++idx[v_id];
        }

        /* e_idx also needs to be sorted, for the purpose of join operations */
        for(int32_t i=0; i<num_v; i++)
        {
            pair<int32_t, int32_t> rg = get_e_range(i);
            sort(e_idx[c]+rg.first, e_idx[c]+rg.second);
        }
    }

    /* Frees */
    delete [] idx;
    fclose(reader);

    LOG(INFO) << "Finished initializing CSR";
}

/**
 * @brief   This is the constructor
 *
 * @param[in]   edges         edge list 
 *
 * @return      N/A
**/
CSR::CSR(vector<pair<int32_t, int32_t>> &edges)
{
    LOG(INFO) << "Sorting edges, number of edges is: "<<edges.size();

    sort(edges.begin(), edges.end(), Utils::smaller);

    map<int32_t, int32_t> count;
    num_e = edges.size();
    num_v = 0;
    for(uint32_t i=0; i<edges.size(); i++)
    {
        int32_t v_origin = edges[i].first;
        if(dic.find(v_origin) == dic.end())
        {
            dic[v_origin]  = num_v;
            rev_dic[num_v] = v_origin;
            num_v++;
        }
        count[dic[v_origin]]++;
    }

    LOG(INFO) << "Allocating data structure..";
    allocate_data_structure(num_v, num_e);

    LOG(INFO) << "Computing prefix sum..";
    int sum = 0;
    for(int32_t i=0; i<num_v; i++)
    {
        sum += count[i]; 
        v_idx[0][i] = sum;
    }
    
    LOG(INFO) << "Putting edge index..";
    for(uint32_t i=0; i<edges.size(); ++i)    
    {
        e_idx[0][i] = dic[edges[i].second];
    }
}

/**
 * @brief   Destrutor
**/
CSR::~CSR()
{
    for(int c=0; c<num_c; c++)
    {
        delete [] v_idx[c];
        delete [] e_idx[c];
    }

    delete [] v_idx;
    delete [] e_idx;
}

/**
 * Allocate memory for basic graph data structures. 
 *
 * @param[in]       v_num       number of vertices
 * @param[in]       e_num       number of edges 
 * @param[in]       _num        number of colors 
 *
 * @return      N/A
**/
void CSR::allocate_data_structure(const int32_t v_num, 
                                  const int32_t e_num, 
                                  const int32_t c_num)
{
    num_v = v_num;
    num_e = e_num;
    num_c = c_num;

    v_idx = new int32_t*[num_c];
    e_idx = new int32_t*[num_c];

    for(int32_t c=0; c<num_c; c++)
    {
        v_idx[c] = new int32_t[num_v];
        e_idx[c] = new int32_t[num_e];
        memset(v_idx[c], 0, num_v * sizeof(int32_t));
        memset(e_idx[c], 0, num_e * sizeof(int32_t));
    }
}

/**
 * @brief   compute the number of intersect edges between two vertices
 *
 * @param[in]       rg1         range of the first vertex
 * @param[in]       rg2         range of the second vertex
 * @param[in]       c           which color
 *
 * @return      number of intersections
 *
 * @note    edge list has to be sorted.
 **/
int32_t CSR::compute_num_edge_intersect(pair<int32_t, int32_t> rg1,
        pair<int32_t, int32_t> rg2,
        int32_t c)
{
    int32_t ret = 0;
    int32_t i(rg1.first), j(rg2.first);
    while(i<rg1.second && j<rg2.second)
    {
        if(e_idx[c][i] == RMVD)
        {
            i++;
        }
        if(e_idx[c][j] == RMVD)
        {
            j++;
        }
        if(e_idx[c][i] == e_idx[c][j])
        {
            ++ret;
            ++i;
            ++j;
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
 * @brief   get a list of actual intersect edges between two vertices 
 *
 * @param[in]       u           one vertex id
 * @param[in]       v           another vertex id
 * @param[in]       c           which color
 *
 * @return      List of intersected edges.
 *
 * @note    edge list has to be sorted.
**/
vector<int32_t> CSR::get_intersect_edges(int32_t u, int32_t v,
                                         int32_t c)
{
    assert(u>=0 && u<get_num_v());
    assert(v>=0 && v<get_num_v());

    vector<int32_t> ret;
    vector<int32_t> vto;

    /* process from edges */
    pair<int32_t, int32_t> rg1 = get_e_range(u);
    pair<int32_t, int32_t> rg2 = get_e_range(v);

    int32_t i(rg1.first), j(rg2.first);

    while(i<rg1.second && j<rg2.second)
    {
        if(e_idx[c][i] == RMVD)
        {
            i++;
        }
        if(e_idx[c][j] == RMVD)
        {
            j++;
        }
        if(e_idx[c][i] == e_idx[c][j])
        {
            if(e_idx[c][i] != RMVD)
            {
                ret.push_back(i);
                ret.push_back(j);
                vto.push_back(e_idx[c][i]);
            }
            ++i;
            ++j;
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

    /* process to edges */
    for(vector<int32_t>::iterator it = vto.begin(); it != vto.end(); ++it)
    {
        pair<int32_t, int32_t> rg = get_e_range(*it);
        for(int i = rg.first; i<rg.second; i++)
        {
            if(e_idx[c][i] == u || e_idx[c][i] == v)
            {
                ret.push_back(i);
            }
        }
    }

    return ret;
}


/**
 * @brief   get number of vertices
 *
 * @return  number of vertices 
**/
int32_t CSR::get_num_v()
{
    return num_v;
}

/**
 * @brief   get number of edges 
 *
 * @return  number of edges 
**/
int32_t CSR::get_num_e()
{
    return num_e;
}

/**
 * @brief   get number of colors 
 *
 * @return  number of colors 
**/
int32_t CSR::get_num_c()
{
    return num_c;
}

/**
 * @brief       get vertex being pointed to
 *
 * @param[in]       pos         which position
 * @param[in]       c           which color
 *
 * @return      pointed vertex
**/
int32_t CSR::get_to_v(int32_t pos, int32_t c)
{
    return e_idx[c][pos];
}

/**
 * @brief   given from and to vertex, search the according edge index
 *
 * @param[in]       from        from vertex
 * @param[in]       to          to vertex
 * @paran[c]        c           which color
 *
 * @return      index
**/
int32_t CSR::search_e(int32_t from, int32_t to, int32_t c)
{
    pair<int32_t, int32_t> rg1 = get_e_range(from);
    int32_t ret = Utils::bsearch(e_idx[c] + rg1.first, 
                                 rg1.second - rg1.first, to); 
    return ret == -1 ? -1 : ret+rg1.first;
}

/**
 * @brief   Reconstruct the graph, because some edges has been removed.
 *
 * @param[in]       c           which color
 *
 * @return  N/A
**/
void CSR::reconstruct(int32_t c)
{
    assert(c < num_c);

    /* update v_idx */
    int32_t *prefix_sum = new int32_t[num_v];
    memset(prefix_sum, 0, num_v * sizeof(int32_t));
    int32_t sum = 0; 

    for(int32_t i=0; i<num_v; i++)
    {
        int32_t count = 0;

        pair<int32_t, int32_t> rg = get_e_range(i, c);
        for(int32_t j=rg.first; j<rg.second; ++j)
        {
            if(e_idx[c][j] != RMVD)
            {
                ++count;
            }
        }

        sum += count;

        prefix_sum[i] = sum;
    }

    memcpy(v_idx[c], prefix_sum, num_v * sizeof(int32_t));

    delete [] prefix_sum;

    /* moving elements in e_idx */
    int32_t cur=0, nxt=0;
    while(nxt < num_e)
    {
        if(e_idx[c][nxt] == RMVD) 
        {
            ++nxt;
        }
        else
        {
            e_idx[c][cur] = e_idx[c][nxt];
            ++cur;
            ++nxt;
        }
    }
    num_e = cur;
}

/**
 * @brief       Remove one edge
 *
 * @param[in]       from        from vertex
 * @param[in]       to          to vertex
 * @param[in]       c           which color
 *
 * @return      Ture if there is such an edge to be removed
 *              else return false.
**/
bool CSR::remove_e_by_v(int32_t from, int32_t to, int c)
{
    int8_t find = 0;
    pair<int32_t, int32_t> rg_from = get_e_range(from, c); 
    pair<int32_t, int32_t> rg_to   = get_e_range(to, c); 

    for(int32_t i=rg_from.first; i<rg_from.second; ++i)
    {
        if(e_idx[c][i] == to)
        {
            e_idx[c][i] = RMVD;
            ++find;
            break;
        }
    }

    for(int32_t i=rg_to.first; i<rg_to.second; ++i)
    {
        if(e_idx[c][i] == from)
        {
            e_idx[c][i] = RMVD;
            ++find;
            break;
        }
    }

    if(find == 2)
        return true;
    return false;
}

bool CSR::remove_v(int32_t v, int c)
{
    pair<int32_t, int32_t> rg_from = get_e_range(v, c); 
    for(int32_t i=rg_from.first; i<rg_from.second; ++i)
    {
        pair<int32_t, int32_t> rg_to = get_e_range(e_idx[c][i], c); 
        for(int32_t j=rg_to.first; j<rg_to.second; ++j)
        {
            if(e_idx[c][j] == v)
            {
                e_idx[c][j] = RMVD;
                break;
            }
        }
        e_idx[c][i] = RMVD;
    }
    return true;
}

/**
 * @brief       Remove one edge
 *
 * @param[in]       e_id        which e
 * @param[in]       c           which color
 *
 * @return      Ture if there is such an edge to be removed
 *              else return false.
**/
bool CSR::remove_e_by_eidx(int32_t e_id, int c)
{
    if(e_id < num_e)
    {
        e_idx[c][e_id] = -1;
        return true;
    }
    return false;
}


/**
 * @brief   output the truss as connected components
 *
 * @param[in]       writer      the file which is going to be written
 * @param[in]       c           which color
 *
 * @return      N/A
**/
void CSR::output_all_CC(FILE *writer, bool with_edge, int32_t c)
{
    assert(c < num_c);
    assert(writer  != NULL);

    bool *visited = new bool[num_v];
    memset(visited, false, num_v * sizeof(bool));

    int32_t count = 0;
    for(int32_t i=0; i<num_v; i++)
    {
        pair<int32_t, int32_t> rg = get_e_range(i, c);
        if(!visited[i] && (!with_edge || rg.first < rg.second))
        {
            fprintf(writer, "Comp [%d] : ", count++);
            int32_t cnt = 0;
            double  coe = 0.0;
            output_one_CC(writer, i, visited, cnt, coe, c);
            fprintf(writer, "\n");

            string kcomp;
            kcomp = Config::instance()->get("kcomp") + "," + to_string(cnt) + "," + to_string(coe);

            if(Config::instance()->get("comp") == "ktruss")
            {
                Stats::instance()->write_content(Stats::TRUSS, kcomp); 
            }
            else if(Config::instance()->get("comp") == "kcore")
            {
                Stats::instance()->write_content(Stats::CORE, kcomp); 
            }
            else if(Config::instance()->get("comp") == "dbscan")
            {
                Stats::instance()->write_content(Stats::DBSCAN, kcomp); 
            }
        }
    }

    delete [] visited;
}

/**
 * @brief   get the range of e_idxs from a given vertex
 *
 * @param[in]       v           given vertex
 * @param[in]       c           which color
 *
 * @return      the range
 *
**/
pair<int32_t, int32_t> CSR::get_e_range(int32_t v, int32_t c)
{
    pair<int32_t, int32_t> ret;
    ret.first  = v == 0 ? 0 : v_idx[c][v-1];
    ret.second = v_idx[c][v];
    return ret;
}

/**
 * @brief   visualize CSR using graphviz format
**/
void CSR::visualize()
{
    FILE *writer = fopen("./csr.dot", "w");
    fprintf(writer, "graph{\n");
    for(int c=0; c<num_c; c++)
    {
        char *color;
        if(c==0)
        {
            color = (char*)"red";
        }
        if(c==1)
        {
            color = (char*)"blue";
        }
        if(c==2)
        {
            color = (char*)"green";
        }
        for(int i=0; i<num_v; i++)
        {
            pair<int32_t, int32_t> rg = get_e_range(i);
            for(int j=rg.first; j<rg.second; j++)
            {
                if(e_idx[c][j] != -1)
                {
                    fprintf(writer, "%d -- %d [color=%s];\n", i, e_idx[c][j], color);
                }
            }
        }
    }
    fprintf(writer, "}\n");
    fclose(writer);
}

/**
 * @recursive algorithm to output a specific CC.
 *
 * @param[in]       writer      the file which is going to be written
 * @param[in]       v           the seed vertex 
 * @param[in]       visited     indicate which vertex has been visited
 * @param[out]      cnt         num of vertices in this CC
 * @param[out]      coe         clustering coefficient of the CC 
 * @param[in]       c           which color 
 *
 * @return      N/A
**/
void CSR::output_one_CC(FILE *writer, int32_t v,    bool *visited, 
                        int32_t &cnt, double & coe, int32_t c)
{
    assert(c < num_c);
    assert(writer  != NULL);
    assert(visited != NULL);
    assert(v >= 0 && v < num_v);

    std::queue<int32_t> q;
    q.push(v);
    edge_list el;

    while(!q.empty())
    {
        int32_t u = q.front();
        q.pop();
        if(!visited[u])
        {
            if(!rev_dic.size())
            {
                fprintf(writer, "%d ", u);
            }
            else
            {
                fprintf(writer, "%d ", rev_dic[u]);
            }

            pair<int32_t, int32_t> rg = get_e_range(u);
            for(int32_t i=rg.first; i<rg.second; ++i)
            {
                q.push(e_idx[c][i]);
                el.push_back(pair<int32_t, int32_t>(u, e_idx[c][i]));
            }

            cnt++;
            visited[u] = true;
        }
    }

    BGL g(el);
    g.one_cluster_coef();
}
