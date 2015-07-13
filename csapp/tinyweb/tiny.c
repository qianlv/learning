// =====================================================================================
// 
//       Filename:  tiny.c
// 
//    Description:  a tiny web server
// 
//        Version:  1.0
//        Created:  2015年07月03日 09时41分42秒 CST
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv@qq.com
//        License:  Copyright © 2015 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#include "csapp.h"
#include <sys/epoll.h>

#define MAXEVENTS (20)

void *get_in_addr(struct sockaddr *sa);
const char *change_sockaddr_to_ip(struct sockaddr_storage *ss_addr);
int open_listen_socket(const char *port, int nlisten);
void AcceptSelect(int listenfd);
void AcceptEpoll(int listenfd);
void doit(int fd);
void read_requestaddr(rio_t *rp, char *header);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize, char *request_header);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs, char *request_header);
void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg, char *header);

// ===  FUNCTION  ======================================================================
//         Name:  open_listen_socket
//  Description:  打开socket并监听 
// =====================================================================================
int open_listen_socket(const char *port, int nlisten)
{
    struct addrinfo hints, *serverinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int rv;
    if ((rv = getaddrinfo(NULL, port, &hints, &serverinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    int listenfd;
    int yes = 1; // port 复用
    for (p = serverinfo; p != NULL; p = p->ai_next)
    {
        listenfd = Socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        const char *ip;
        ip = change_sockaddr_to_ip((struct sockaddr_storage*)(p->ai_addr));
        printf("new connection from %s on socket %d\n", ip, listenfd);
        if ((listenfd = socket(p->ai_family, p->ai_socktype,
                    p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                    sizeof(int)) == -1)
        {
            perror("setsockopt");
            continue;
        }

        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(listenfd);
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

    if (listen(listenfd, nlisten) == -1)
    {
        perror("listen");
        return -1;
    }

    return listenfd;
}


// ===  FUNCTION  ======================================================================
//         Name:  get_in_addr
//  Description:  get internet address (ipv4 or ipv6)
// =====================================================================================
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// ===  FUNCTION  ======================================================================
//         Name:  change_sockaddr_to_ip
//  Description:  获取字符串形式的IP地址
// =====================================================================================
const char *change_sockaddr_to_ip(struct sockaddr_storage *ss_addr)
{
    void *addr = get_in_addr((struct sockaddr*)ss_addr);
    static char ip[INET6_ADDRSTRLEN];
    inet_ntop(ss_addr->ss_family, addr, ip, sizeof(ip));
    return ip;
}


// ===  FUNCTION  ======================================================================
//         Name:  AcceptSelect
//  Description:  监听Http请求
// =====================================================================================
void AcceptSelect(int listenfd)
{
    fd_set master, read_fds;    
    int fd_max;
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(listenfd, &master);
    fd_max = listenfd;

    for(; ;)
    {
        read_fds = master;
        if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(1);
        }

        int fd;
        for (fd = 0; fd <= fd_max; fd++)
        {
            if (FD_ISSET(fd, &read_fds))
            {
                if (fd == listenfd)
                {
                    struct sockaddr_storage remoteaddr;
                    socklen_t addr_len = sizeof(remoteaddr);
                    int new_fd;
                    new_fd = accept(fd, (struct sockaddr*)&remoteaddr, &addr_len);
                    if (new_fd == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        FD_SET(new_fd, &master);
                        if (new_fd > fd_max)
                            fd_max = new_fd;
                        const char *ip;
                        ip = change_sockaddr_to_ip(&remoteaddr);
                        printf("new connection from %s on socket %d\n", ip, new_fd);
                    }

                }
                else
                {
                    doit(fd);
                    FD_CLR(fd, &master);
                    Close(fd);
                }
            }
        }
    }
}

// ===  FUNCTION  ======================================================================
//         Name:  AcceptEpoll
//  Description:  监听Http请求，并处理
// =====================================================================================
void AcceptEpoll ( int listenfd )
{

    int epollfd;
    if ((epollfd = epoll_create1(0)) == -1)
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev, *evs;
    ev.events = EPOLLIN;
    ev.data.fd = listenfd;
    
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1)
    {
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
    }
    
    evs = (struct epoll_event*) Calloc(MAXEVENTS, sizeof(struct epoll_event));
    
    for ( ; ; ) 
    {
        int nready;
        nready = epoll_wait(epollfd, evs, MAXEVENTS, -1);

        int i;
        for ( i = 0; i < nready; ++i) 
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

            if (ev.data.fd == listenfd)
            {
                struct sockaddr sa;
                socklen_t sa_len = sizeof (struct sockaddr);
                int newfd;
                LABLE: 
                newfd = accept(listenfd, &sa, &sa_len);
                if ( newfd == -1 )
                {
                    if ( errno == EINTR)
                    {
                        break;
                        goto LABLE;
                    }
                    perror("accept");
                    continue;
                }

                char ip[INET6_ADDRSTRLEN];
                void *addr = get_in_addr(&sa);
                inet_ntop(sa.sa_family, addr, ip, sizeof(ip));
                printf("Accept connection %s on descriptor %d\n", ip, newfd);

                struct epoll_event newev;
                newev.data.fd = newfd;
                newev.events = EPOLLIN | EPOLLONESHOT;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, newfd, &newev) == -1)
                {
                    perror("epoll_ctl");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                doit(ev.data.fd);
                Close(ev.data.fd);
            }
        }
    }
}		// -----  end of function AcceptEpoll  -----


// ===  FUNCTION  ======================================================================
//         Name:  doit
//  Description:  处理http请求
// =====================================================================================
void doit(int fd)
{
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
    sscanf(buf, "%s %s %s", method, uri, version);
//    printf("%s %s %s", method, uri, version);

    char request_header[MAXBUF];
    read_requestaddr(&rio, request_header);

    if (strcasecmp(method, "GET"))
    {
        clienterror(fd, method, "501", "Not Implemented", 
                    "Tiny does not Implement this method", request_header);
        return;
    }


    // Parse UIR from GET request
    char filename[MAXLINE], cgiargs[MAXLINE];
    int is_static = parse_uri(uri, filename, cgiargs);
    struct stat sbuf;
    if (stat(filename, &sbuf) < 0)
    {
        clienterror(fd, filename, "404", "Not Found",
                    "Tiny couldn't find this file", request_header);
        return ;
    }

    if (is_static)
    {
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode))
        {
            clienterror(fd, filename, "403", "Forbidden",
                        "Tiny couldn't read the file", request_header);
            return ;
        }
        serve_static(fd, filename, sbuf.st_size, request_header);
    }
    else
    {
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode))
        {
            clienterror(fd, filename, "403", "Forbidden",
                        "Tiny couldn't run the CGI program", request_header);
            return ;
        }
        printf("filename: %s", filename);
        serve_dynamic(fd, filename, cgiargs, request_header);
    }
}


