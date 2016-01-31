/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Basic list implementation.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   01/30/16 - Creation
**/


#pragma once


#ifndef __NODE_H__
#define __NODE_H__

using namespace std;

class Node 
{
public:
    Node() {};
    ~Node() {};

    virtual void serialize() = 0;
    virtual void deserialize() = 0;
};

#endif
