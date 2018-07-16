/*
 * =====================================================================================
 *
 *       Filename:  threadsafe_list.cpp
 *
 *    Description:  thread safe list with iteartion suppport
 *
 *        Version:  1.0
 *        Created:  2018年07月16日 14时05分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <utility>
#include <mutex>
#include <shared_mutex>
#include <list>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <memory>

template <typename T>
class threadsafe_list {
private:
    struct node {
        std::mutex m;
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;

        node(): next() {}

        node(const node& value):
            data(std::make_shared<T>(value)) {}
    };

    node head;

public:
    threadsafe_list() {}
    ~threadsafe_list() {
    }

    threadsafe_list(threadsafe_list const& other) = delete;
    threadsafe_list& operator=(threadsafe_list const& other) = delete;

    void push_back(T const& value) {
        std::unique_ptr<node> new_node(new node(value));
        std::lock_guard<std::mutex> lk(head.m);
        new_node->next = std::move(head.next);
        head.next = std::move(new_node);
    }

    template <typename Function>
    void for_each(Function f) {
        node* current = &head;
        std::unique_lock<std::mutex> lk(head.m);
        while (node* const next = current->next.get()) {
            std::unique_lock<std::mutex> next_lk(next->m);
            lk.unlock();
            f(*next->data);
            current = next;
            lk = std::move(next_lk);
        }
    }

    template <typename Predicate>
    std::shared_ptr<T> find_first_if(Predicate p) {
        node* current = &head;
        std::unique_lock<std::mutex> lk(head.m);
        while (node* const next = current->next.get()) {
            std::unique_lock<std::mutex> next_lk(next->m);
            lk.unlock();
            if (p(*next->data)) {
                return next->data;
            };
            current = next;
            lk = std::move(next_lk);
        }
    }

    template <typename Predicate>
    void remove_if(Predicate p) {
        node* current = &head;
        std::unique_lock<std::mutex> lk(head.m);
        while (node* const next = current->next.get()) {
            std::unique_lock<std::mutex> next_lk(next->m);
            if (p(*next->data)) {
                std::unique_ptr<node> old_next = std::move(current->next);
                current->next = std::move(next->next);
                next_lk.unlock();
            } else {
                lk.unlock();
                current = next;
                lk = std::move(next_lk);
            }
        }
    }
};
