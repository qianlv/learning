// =====================================================================================
// 
//       Filename:  base_socket.c
// 
//    Description:  base socket code
// 
//        Version:  1.0
//        Created:  2015年07月09日 11时49分31秒 CST
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv@qq.com
//        License:  Copyright © 2015 肖守冬. All Rights Reserved.
// 
// =====================================================================================

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

#include "base_socket.h"

int create_socket_and_bind_port(const char *port)
{
    struct addrinfo hints, *serverinfo, *p;
    int socketfd;       
    int yes = 1;        // 端口复用

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family     = AF_UNSPEC;    
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_flags      = AI_PASSIVE;
    
    int rv;
    if ((rv = getaddrinfo(NULL, port, &hints, &serverinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return -1;
    }

    for (p = serverinfo; p != NULL; p = p->ai_next)
    {
        if ((socketfd = socket(p->ai_family, p->ai_socktype, 
                    p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }
        if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, 
                sizeof(int)) == -1)
        {
            perror("setsockopt");
            continue;
        }

        if (bind(socketfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(socketfd);
            perror("server: bind");
            continue;
        }
        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        return -1;
    }

    freeaddrinfo(serverinfo);

    return socketfd;
}

int listen_socket(int fd, int n)
{
    if (listen(fd, n) == -1)
    {
        perror("listen");
        return -1;
    }

    return 0;
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return (void *)&(((struct sockaddr_in *)sa)->sin_addr);
    }
    return (void *)&(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int make_fd_nonblock(int fd)
{
    int flags, s;
    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
    {
        perror("fcntl");
        return -1;
    }
    flags |= O_NONBLOCK;
    s = fcntl(fd, F_SETFL, flags);
    if (s == -1)
    {
        perror("fcntl");
        return -1;
    }

    return 0;
}

int del_and_close_fd_from_epoll(int epollfd, int fd)
{
    if (epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL) == -1)
    {
        perror("epoll_ctl");
        return -1;
    }
    if (close(fd) == -1)
    {
        perror("close");
        return -1;
    }
    return 0;
}

