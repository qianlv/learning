/*
 * =====================================================================================
 *
 *       Filename:  passing_arguments_to_a_thread_function.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年12月14日 19时50分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <thread>
#include <string>

void f(int i, std::string const& s);

// avoid dangling pointer
void oops(int some_param)
{
    char buffer[1024];
    sprintf(buffer, "%i", some_param);
    std::thread t(f, 3, buffer); // 在新线程中 buffer 已经失效, 当 oops 函数先返回时, 无法转换为string
    // std::thread t(f. 3, std::string(buffer)); // 在 thread 的构造函数传值提前转换为 string, 从而避免传buffer 指针。
    t.detach();
}

class widget_id {};
class widget_data {};
void update_data_for_widget(widget_id w, widget_data& data);
void process_widget_data(widget_data& data);

// 函数目的是在线程中修改data, 然后主线中处理修改后的数据.
// 此次查看 thread 构造函数源代码:
// template<typename _Callable, typename... _Args>
// thread(_Callable&& __f, _Args&&... __args)
// { _M_start_thread(_M_make_routine(std::bind(__f, __args...))); }
// 参数用的了 std::bind, 导致数据的 copy. 关于 std::bind 可以参考: http://stackoverflow.com/questions/5850360/why-does-stdbind-tries-to-copy-my-object
void oops_again(widget_id w)
{
    widget_data data;
    std::thread t(update_data_for_widget, w, data); // 虽然 update_data_for_widget 参数是对 widget_data 的引用, 但是 thread 的构造函数拷贝了一份 data, 因此引用的是一个 copy.
    // std::thread t(update_data_for_widget, w, std::ref(data);
    t.join();
    process_widget_data(data);
}

// 传递类函数

class X
{
public:
    void do_lengthy_work();
};

void oops_again_again()
{
    X my_x;
    std::thread t(&X::do_lengthy_work, &my_x);
    t.join();
}
