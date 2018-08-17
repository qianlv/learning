/*
 * =====================================================================================
 *
 *       Filename:  lock_free_stack_with_ref_count.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年07月17日 10时10分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <atomic>
#include <memory>
#include <iostream>
#include <thread>

template <typename T>
class lock_free_stack {
private:
    struct node;
    struct counted_node_ptr {
        int external_count;
        node* ptr;
    };

    struct node {
        std::shared_ptr<T> data;
        std::atomic<int> internal_count;
        counted_node_ptr next;

        node(T const& data_):
            data(std::make_shared<T>(data_)), internal_count(0) { }
    };

    std::atomic<counted_node_ptr> head;

public:
    lock_free_stack() {}
    lock_free_stack(const lock_free_stack&) = delete;
    lock_free_stack& operator=(const lock_free_stack&) = delete;

    void push(T const& data) {
        counted_node_ptr new_node;
        new_node.ptr = new node(data);
        new_node.external_count = 1;
        new_node.ptr->next = head.load();
        while(!head.compare_exchange_weak(new_node.ptr->next, new_node)) {
        }
    }

    std::shared_ptr<T> pop() {
    }
};
