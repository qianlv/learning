// =====================================================================================
// 
//       Filename:  delegate_example.h
// 
//    Description:  委托实现实例
// 
//        Version:  1.0
//        Created:  11/11/2014 02:09:41 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com
//        License:  Copyright © 2014 肖守冬. All Rights Reserved.
// 
// =====================================================================================
//
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <list>



#ifndef __DELEGATE_EXAMPLE_IMP_H__
#define __DELEGATE_EXAMPLE_IMP_H__

//T是boost::function类型
template <typename T>
class DelegateBase
{
public:
    typedef T DelegateType;
    typedef std::list<DelegateType> ListContainer;
    typedef typename ListContainer::iterator ListContainerIter;

    inline void add(DelegateType ptr)
    {
        //if(contains(ptr))
        //    return;
        std::cout << "添加成功" << std::endl;
        my_list_func.push_back(ptr);
    }
    inline void remove(DelegateType ptr)
    {
        my_list_func.remove(ptr);
    }
    inline void operator +=(DelegateType ptr)
    {
        add(ptr);
    }
    inline void operator -=(DelegateType ptr)
    {
        remove(ptr);
    }
    inline operator bool()
    {
        if(my_list_func.size())
        {
            std::cout << my_list_func.size() << std::endl;
            return true;
        }
        return false;
    }
protected:
    DelegateBase(){}
    virtual ~DelegateBase()
    {
        my_list_func.clear();
    }
    inline bool contains(DelegateType ptr)
    {
        for(ListContainerIter iter = my_list_func.begin();
            iter != my_list_func.end(); ++iter)
        {
            if (*iter == ptr) return true;
        }
        return false;
    }
protected:
    ListContainer my_list_func;
};

#define EVNET_ALL(...)                                      \
    {                                                       \
        ListContainer my_list_func = this->my_list_func;    \
        for(ListContainerIter iter = my_list_func.begin();  \
            iter != my_list_func.end(); ++iter)             \
        {                                                   \
            (*iter)(__VA_ARGS__);                       \
        }                                                   \
    }
//声明Delegate, 根据函数指针类型特例化
template<typename T>
class Delegate{};

#endif //__DELEGATE_EXAMPLE_IMP_H__

