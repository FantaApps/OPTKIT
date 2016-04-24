/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Some utility implementations.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   04/24/16 - Add check_create_dir 
 *  stplaydog   04/11/16 - instroduced vet to string and string to vec functions 
 *  stplaydog   08/02/15 - Creation
**/

#pragma once
#ifndef _H_UTILS
#define _H_UTILS

/**
 * Copy right YMSys, 2015, Zhaoming Yin
 *
 * @brief    This file includes some basic utility functions and definitions.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   08/01/15 - Creation
 *
**/


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <vector>
#include <glog/logging.h>
#include <boost/lexical_cast.hpp>
#include <sys/types.h>
#include <sys/stat.h>


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define red_p(cl, ...)   printf(RED); \
                printf(cl, ##__VA_ARGS__);\
                printf(RESET "\n")
#define blue_p(cl, ...)   printf(BLUE  ##__VA_ARGS__  RESET "\n")
#define ERROR_PRINT() {printf("Error on (%d) line in (%s) file\n", __LINE__, __FILE__); exit(123);}

#define OPTKIT_INVALID -1
/**
 *  @enum       GGPARAM_COMP
 *
 *  @brief      Component type that a parameter is applicable to.
 *
 *  @details    This is a one-2-one mapping of type tcomp in ggparam.xsd.
 *              It enumerates all OGG applications. GGPARAM_COMP and tcomp
 *              must stay in sync with actual applications in the OGG
 *              installation package. Each enum value is defined in a way
 *              so that they can used in a bit map, since parameters can
 *              to more than one component.
**/
typedef enum
{
    OPTKIT_NULL = -1,
    OPTKIT_ZERO = 0, 
    OPTKIT_FILE_SIZE = 512,
    OPTKIT_GTEST_SIZE = 100000 
}
OPTKIT_DEF;

#define OPTKIT_EDEA 0.595639
#define OPTKIT_EDEC 0.457748

using namespace std;


typedef vector<pair<int32_t, int32_t>>         edge_list;
typedef vector<vector<pair<int32_t, int32_t>>> edge_list_CC;

class Utils
{
public:
    static char *readLine(FILE *file);
    static int  str_split(char* a_str, const char a_delim, char **result);
    static void q_sort_two(int *key, int *val, int left, int right);
    static void q_sort(int *number, int left, int right);
    static void get_file_name(const char *full_path_name, char *file_name, int16_t size);
    static void get_file_name(const char *full_path_name, int16_t size1, char *file_name, int16_t size2);
    static void concate_path(const char *path, const char *full_path_name, int16_t size2, char* concated, int size3);
    static int  ede1(int invdist, int ngene);
    static vector<string> split(string &s, char delim);
    
    
    // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    static const string currentDateTime() 
    {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
        // for more information about date/time format
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }

    static void gtest_log_vector(const std::vector<int> &vec)
    {
        for(uint32_t i=0; i<vec.size(); ++i)
        {
            printf("%d ", vec[i]);
        }
        printf("\n");
    }


    template <typename T, typename L>
    static void vec_pair_to_string(const vector<pair<T, L>> &v, string &ret)
    {
        for(auto it = v.begin(); it != v.end(); )
        {
            auto cur = it++;
            if(it != v.end())
            {
                ret += to_string(cur->first) + "," + 
                       to_string(cur->second) + "\n";
            }
            else
            {
                ret += to_string(cur->first) + "," + 
                       to_string(cur->second);
            }
        }
    }

    template <typename T, typename L>
    static void vec_vec_pair_to_string(const vector<vector<pair<T, L>>> &v, string &ret)
    {
        for(auto it = v.begin(); it != v.end(); )
        {
            string tmp;
            auto cur = it++;
            if(it != v.end())
            {
                vec_pair_to_string<T, L>(*cur, tmp); 
                ret += tmp + "\n"; 
            }
            else
            {
                vec_pair_to_string<T, L>(*cur, tmp); 
                ret += tmp; 
            }
        }
    }

    template <typename T>
    static void vec_to_string(const vector<T> &v, string &ret)
    {
        for(auto it = v.begin(); it != v.end(); )
        {
            auto cur = it++;
            if(it != v.end())
            {
                ret += to_string(*cur) + ","; 
            }
            else
            {
                ret += to_string(*cur); 
            }
        }
    }

    template <typename T>
    static void vec_vec_to_string(const vector<vector<T>> &v, string &ret)
    {
        for(auto it = v.begin(); it != v.end(); )
        {
            string tmp;
            auto cur = it++;
            if(it != v.end())
            {
                vec_to_string<T>(*cur, tmp); 
                ret += tmp + "\n";
            }
            else
            {
                vec_to_string<T>(*cur, tmp); 
                ret += tmp;
            }
        }
    }

    template <typename T>
    static void string_to_vec(string &s, vector<T> &ret)
    {
        vector<string> val = split(s, ',');
        for(auto it = val.begin(); it != val.end(); ++it)
        {
            T  val = boost::lexical_cast<T>(*it); 
            ret.push_back(val);
        }
        
    }

    static int check_create_dir(const char *path)
    {
        struct stat info;

        if(stat( path, &info ) != 0)
            return 0;
        else if(info.st_mode & S_IFDIR)
            return 1;
        else
            return 0;
    }


    /**
     * @brief       used for sorting pairs
     *
     * @param[in]       e1          the first edge      
     * @param[in]       e2          the second edge      
     *
     * @return  true if e1 is smaller than e2
    **/
    static bool smaller(pair<int32_t, int32_t> e1, pair<int32_t, int32_t> e2)
    {
        if(e1.first < e2.first)
        {
            return true;
        }
        else if(e1.first == e2.first && e1.second <= e2.second)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif
