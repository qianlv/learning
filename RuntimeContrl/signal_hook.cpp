// =====================================================================================
// 
//       Filename:  signal_hook.cpp
// 
//    Description:  信号挂钩
// 
//        Version:  1.0
//        Created:  11/13/2014 03:48:37 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com
//        License:  Copyright © 2014 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#include <iostream>
#include <string>
#include <map>

#include <boost/function.hpp>
#include <signal.h>

#include "signal_hook.h"

static void SigHandler(int signo)
{
    std::cout << "接受到信号:" << signo <<  std::endl;
    if(Delegate<boost::function<void (int)> > *deal_signal = SignalHook::handler(signo))
    {
        (*deal_signal)(signo);
    }
}

Delegate<boost::function<void (int)> >* SignalHook:: handler(int signo)
{
    auto it = handler_map.find(signo);
    if (it != handler_map.end())
    {
        return &(it->second);
    }
    //注册信号
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SigHandler;
    sigaction(signo, &sa, NULL);
    return &handler_map[signo];
}

void SignalHook::Init()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &sa, NULL);
}
std::map<int, Delegate<boost::function<void (int)> > > SignalHook::handler_map;
