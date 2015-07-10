// =====================================================================================
// 
//       Filename:  logical_to_physical_block.c
// 
//    Description:  获取从文件的逻辑块(logical block)号到物理块(physical block)号
//                  logical block 只与文件本身相关, 每个文件由若干个logical block组成
//                  块号从0开始索引.
//                  physical block 一个或多个扇区组成(sector).
//                  每个逻辑块对于一个物理块.
// 
//        Version:  1.0
//        Created:  2015年07月10日 15时39分19秒 CST
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv@qq.com
//        License:  Copyright © 2015 肖守冬. All Rights Reserved.
// 
// =====================================================================================


#include	<stdio.h>
#include    <stdlib.h>
#include	<errno.h>
#include	<unistd.h>
#include	<string.h>
#include    <fcntl.h>
#include    <sys/types.h>      
#include    <sys/socket.h>
#include    <sys/stat.h>
#include    <sys/ioctl.h>
#include    <linux/fs.h>

#define handle_error_ret(msg) \
    do { perror(msg); return -1; } while(0)
#define handle_error_exit(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while(0)


// ===  FUNCTION  ======================================================================
//         Name:  get_block
//  Description:  for file associated with the given fd, returns
//                the physical block mapping to logical_block. 
// =====================================================================================
int get_block ( int fd, int logical_block )
{
    int ret;
    ret = ioctl (fd, FIBMAP, &logical_block);
    if ( ret == -1 ) {
        handle_error_ret("ioctl");
    }

    return logical_block;
}		// -----  end of function get_block  -----


// ===  FUNCTION  ======================================================================
//         Name:  get_nr_blocks
//  Description:  returns the number of 512B blocks
//                consumed the file associated with fd.
// =====================================================================================
int get_nr_blocks ( int fd )
{
    struct stat buf;
    int ret;

    ret = fstat (fd, &buf);
    if ( ret == 1 ) {
        handle_error_ret("fstat");
    }

    return buf.st_blocks;
}


// ===  FUNCTION  ======================================================================
//         Name:  print_blocks
//  Description:  print (logical_block, phys_block) for fd
// =====================================================================================
void print_blocks ( int fd )
{
    int nr_blocks, i;
    
    nr_blocks = get_nr_blocks (fd);
    if (nr_blocks < 0) {
        fprintf(stderr, "get_nr_blocks failed \n");
        return ;
    }
    
    if ( nr_blocks == 0 ) {
        printf ("no allocated blocks\n");
        return ;
    }
    else {
        printf ("%d blocks\n\n", nr_blocks);
    }
    
    for ( i = 0; i < nr_blocks; ++i) {
        int phys_block;
        phys_block = get_block (fd, i);
        if ( phys_block < 0 ) {
            fprintf (stderr, "get_block failed!\n");
            return ;
        }
        
        if ( !phys_block )
            continue;

        printf ("(%u, %u) \n", i, phys_block);
    }
    
    return ;
}		// -----  end of function print_blocks  -----

int main(int argc, char *argv[])
{
    int fd;
    
    if ( argc < 2 ) {
        fprintf (stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }

    fd = open (argv[1], O_RDONLY);
    if ( fd < 0 ) {
        handle_error_exit("open");
    }
    
    print_blocks (fd);

    return 0;
}
