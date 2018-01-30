/*
 * =====================================================================================
 *
 *       Filename:  thread_safe_queue.h
 *
 *    Description:  Threa safe queue
 *
 *        Version:  1.0
 *        Created:  2016年12月16日 22时19分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

template <class T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue() {};
    ThreadSafeQueue(const ThreadSafeQueue& other)
    {
        std::lock_guard<std::mutex> lk(other.mutex_);
        queue_ = other.queue_;
    }

    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mutex_);
        queue_.push(new_value);
        notEmpty_.notify_one();
    }

    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mutex_);
        if (queue_.empty())
        {
            return false;
        }
        value = queue_.front();
        queue_.pop();
        return true;
    }

    std::shared_ptr<T> try_pop()
    {
        std::unique_lock<std::mutex> lk(mutex_);
        if (queue_.empty())
        {
            return false;
        }
        std::shared_ptr<T> res(std::make_shared<T>(queue_.front()));
        queue_.pop();
        return res;
    }

    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mutex_);
        notEmpty_.wait(lk, [this] { return !queue_.empty();});
        value = queue_.front();
        queue_.pop();
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mutex_);
        notEmpty_.wait(lk, [this] { return !queue_.empty();});
        std::shared_ptr<T> res(std::make_shared<T>(queue_.front()));
        queue_.pop();
        return res;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mutex_);
        return queue_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable notEmpty_;
    std::queue<T> queue_;
};
