// =====================================================================================
// 
//       Filename:  listener.c
// 
//    Description:  a simple datagram sockets server demo
// 
//        Version:  1.0
//        Created:  2015年06月29日 20时18分46秒 CST
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
#define MAXBUFLEN   100

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    int sockfd, new_fd;
    int rv;
    int numbytes;
    struct addrinfo hints, *serverinfo, *p;
    struct sockaddr_storage their_addr; //  connector's address information.
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];
    char buf[MAXBUFLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &serverinfo)) != 0)
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
            perror("listener: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("listener: bind");
            continue;
        }
        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "listener: failed to bind\n");
        return 2;
    }

    freeaddrinfo(serverinfo);

    printf("listener: waiting for recvfrom..\n");
    
    addr_len = sizeof(their_addr);
    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, 
            (struct sockaddr *)&their_addr, &addr_len)) == -1)
    {
        perror("recvfrom");
        exit(1);
    }
    inet_ntop(their_addr.ss_family, 
            get_in_addr((struct sockaddr*)&their_addr), 
            s, sizeof(s));
    printf("listener: got packet from %s\n", s);
    printf("listener: packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
    printf("listener: packet contains %s\n", buf);

    close(sockfd);
    return 0;
}
