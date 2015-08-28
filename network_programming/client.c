// =====================================================================================
// 
//       Filename:  client.c
// 
//    Description:  a stream socket client demo
// 
//        Version:  1.0
//        Created:  2015年06月29日 19时58分28秒 CST
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
#include <sys/wait.h>
#include <signal.h>

#define PORT        "3490"  // the port users will be connecting to
#define MAXDATESIZE 100


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
    int sockfd, numbytes;
    int rv;
    struct addrinfo hints, *serverinfo, *p;
    char buf[MAXDATESIZE];
    char s[INET6_ADDRSTRLEN];


    if (argc < 2)
    {
        fprintf(stderr, "Usage: client hostname\n");
        exit(1);
    }
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((rv = getaddrinfo(argv[1], PORT, &hints, &serverinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for (p = serverinfo; p != NULL; p = p->ai_next)
    {
        void *addr = get_in_addr((struct sockaddr*)p); 
        inet_ntop(p->ai_family, addr, s, sizeof(s));
        printf("current deal ip: %s\n", s);

        if ((sockfd = socket(p->ai_family, p->ai_socktype, 
                    p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }
        
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            if (errno == ECONNREFUSED)
            {
                fprintf(stderr, "recv rst error\n");
            }
            close(sockfd);
            perror("server: connect");
            continue;
        }
        break; 
    }

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to connect\n");
        return 2;
    }
    
    printf("clinet: conneting to %s\n", s);
    
    freeaddrinfo(serverinfo);

    if ((numbytes = recv(sockfd, buf, MAXDATESIZE - 1, 0)) == -1)
    {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';
    printf("clinet: received '%s', %d\n", buf, numbytes);
    
    close(sockfd);

    return 0;
}
