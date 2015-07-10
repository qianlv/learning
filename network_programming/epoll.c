// =====================================================================================
// 
//       Filename:  epoll.c
// 
//    Description:  epoll code example
// 
//        Version:  1.0
//        Created:  2015年07月09日 11时46分19秒 CST
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
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include "base_socket.h"

#define MAXLISTEN   10
#define MAXEVENTS   20 

int main(int argc, char *argv[])
{
    struct epoll_event ev;
    struct epoll_event *evs;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: epoll port\n");
        exit(1);
    }

    int socketfd = create_socket_and_bind_port(argv[1]);
    if (socketfd == -1)
    {
        exit(EXIT_FAILURE);
    }

    if (make_fd_nonblock(socketfd) == -1)
    {
        exit(EXIT_FAILURE);
    }

    if (listen_socket(socketfd, MAXLISTEN) == -1)
    {
        exit(EXIT_FAILURE);
    }

    int epollfd;
    if ((epollfd = epoll_create1(0)) == -1)
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events    = EPOLLIN | EPOLLET;
    ev.data.fd   = socketfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, socketfd, &ev) == -1)
    {
        perror("epoll_ctl"); 
        exit(EXIT_FAILURE);
    }

    evs= calloc(sizeof (struct epoll_event), MAXEVENTS);
    if (!evs)
    {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    
    for ( ; ;)
    {
        int nret; 
        nret = epoll_wait(epollfd, evs, MAXEVENTS, -1);
        int i;
        for (i = 0; i < nret; ++i)
        {
            ev = evs[i];
            if ((ev.events & EPOLLERR) || 
                 (ev.events & EPOLLHUP) || 
                (!(ev.events & EPOLLIN)))
            {
                fprintf(stderr, "epoll error: %u\n", ev.events); 
                epoll_ctl(epollfd, EPOLL_CTL_DEL, ev.data.fd, NULL);
                close(ev.data.fd); 
                continue;
            }

            if (ev.data.fd == socketfd)
            {  
                for (; ;)
                {
                    int newfd;
                    struct sockaddr sa;
                    socklen_t sa_len = sizeof(struct sockaddr);
                    newfd = accept(socketfd, &sa, &sa_len);
                    if (newfd == -1)
                    {
                        if ( errno == EAGAIN || errno == EWOULDBLOCK)
                        {
                            break;
                        }
                        perror("accept");
                        break;
                    }

                    char ip[INET6_ADDRSTRLEN];
                    void *addr = get_in_addr(&sa);
                    inet_ntop(sa.sa_family, addr, ip, sizeof(ip));
                    printf("Accept connection %s on descriptor %d\n", ip, newfd);
                    
                    if (make_fd_nonblock(newfd) == -1)
                    {
                        exit(EXIT_FAILURE);
                    }

                    struct epoll_event newev;
                    newev.data.fd = newfd;
                    newev.events = EPOLLIN | EPOLLET;
                    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, newfd, &newev) == -1)
                    {
                        perror("epoll_ctl");
                        exit(EXIT_FAILURE);
                    }
                } // END FOR
            } // END IF
            else
            {
                int done = 0;
                for ( ; ;)
                {
                    ssize_t count;
                    char buf[BUFSIZ];

                    count = read(ev.data.fd, buf, BUFSIZ);
                    if (count == -1)
                    {
                        if (errno != EAGAIN)
                        {
                            perror("read");
                            done = 1;        
                        }
                        break;
                    } 
                    else if (count == 0)
                    {
                        done = 1;
                        break;
                    }

                    int nw = write(STDOUT_FILENO, buf, count); // write buf to standard output
                    if (nw == -1)
                    {
                        perror("write");
                        exit(EXIT_FAILURE);
                    }
                } // END FOR

                if (done == 1)
                {
                    printf("Closed connection on descriptor %d\n", ev.data.fd);
                    del_and_close_fd_from_epoll(epollfd, ev.data.fd);
                    continue;
                }
            } // END ELSE
        }
    }
}
