/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for keeping global config 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   03/09/16 - Creation
 *
**/

#pragma once
#ifndef __H_CONFIG__
#define __H_CONFIG__


using namespace std;

/**
 * @class Config
 *
 * @note  This is class for keeping global configuration 
 *
**/
class Config 
{
    map<string, string> m_dic;
    static Config *s_instance;
    Config() {}
    
public:
    string get(const string &key)
    {
        return m_dic[key];
    }
    void set(const string &key, const string &val)
    {
        m_dic[key] = val;
    }

    static Config *instance()
    {
        if (!s_instance)
            s_instance = new Config;
        return s_instance;
    }
};

#endif
