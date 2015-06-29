// =====================================================================================
// 
//       Filename:  selectserver.c
// 
//    Description:  a cheezy multiperson chat server
// 
//        Version:  1.0
//        Created:  2015年06月29日 21时28分40秒 CST
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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT "9034" // listening port

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    fd_set master;
    fd_set read_fds;
    int fd_max;

    int listener;
    int new_fd;
    struct sockaddr_storage remoteaddr;
    socklen_t addr_len;

    char buf[256];
    int nbytes;

    char remoteIP[INET6_ADDRSTRLEN];
    int yes = 1;

    struct addrinfo hints, *serverinfo, *p;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int rv;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &serverinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for (p = serverinfo; p != NULL; p = p->ai_next)
    {
        if ((listener = socket(p->ai_family, p->ai_socktype, 
                    p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }
        if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, 
                sizeof(int)) == -1)
        {
            perror("setsockopt");
            continue;
        }


        if (bind(listener, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(listener);
            perror("server: bind");
            continue;
        }
        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(serverinfo);

    if (listen(listener, 10) == -1)
    {
        perror("listen");
        exit(1);
    }
    
    FD_SET(listener, &master);
    fd_max = listener;

    for (; ;)
    {
        read_fds = master;
        if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(1);
        }
        int i, j;
        for (i = 0; i <= fd_max; i++)
        {
            if (FD_ISSET(i, &read_fds)) 
            {
                if (i == listener)
                {
                    addr_len = sizeof(remoteaddr);
                    new_fd = accept(listener, (struct sockaddr*)&remoteaddr, &addr_len);
                    if (new_fd == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        FD_SET(new_fd, &master);
                        if (new_fd > fd_max)
                            fd_max = new_fd;
                        void *addr = get_in_addr((struct sockaddr*)&remoteaddr); 
                        inet_ntop(remoteaddr.ss_family, addr, remoteIP, sizeof(remoteIP));
                        printf("selectserver: new connection from %s on"
                                "socket %d\n", remoteIP, new_fd);
                    }
                }
                else
                {
                    if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
                    {
                        if (nbytes == 0)
                        {
                            printf("selectserver: socket %d hung up\n", i);
                        }
                        else
                        {
                            perror("recv");
                        }
                        close(i);
                        FD_CLR(i, &master);
                        continue;
                    }
                    int j;
                    // 把收取的数据转发
                    for (j = 0; j <= fd_max; j++)
                    {
                        if (!FD_ISSET(j, &master) || j == listener || j == i)
                            continue;
                        if (send(j, buf, nbytes, 0) == -1)
                        {
                            perror("send");
                        }
                    }
                }
            }
        }
    }
    return 0;
}

