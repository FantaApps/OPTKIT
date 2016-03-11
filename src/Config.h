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

#include "../libs/Parser.h"

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

    void set(const string &key, const string &val);
    string get(const string &key);


private:
    Config() {}
    
    static Config * m_instance;

};

#endif
