/*
 * =====================================================================================
 *
 *       Filename:  singleton.h
 *
 *    Description:  Singleton
 *
 *        Version:  1.0
 *        Created:  2016年04月09日 22时28分13秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <pthread.h>
#include <boost/noncopyable.hpp>

template <typename T>
class Singleton : public boost::noncopyable
{
public:
    static T& Instance()
    {
        pthread_once(&ponce_, &Singleton::Init);
        return *value_;
    }

private:
    Singleton();
    ~Singleton();
    
    static void Init()
    {
        value_ = new T();
    }

private:
    static pthread_once_t ponce_;
    static T* value_;
};

#endif //SINGLETON_H_

