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

#include "utils.h"
#include <map>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;


/**
 * @class Config
 *
 * @note  This is class for keeping global configuration 
 *
**/
class Config 
{
public:
    static Config *instance()
    {
        if(!m_instance)
        {
            m_instance = new Config;
        }
        return m_instance;
    }

    void set(const string &key, const string &val)
    {
        m_params[key] = val;
    }

    string get(const string &key)
    {
        string ret;
        ret = m_params[key];
        return ret;
    }

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_params;
    }

    void clear()
    {
        m_params.clear();
    }


private:
    Config() {}

    static Config *     m_instance;

    map<string, string> m_params;
};



#endif
