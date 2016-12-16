/*
 * =====================================================================================
 *
 *       Filename:  a_simple_hierachical_mutex.h
 *
 *    Description:  a simple hierachical mutex
 *
 *        Version:  1.0
 *        Created:  2016年12月15日 19时34分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <exception>
#include <memory>
#include <stack>
#include <mutex>
#include <limits.h>

class hierachical_mutex
{
public:
    explicit hierachical_mutex (unsigned long value):
        hierarchy_value(value),
        previous_hierarchy_value(0)
    {}
    
    void lock()
    {
        check_for_hierarchy_violation();
        internal_mutex.lock();
        update_hierarchy_value();
    }

    void unlock()
    {
        this_thread_hierarchy_value = previous_hierarchy_value;
        internal_mutex.unlock();
    }

    bool try_lock()
    {
        check_for_hierarchy_violation();
        if (!internal_mutex.try_lock())
            return false;
        update_hierarchy_value();
        return true;
    }
private:
    void check_for_hierarchy_violation()
    {
        if (this_thread_hierarchy_value <= hierarchy_value)
        {
            throw std::logic_error("mutext hierarchy violated");
        }
    }

    void update_hierarchy_value()
    {
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }

private:
    /* data */
    std::mutex internal_mutex;
    const unsigned long hierarchy_value;
    unsigned long previous_hierarchy_value;
    thread_local static unsigned long this_thread_hierarchy_value;
};

thread_local unsigned long hierachical_mutex::this_thread_hierarchy_value(ULONG_MAX);
