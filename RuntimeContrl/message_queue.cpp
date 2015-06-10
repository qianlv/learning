// =====================================================================================
// 
//       Filename:  message_queue.cpp
// 
//    Description:  消息队列, 对应API可以查看man, man mq_overview比较好
// 
//        Version:  1.0
//        Created:  11/13/2014 01:57:55 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com
//        License:  Copyright © 2014 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#include <iostream>
#include <string>

#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>

#include "message_queue.h"
#include "signal_hook.h"

MessageQueue::MessageQueue() : m_mqd(-1)
{
    ;
}
MessageQueue::~MessageQueue()
{
    if ((mqd_t)-1 != m_mqd)
    {
        std::cout << "~MessageQueue" << std::endl;
        mq_close(m_mqd);
        //mq_unlink(m_name.c_str());
    }
}

// name必须以'/'开头的字符串
void MessageQueue::Init(std::string name, int signo, int flag)
{
    m_mqd = mq_open(name.c_str(), O_RDWR|O_CREAT|O_NONBLOCK, 0666, NULL);
    if ((mqd_t)-1 == m_mqd)
    {
        std::cout << "打开或创建消息队列失败|" << errno 
                  << "|" << strerror(errno) << std::endl;
    }
    m_name = name; 
    if (flag) {
        std::cout << "signo" << std::endl;
        // 注册signo信号的处理函数
        boost::function<void (int)> d_signal = 
               boost::bind(&MessageQueue::deal_signal, this, _1);
        (SignalHook::handler(signo))->add(d_signal);
        // 设置当空的消息队列接受到一个消息时，发出设置的信号signo
        m_sigevent.sigev_notify = SIGEV_SIGNAL;
        m_sigevent.sigev_signo = signo;
        mq_notify(m_mqd, &m_sigevent);
    }
}
// 信号处理函数
void MessageQueue::deal_signal(int signo)
{
    std::cout << "On deal_signal" << std::endl;
    struct mq_attr attr;
    mq_getattr(m_mqd, &attr);
    mq_notify(m_mqd, &m_sigevent);
    size_t size = attr.mq_msgsize;
    char buff[size + 1];
    int n;
    while ((n = mq_receive(m_mqd, buff, size, NULL)) >= 0)
    {
        // 通过委托把接受的数据，转发给OnRevc
        if(OnRevc)
        {
            OnRevc(buff, n);
        }
    }
    // If  the queue is empty, then, by default, 
    // mq_receive() blocks until a message becomes available, 
    // or the call is interrupted by a signal handler.  If the O_NONBLOCK
    // flag is enabled for the message queue description, 
    // then the call instead fails immediately with the error EAGAIN
    if (n == -1 && errno != EAGAIN)
    {
        std::cout << "[mq_receive]接受消息失败|" << errno 
                  << "|" << strerror(errno) << std::endl;
    }
}

bool MessageQueue::Send(std::string buff)
{
    return Send(buff.c_str(), buff.size());
}

bool MessageQueue::Send(const char *buff, size_t size)
{
    if(mq_send(m_mqd, buff, size, 0) == -1)
    {
        std::cout << "[mq_send]接受消息失败|" << errno 
                  << "|" << strerror(errno) << std::endl;
        return false;
    }
    return true;
}
