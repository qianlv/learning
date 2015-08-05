//==============================================================================
// 
//       Filename:  mmap.c
// 
//    Description:  mmap usage code example
// 
//        Version:  1.0
//        Created:  2015年07月10日 10时48分50秒 CST
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv@qq.com
//        License:  Copyright © 2015 肖守冬. All Rights Reserved.
// 
// =====================================================================================


#include	<stdio.h>
#include	<errno.h>
#include	<unistd.h>
#include	<string.h>
#include    <fcntl.h>
#include    <sys/mman.h>
#include    <sys/types.h>      
#include    <sys/socket.h>
#include    <sys/stat.h>

void *Mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    void *p;

    p = mmap(addr, length, prot, flags, fd, offset);
    if (p == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }
    
    return p;
}

int main(int argc, char *argv[])
{
    char *ptr_pri, *ptr_sha;
    int fd;
    struct stat sb;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        return 1;
    }

    if (fstat(fd, &sb) == -1) {
       perror("fstat"); 
       return 1;
    }

    if (!S_ISREG(sb.st_mode)) {
        fprintf(stderr, "%s is not a file\n", argv[1]);
        return 1;
    }
    
    ptr_pri = Mmap(0, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    ptr_sha = Mmap(0, sb.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (!ptr_pri || !ptr_sha)
    {
        fprintf(stderr, "%s mmap fail\n", argv[1]);
        return 1;
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    int i;
    // 数据是共享的
    for (i = 0; i < 10; i++)
        ptr_sha[i] = 'f';
    for (i = 0; i < 10; i++)
        putchar(ptr_pri[i]);

    if (munmap(ptr_pri, sb.st_size) == -1 || 
        munmap(ptr_sha, sb.st_size) == -1) {
        perror("munmap");
        return 1;
    }

    return 0;
}
