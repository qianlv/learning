// =====================================================================================
// 
//       Filename:  signal_hook.h
// 
//    Description:  信号挂钩 
// 
//        Version:  1.0
//        Created:  11/13/2014 03:42:38 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com
//        License:  Copyright © 2014 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#ifndef _SIGNAL_HOOK_H__
#define _SIGNAL_HOOK_H__
#include <map>
#include <string>

#include <signal.h>
#include <boost/function.hpp>

#include "delegate_example.h"

class SignalHook
{
public:
    static void Init();
    static Delegate<boost::function<void (int)> >* handler(int signo);
private:
    static std::map<int, Delegate<boost::function<void (int)> > > handler_map;
};

#endif // _SIGNAL_HOOK_H__
