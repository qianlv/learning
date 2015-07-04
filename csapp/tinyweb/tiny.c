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

int open_listen_socket(const char *port, int nlisten);
int AcceptSelect(int listenfd);
void doit(int fd);
char *read_requestaddr(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize, char *request_header);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs, char *request_header);
void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg, char *header);

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

/* get internet address (ipv4 or ipv6) */
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/* get ip address */
const char *change_sockaddr_to_ip(struct sockaddr_storage *ss_addr)
{
    void *addr = get_in_addr((struct sockaddr*)ss_addr);
    static char ip[INET6_ADDRSTRLEN];
    inet_ntop(ss_addr->ss_family, addr, ip, sizeof(ip));
    return ip;
}

/* 监听请求 */
int AcceptSelect(int listenfd)
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
    return 0;
}

void doit(int fd)
{
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
    sscanf(buf, "%s %s %s", method, uri, version);
    char *request_header;
    request_header = read_requestaddr(&rio);
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

// response error msg to client
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

// Ignores any of imformation in the request headers
char *read_requestaddr(rio_t *rp)
{
    char buf[MAXLINE];
    char *header = Malloc(MAXBUF);
    Rio_readlineb(rp, buf, MAXLINE);
    printf("%lu\n", strlen(buf)); 
    strcpy(header, buf);
    while (1)
    {
        Rio_readlineb(rp, buf, MAXLINE);
        printf("%lu\n", strlen(buf)); 
        //printf("%s\n", buf); 
        if (strcmp(buf, "\r\n") == 0)
            break;
        strcat(header, buf);
    }
    return header;
}

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

void serve_static(int fd, char *filename, int filesize, char *request_header)
{
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];

    // Send response headers to client
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%s%s", buf, request_header);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));
    
    // Send response body to client
    srcfd = Open(filename, O_RDONLY, 0);
    srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);
}

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

void serve_dynamic(int fd, char *filename, char *cgiargs, char *request_header)
{
    char buf[MAXLINE], *emptylist[] = { NULL };

    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%s%s", buf, request_header);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));

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
    AcceptSelect(listenfd);
}