// ===  FUNCTION  ======================================================================
//         Name:  clienterror
//  Description:  处理错误的HTTP请求
// =====================================================================================
void clienterror(int fd, char *cause, char *errnum, 
                 char *shortmsg, char *longmsg, char *request_header)
{
    char buf[MAXLINE], body[MAXBUF];

    // Build the HTTP response body
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The tiny Web Server</em>\r\n", body);

    // Print the HTTP response
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    // request header
    Rio_writen(fd, request_header, strlen(request_header));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
    
    return;
}


// ===  FUNCTION  ======================================================================
//         Name:  read_requestaddr
//  Description:  获取Http请求的header
// =====================================================================================
void read_requestaddr(rio_t *rp, char *header)
{
    char buf[MAXLINE];
    Rio_readlineb(rp, buf, MAXLINE);
//    printf("%lu\n", strlen(buf)); 
//    printf("%s\n", buf); 
    strcpy(header, buf);
    while (1)
    {
        Rio_readlineb(rp, buf, MAXLINE);
//        printf("%lu\n", strlen(buf)); 
//        printf("%s\n", buf); 
        if (strcmp(buf, "\r\n") == 0)
            break;
        strcat(header, buf);
    }
    return ;
}


// ===  FUNCTION  ======================================================================
//         Name:  parse_uri
//  Description:  解析uri, 获取请求文件名和参数, 判断静态请求或动态请求.
// =====================================================================================
int parse_uri(char *uri, char *filename, char *cgiargs)
{
    char *ptr;

    if (!strstr(uri, "cgi-bin"))
    {
        strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        if (uri[strlen(uri) - 1] == '/')
            strcat(filename, "home.html");
        return 1;
    }
    else
    {
        ptr = index(uri, '?');
        if (ptr) 
        {
            strcpy(cgiargs, ptr+1);
            *ptr = '\0'; // 截断uri
        }
        else
            strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri); 
        return 0;
    }
}


// ===  FUNCTION  ======================================================================
//         Name:  response_header
//  Description:  Http正确请求的应答header
// =====================================================================================
void response_header ( int fd, char *filename, 
                       int filesize, char *request_header)
{
    char filetype[MAXLINE], buf[MAXBUF];

    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%s%s", buf, request_header);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));
     
    return ;
}	


// ===  FUNCTION  ======================================================================
//         Name:  serve_static
//  Description:  处理Http静态文件请求
// =====================================================================================
void serve_static ( int fd, char *filename, 
                    int filesize, char *request_header)
{
    int srcfd;
    char *srcp;

    response_header(fd, filename, filesize, request_header);
    
    // Send response body to client
    srcfd = Open(filename, O_RDONLY, 0);
    srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);
}


// ===  FUNCTION  ======================================================================
//         Name:  get_filetype
//  Description:  获取文件类型
// =====================================================================================
void get_filetype(char *filename, char *filetype)
{
    if (strstr(filename, ".html"))
        strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
        strcpy(filetype, "image/gif");
    else if (strstr(filename, ".jpg"))
        strcpy(filetype, "image/jpeg");
    else 
        strcpy(filetype, "text/plain");
}

// ===  FUNCTION  ======================================================================
//         Name:  serve_dynamic
//  Description:  处理CGI动态请求
// =====================================================================================
void serve_dynamic(int fd, char *filename, char *cgiargs, char *request_header)
{
    char buf[MAXLINE], *emptylist[] = { NULL };

//    sprintf(buf, "HTTP/1.0 200 OK\r\n");
//    sprintf(buf, "%s%s", buf, request_header);
//    Rio_writen(fd, buf, strlen(buf));
//    sprintf(buf, "Server: Tiny Web Server\r\n");
//    Rio_writen(fd, buf, strlen(buf));

    response_header(fd, filename, 0, request_header);

    if (Fork() == 0)
    {
        setenv("QUERY_STRING", cgiargs, 1);
        Dup2(fd, STDOUT_FILENO);
        Execve(filename, emptylist, environ);
    }
    Wait(NULL);
}

int main(int argc, char *argv[])
{
    int listenfd;
    listenfd = open_listen_socket("1054", 10);
    //AcceptSelect(listenfd);
    AcceptEpoll(listenfd);
    return 0;
}

