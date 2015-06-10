// =====================================================================================
// 
//       Filename:  message_queue.h
// 
//    Description:  消息队列
// 
//        Version:  1.0
//        Created:  11/13/2014 01:27:07 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com
//        License:  Copyright © 2014 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#ifndef _MESSAGE_QUEUE_H__
#define _MESSAGE_QUEUE_H__

#include <iostream>
#include <string>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <mqueue.h>

#include "delegate_example.h"

class MessageQueue
{
public:
    MessageQueue();
    ~MessageQueue();
public:
    void Init(std::string name, int signo, int flag);
    bool Send(std::string buff);
    bool Send(const char *buff, size_t size);
public:
    Delegate<boost::function<void(const char *, size_t)> > OnRevc;
private:
    void deal_signal(int);
    mqd_t m_mqd;
    std::string m_name;
    struct sigevent m_sigevent;
};
#endif //_MESSAGE_QUEUE_H__
