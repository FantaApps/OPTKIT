/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Basic list implementation.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/02/15 - Creation
**/


#include "list.h"
#include "insknap.h"

//TODO need to change this hard code.
int parallel_mode = MODE_SEQ; 
extern int which_med;
int g_count;
bool control;

#define FILTER 4

/**
 * The constructor for list.
 *
 * @param[in]       b_size          bucket size
 * @param[in]       list_size       size of each bucket
 * @param[in]       b               base index
 * @param[in]       num_t           number of threads
 * @param[in]       is_u            compute based on upper bound
 * @param[in]       is_enumerate_a  unumerate all possible solutions
 *
**/
List::List(int32_t b_size, int32_t list_size, 
           int32_t b,      int32_t num_t, 
           bool is_u,      bool is_enumerate_a)
{
    content          = new T*[b_size];
    c_idx            = new int*[b_size];
    c_pos            = new int[b_size];    
    count            = new int*[num_threads];
	eliminate        = new bool*[num_threads];
    idx_sum          = new int*[num_threads];
	nei_score        = new int*[num_t];
	start            = new int*[num_threads];

	elim_idx         = new int[num_t*CACHE_FILL];
    num              = new int64_t[b_size];

    base             = b;
    buck_size        = b_size; 
    is_ub            = is_u;
    is_enumerate_all = is_enumerate_a;
	max_val          = 0;
	min_val          = 100000000;
	num_threads      = num_t;
	read_num         = 0;
	read_cnt         = 0;
	search_space     = 0;
	write_num        = 0;
	write_cnt        = 0;


    for(int i =0; i<num_threads; i++)
    {
        count[i]     = new int[b_size];
		eliminate[i] = new bool[LIST_SIZE*10]; 
		end[i]       = new int[b_size];
		idx_sum[i]   = new int[b_size+2];
		nei_score[i] = new int[LIST_SIZE*10]; 
		start[i]     = new int[b_size];
    }
	/* init values */
	for(int i=0; i<b_size; i++)
    {
        content[i] = new int[LIST_SIZE*num_elem];
        c_idx[i]   = new int[LIST_SIZE];
		num[i]          = 0;
		for(int j=0; j<num_t; j++)
        {
			count[j][i]   = 0;
			idx_sum[j][i] = 0;
			end[j][i]     = 0;
			start[j][i]   = 0;
		}
	}

	for(int i=0; i<10; i++)
    {
		time_elem e;
		t.list.push_back(e);
		t.init_timer(i);
	}
}


/**
 * The destructor.
 *
 * @return      N/A
**/
List::~List()
{
    for(int i=0; i<buck_size; ++i)
    {
        free(content[i]);
        free(c_idx[i]);
    }
    free(content);
    free(c_idx);
    free(c_pos);
    /* free original stuff */
    for(int i=0; i<num_threads; ++i)
    {
        free(count[i]);
        free(idx_sum[i]);
        free(end[i]);
        free(start[i]);
        free(eliminate[i]);
        free(nei_score[i]);
    }
    free(count);
    free(idx_sum);
    free(end);
    free(start);
    free(eliminate);
    free(nei_score);
    free(num);
    free(elim_idx);
}


