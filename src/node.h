/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 *  @brief    Basic list implementation.
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   01/31/16 - defined the interface. 
 *  stplaydog   01/30/16 - Creation
**/


#pragma once


#ifndef __NODE_H__
#define __NODE_H__

using namespace std;

/**
 * @interface   for a representation of a search node that can be 
 *              serialized or deserialized.
 *
**/
template <class T>
class Node 
{
public:
    Node() {};
    ~Node() {};

    virtual void serialize(T* buf, int32_t &idx) = 0;
    virtual void deserialize(T* buf, int32_t &idx) = 0;
    virtual void get_encode_size() = 0;
};

#endif
