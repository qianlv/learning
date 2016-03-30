/*
 * =====================================================================================
 *
 *       Filename:  thread_attr.h
 *
 *    Description:  线程属性
 *
 *        Version:  1.0
 *        Created:  2016年03月30日 14时09分36秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef THREAD_ATTR_H_
#define THREAD_ATTR_H_

int makethread(void *(*fn)(void *), void *arg);

#endif // THREAD_ATTR_H_
