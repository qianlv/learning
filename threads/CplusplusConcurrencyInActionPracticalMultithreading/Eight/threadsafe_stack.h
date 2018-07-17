/*
 * =====================================================================================
 *
 *       Filename:  threadsafe_stack.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年07月17日 14时30分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <mutex>
#include <memory>
#include <exception>
#include <stack>

struct empty_stack : std::exception {
    const char* what() const throw();
};

template <typename T>
class threadsafe_stack {
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack& other) {
        std::lock_guard<std::mutex> lk(other.m);
        data = other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T& value) {
        std::lock_guard<std::mutex> lk(m);
        data.push(std::move(value));
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lk(m);
        if (data.empty()) throw empty_stack();
        std::shared_ptr<T> const res(
            std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    void pop(T& value) {
        std::lock_guard<std::mutex> lk(m);
        if (data.empty()) throw empty_stack();
        value = std::move(data.top());
        data.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(m);
        return data.empty();
    }
};
