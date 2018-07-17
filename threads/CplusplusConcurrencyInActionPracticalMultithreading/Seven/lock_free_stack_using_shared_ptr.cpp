/*
 * =====================================================================================
 *
 *       Filename:  lock_free_stack_using_shared_ptr.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年07月17日 09时57分50秒
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
    struct node {
        std::shared_ptr<T> data;
        std::shared_ptr<node> next;

        node(T const& data_):
            data(std::make_shared<T>(data_)) { }
    };

    std::shared_ptr<node> head;

public:
    lock_free_stack(): head(nullptr) {}
    lock_free_stack(const lock_free_stack&) = delete;
    lock_free_stack& operator=(const lock_free_stack&) = delete;

    void push(T const& data) {
        std::shared_ptr<node> const new_node = std::make_shared<node>(data);
        new_node->next = std::atomic_load(&head);
        while (!std::atomic_compare_exchange_weak(&head,
                &new_node->next, new_node)) {
        }
    }

    std::shared_ptr<T> pop() {
        std::shared_ptr<node> old_head = std::atomic_load(&head);
        while (old_head && !std::atomic_compare_exchange_weak(
                    &head, &old_head, old_head->next)) {
        }
        return old_head ? old_head->data : std::shared_ptr<T>();
    }
};

int main(void) {
    lock_free_stack<int> t;
    t.push(2);
    std::thread th1([&]() {t.push(1);});
    th1.join();
    auto v = t.pop();
    std::cout << (*v) << std::endl;
    v = t.pop();
    std::cout << (*v) << std::endl;
    return 0;
}
