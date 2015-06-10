// =====================================================================================
// 
//       Filename:  delegate_example.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  11/12/2014 02:19:10 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com
//        License:  Copyright © 2014 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#ifndef _DELEGATE_EXAMPLE_H__
#define _DELEGATE_EXAMPLE_H__

#include "delegate_example_imp.h"
////typename T0, typename T1, ..., typename Tn-1 
//#define DELEGATE_TEMPLATE_PARAMS BOOST_PP_ENUM_PARAMS(DELEGATE_NUM, typename T)
////T0 p0, T1 p1, ..., Tn-1 pn-1
//#define PARAMS(z, n, datat) BOOST_PP_CAT(T, n) BOOST_PP_CAT(p, n)
//#define DELEGATE_T_P_ARGS BOOST_PP_ENUM(DELEGATE_NUM, PARAMS, ' ')
////p0, p1, ..., pn-1
//#define DELEGATE_P_ARGS BOOST_PP_ENUM_PARAMS(DELEGATE_NUM, p)
////T0, T1, ..., Tn-1
//#define DELEGATE_T_ARGS BOOST_PP_ENUM_PARAMS(DELEGATE_NUM, T)
//
//#define DELEGATE_COMMA BOOST_PP_COMMA_IF(DELEGATE_NUM)

// 特例化 Delegate 
template <>
class Delegate<boost::function<void()> >:
public DelegateBase<boost::function<void()> >
{
public:
    void operator() ()
    {
        EVNET_ALL();
    }
};

template <typename T0>
class Delegate<boost::function<void(T0)> >:
public DelegateBase<boost::function<void(T0)> >
{
public:
    typedef typename DelegateBase<boost::function<void (T0)> >::ListContainer ListContainer;
    typedef typename DelegateBase<boost::function<void (T0)> >::ListContainerIter ListContainerIter;
    void operator() (T0 p0)
    {
        EVNET_ALL(p0);
    }
};

template <typename T0, typename T1>
class Delegate<boost::function<void(T0, T1)> >:
public DelegateBase<boost::function<void(T0, T1)> >
{
public:
    typedef typename DelegateBase<boost::function<void (T0, T1)> >::ListContainer ListContainer;
    typedef typename DelegateBase<boost::function<void (T0, T1)> >::ListContainerIter ListContainerIter;
    void operator() (T0 p0, T1 p1)
    {
        EVNET_ALL(p0, p1);
    }
};

template <typename T0, typename T1, typename T2>
class Delegate<boost::function<void(T0, T1, T2)> >:
public DelegateBase<boost::function<void(T0, T1, T2)> >
{
public:
    typedef typename DelegateBase<boost::function<void (T0, T1, T2)> >::ListContainer ListContainer;
    typedef typename DelegateBase<boost::function<void (T0, T1, T2)> >::ListContainerIter ListContainerIter;
    void operator() (T0 p0, T1 p1, T2 p2)
    {
        EVNET_ALL(p0, p1, p2);
    }
};

template <typename T0, typename T1, typename T2, typename T3>
class Delegate<boost::function<void(T0, T1, T2, T3)> >:
public DelegateBase<boost::function<void(T0, T1, T2, T3)> >
{
public:
    typedef typename DelegateBase<boost::function<void (T0, T1, T2, T3)> >::ListContainer ListContainer;
    typedef typename DelegateBase<boost::function<void (T0, T1, T2, T3)> >::ListContainerIter ListContainerIter;
    void operator() (T0 p0, T1 p1, T2 p2, T3 p3)
    {
        EVNET_ALL(p0, p1, p2, p3);
    }
};

#endif //_DELEGATE_EXAMPLE_H__


