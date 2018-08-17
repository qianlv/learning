/*
 * =====================================================================================
 *
 *       Filename:  lock_free_stack.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年07月16日 15时26分14秒
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
        node* next;

        node(T const& data_):
            data(std::make_shared<T>(data_)) { }
    };

    std::atomic<node*> head;
    std::atomic<unsigned> threads_in_pop;
    std::atomic<node*> to_be_deleted;

public:
    lock_free_stack(): head(nullptr), threads_in_pop(0), to_be_deleted(nullptr) {}
    lock_free_stack(const lock_free_stack&) = delete;
    lock_free_stack& operator=(const lock_free_stack&) = delete;

    void push(T const& data) {
        node* const new_node = new node(data);
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node)) {
        }
    }

    std::shared_ptr<T> pop() {
        ++threads_in_pop;
        node* old_head = head.load();
        while (old_head &&
               !head.compare_exchange_weak(old_head, old_head->next)) {
        }
        std::shared_ptr<T> res;
        if (old_head) {
            res.swap(old_head->data);
        }
        try_reclaim(old_head);
        return res;
    }

private:
    static void delete_node(node* nodes) {
        while (nodes) {
            node* next = nodes->next;
            delete nodes;
            nodes = next;
        }
    }

    void try_reclaim(node* old_head) {
        if (threads_in_pop == 1) {
            node* nodes_to_delete = to_be_deleted.exchange(nullptr);
            if (!--threads_in_pop) {
                delete_node(nodes_to_delete);
            } else if (nodes_to_delete) {
                chain_pending_nodes(nodes_to_delete);
            }
            delete old_head;
        } else {
            chain_pending_node(old_head);
            --threads_in_pop;
        }
    }

    void chain_pending_nodes(node* nodes) {
        node* last = nodes;
        while (node* const next = last->next) {
            last = next;
        }
        chain_pending_nodes(nodes, last);
    }

    void chain_pending_nodes(node* first, node* last) {
        last->next = to_be_deleted;
        while (!to_be_deleted.compare_exchange_weak(last->next, first)) {
        }
    }

    void chain_pending_node(node* n) {
        chain_pending_nodes(n, n);
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
