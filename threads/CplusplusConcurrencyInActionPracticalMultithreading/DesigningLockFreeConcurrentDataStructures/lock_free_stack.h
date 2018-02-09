/*
 * =====================================================================================
 *
 *       Filename:  lock_free_stack.h
 *
 *    Description:  lock free stack
 *
 *        Version:  1.0
 *        Created:  2018年02月04日 14时10分45秒
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


template<typename T>
class lock_free_stack
{
public:
    void push(T const& data)
    {
        node* const new_node = new node(data);
        new_node->next = head.load();
        while(!head.compare_exchange_weak(new_node->next, new_node));
    }

    // 赋值时可能抛出异常
    // void pop(T& result)
    // {
        // node* old_head = head.load();
        // while(!head.compare_exchange_weak(old_head, old_head->next));
        // result = old_head->data;
    // }
    
    // node 节点内存泄露
    // std::shared_ptr<T> pop()
    // {
    //     node* old_head = head.load();
    //     while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
    //     return old_head ? old_head->data : std::shared_ptr<T>();
    // }
    
    std::shared_ptr<T> pop()
    {
        ++threads_in_pop;
        node* old_head = head.load();
        while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
        std::shared_ptr<T> res;
        if(old_head)
        {
            res.swap(old_head->data);
        }
        try_reclaim(old_head);
        return res;
    }

private:
    struct node
    {
        //T data;
        std::shared_ptr<T> data;
        node* next;

        node(T const& data_):
            data(std::make_shared<T>(data_))
        {}
    };
    std::atomic<node*> head;
    std::atomic<unsigned> threads_in_pop;

private:
    std::atomic<node*> to_be_deleted;

    static void delete_node(node* nodes)
    {
        while(nodes)
        {
            node* next = nodes->next;
            delete nodes;
            nodes = next;
        }
    }

    void try_reclaim(node* old_head)
    {
        if (threads_in_pop == 1)
        {
            node* nodes_to_delete = to_be_deleted.exchange(nullptr);
            if (!--threads_in_pop)
            {
                delete_node(nodes_to_delete);
            }
            else if (nodes_to_delete)
            {
                chain_pending_nodes(nodes_to_delete);
            }
            delete old_head;
        }
        else
        {
            chain_pending_node(old_head);
            --threads_in_pop;
        }
    }

    void chain_pending_nodes(node* nodes)
    {
        node* last = nodes;
        while(node* const next = last->next)
        {
            last = next;
        }
        chain_pending_nodes(nodes, last);
    }

    void chain_pending_nodes(node* first, node* last)
    {
        last->next = to_be_deleted;
        while(!to_be_deleted.compare_exchange_weak(last->next, first));
    }

    void chain_pending_node(node* n)
    {
        chain_pending_nodes(n, n);
    }
};
