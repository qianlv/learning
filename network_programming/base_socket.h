// =====================================================================================
// 
//       Filename:  base_socket.h
// 
//    Description:  base socket code
// 
//        Version:  1.0
//        Created:  2015年07月09日 11时47分58秒 CST
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv@qq.com
//        License:  Copyright © 2015 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#ifndef BASE_SOCKET_H
#define BASE_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

int create_socket_and_bind_port(const char *port);
int listen_socket(int fd, int n);
int make_fd_nonblock(int fd);
void *get_in_addr(struct sockaddr *sa);
int del_and_close_fd_from_epoll(int epollfd, int fd);

#endif /* BASE_SOCKET_H */
