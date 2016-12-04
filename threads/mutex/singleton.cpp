/*
 * =====================================================================================
 *
 *       Filename:  singleton.cpp
 *
 *    Description:  Singleton
 *
 *        Version:  1.0
 *        Created:  2016年04月09日 22时34分42秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "singleton.h"

#include <pthread.h>

template <typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template <typename T>
T* Singleton<T>::value_ = NULL;
