// =====================================================================================
// 
//       Filename:  simple_delegate1.cpp
// 
//    Description:  普通函数委托
// 
//        Version:  1.0
//        Created:  11/08/2014 04:31:42 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com
//        License:  Copyright © 2014 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <typeinfo>

using namespace std;
#define DELEGATE_TEMPLATE_PARAMS <typename TP1>
#define DELEGATE_TEMPLATE_ARGS TP1 p1
#define MY_DELEGATE IDelegate1
#define DELEGATE_BASE MY_DELEGATE <TP1>
template DELEGATE_TEMPLATE_PARAMS
class MY_DELEGATE 
{
public:
    virtual ~MY_DELEGATE() {}
    virtual bool isType(const type_info &_type) = 0;
    virtual void invoke(DELEGATE_TEMPLATE_ARGS) = 0;
    virtual bool compare(DELEGATE_BASE *_delegate) const = 0;
};

template DELEGATE_TEMPLATE_PARAMS
class CstaticDelegate : public DELEGATE_BASE 
{
public:
    typedef void (*func)(DELEGATE_TEMPLATE_ARGS);

    CstaticDelegate(func _func) : my_func(_func) {}

    virtual bool isType(const type_info &_type) 
    {
        return typeid(CstaticDelegate) == _type;
    }

    virtual void invoke(DELEGATE_TEMPLATE_ARGS)
    {
        my_func(p1);
    }

    virtual bool compare(DELEGATE_BASE *_delegate) const 
    {
        if(0 == _delegate || !_delegate->isType(typeid(CstaticDelegate))) 
            return false;
        CstaticDelegate *cast = static_cast<CstaticDelegate *>(_delegate);
        return cast->my_func == my_func;
    }
private:
    func my_func;
};

template DELEGATE_TEMPLATE_PARAMS
class CMethodDelegate : public DELEGATE_BASE
{
public:
    typedef void (TP1::*Method)(DELEGATE_TEMPLATE_ARGS);

    CMethodDelegate(TP1 *_object, Method _method) 
        : my_object(_object), my_method(_method) {}

    virtual bool isType(const type_info &_type)
    {
        return typeid(CMethodDelegate) == _type;
    }

    virtual void invoke(DELEGATE_TEMPLATE_ARGS)
    {
        (my_object->*my_method)(p1);
    }

    virtual bool compare(DELEGATE_BASE *_delegate) const
    {
        if(0 == _delegate || !_delegate->isType(typeid(CMethodDelegate)))
            return false;
        CMethodDelegate *cast = static_cast<CMethodDelegate *>(_delegate);
        return cast->my_object == my_object && cast->my_method == my_method;
    }

private:
    TP1 *my_object;
    Method my_method;
};

class CMultiDelegate
{
public:
    typedef list<MY_DELEGATE *> ListDelegate;
    typedef ListDelegate::iterator ListDelegateIterator;
    typedef ListDelegate::const_iterator ConstListDelegateIterator;
    CMultiDelegate() { }
    ~CMultiDelegate() { clear(); }

    bool empty() const
    {
        for(ConstListDelegateIterator iter = my_list_delegate.begin(); 
            iter != my_list_delegate.end(); ++iter)
        {
            if(*iter) return false;
        } 
        return true;
    }

    CMultiDelegate& operator +=(DELEGATE_BASE *_delegate)
    {
        for(ListDelegateIterator iter = my_list_delegate.begin(); 
            iter != my_list_delegate.end(); ++iter)
        {
            if((*iter) && (*iter)->compare(_delegate))
            {
                delete (*iter);
                (*iter) = NULL;
            }
        }
        my_list_delegate.push_back(_delegate);
        return *this;
    }

    CMultiDelegate& operator -=(DELEGATE_BASE *_delegate)
    {
        for(ListDelegateIterator iter = my_list_delegate.begin();
            iter != my_list_delegate.end(); ++iter)
        {
            if((*iter) && (*iter)->compare(_delegate))
            {
                if((*iter) != _delegate) delete (*iter);
                (*iter) = NULL;
                break;
            }
        }
        delete _delegate;
        return *this;
    }
    void operator() ()
    {
        ListDelegateIterator iter = my_list_delegate.begin();
        while(iter != my_list_delegate.end())
        {
            if(NULL == (*iter))
            {
                my_list_delegate.erase(iter);
            }
            else
            {
                (*iter)->invoke();
                ++iter; 
            }
        }
    }
private:
    void clear()
    {
        for(ListDelegateIterator iter = my_list_delegate.begin();
            iter != my_list_delegate.end(); ++iter)
        {
            if(*iter)
            {
                delete (*iter);
                (*iter) = NULL;
            }
        }
    }
    CMultiDelegate(const CMultiDelegate&);
    CMultiDelegate& operator =(CMultiDelegate&);
private:
    ListDelegate my_list_delegate;
};
template DELEGATE_TEMPLATE_ARGS
inline DELEGATE_BASE *newDelegate( void (*func)(DELEGATE_TEMPLATE_ARGS) )
{
    return new CstaticDelegate(func);
}

template DELEGATE_TEMPLATE_ARGS
inline DELEGATE_BASE *newDelegate(TP1 *object, void (TP1::*func)(DELEGATE_TEMPLATE_ARGS) )
{
    return new CMethodDelegate<TP1>(object, func); 
}

void normalFunc(int v)
{
    cout << "It is on normalFunc|" << v << endl;
}
class base
{
public:
    void func(int v)
    {
        cout << "The base of func|" << v << endl;
    }
};
int main()
{
    CMultiDelegate my_delegate;
    my_delegate += newDelegate(normalFunc);
    base b;
    my_delegate += newDelegate(&b, &base::func);
    my_delegate();
}
