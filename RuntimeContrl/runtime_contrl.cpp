// =====================================================================================
// 
//       Filename:  runtime_contrl.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  11/13/2014 02:35:03 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com
//        License:  Copyright © 2014 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#include <iostream>
#include <string>

#include <signal.h>
#include "message_queue.h"

void Recv(const char *buff, size_t size)
{
    std::cout << "The data is : " << buff << std::endl
              << "The size is : " << size << std::endl;
}
int main(int argc, char *argv[])
{
    if (argv[1])
    {
        MessageQueue mq;
        mq.Init("/message34", SIGUSR1, 0);
        std::string msg("abc");
        mq.Send(msg);
    }
    else 
    {
        std::cout << "on revc" << std::endl;
        MessageQueue mq;
        mq.Init("/message34", SIGUSR1, 1);
        typedef Delegate<boost::function<void (const char *, size_t) > >::DelegateType DelegateType;
        DelegateType delegate = boost::bind(&Recv, _1, _2);
        mq.OnRevc += delegate;
        while (true)
        {
            std::string input;
            std::cin >> input;
            if (input == "quit")
                break;
            sleep(1);
        }
    }
}
