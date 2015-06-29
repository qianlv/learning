// =====================================================================================
// 
//       Filename:  talker.c
// 
//    Description:  a simple Datagram client demo.
// 
//        Version:  1.0
//        Created:  2015年06月29日 20时27分15秒 CST
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
    int sockfd;
    int rv;
    int numbytes;
    struct addrinfo hints, *serverinfo, *p;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: talker hostname message\n");
        exit(1);
    }
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    if ((rv = getaddrinfo(argv[1], PORT, &hints, &serverinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for (p = serverinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, 
                    p->ai_protocol)) == -1)
        {
            perror("talker: socket");
            continue;
        }

        break; 
    }

    if (p == NULL)
    {
        fprintf(stderr, "talker: failed to bind\n");
        return 2;
    }
    

    if ((numbytes = sendto(sockfd, argv[2], strlen(argv[2]), 0,
                    p->ai_addr, p->ai_addrlen)) == -1)
    {
        perror("talker: sendto");
        exit(1);
    }

    freeaddrinfo(serverinfo);
    printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);
    close(sockfd);

    return 0;
}
