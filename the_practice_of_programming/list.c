// =====================================================================================
// 
//       Filename:  list.c
// 
//    Description:  List
// 
//        Version:  1.0
//        Created:  06/25/2015 05:25:19 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com, qianlv7@gmail.com
//        License:  Copyright © 2015 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eprintf.h"

typedef struct Nameval Nameval;
struct Nameval {
    char *name;
    int value;
    Nameval *next;
};

Nameval *newitem(char *name, int value)
{
    Nameval *newp;
    newp = (Nameval *)emalloc(sizeof(Nameval));
    newp->name = name;
    newp->value = value;
    newp->next = NULL;
    return newp;
}

Nameval *addfront(Nameval *listp, Nameval *newp)
{
    newp->next = listp;
    return newp;
}

Nameval *addend(Nameval *listp, Nameval *newp)
{
    Nameval *p;

    if (listp == NULL)
        return newp;
    for (p = listp; p->next != NULL; p = p->next)
        ;
    p->next = newp;
    return listp;
}

Nameval *lookup(Nameval *listp, char *name)
{
    for (; listp != NULL; listp = listp->next)
    {
        if (strcmp(listp->name, name) == 0)
            return listp;
    }
    return NULL;
}

// excute fn for each element of listp
void apply(Nameval *listp, 
    void (*fn)(Nameval *, void*), void *arg)
{
    for (; listp != NULL; listp = listp->next)
    {
        (*fn)(listp, arg);
    }
}

void printv(Nameval *listp, void *arg)
{
    char *fmt;
    fmt = (char *) arg;
    printf(fmt, listp->name, listp->value);
}

void inccounter(Nameval *p, void *arg)
{
    int *ip;
    ip = (int *)arg;
    (*ip)++;
}
/* call it like this:
 * int n;
 * n = 0;
 * apply(nvlist, inccounter, &n);
 * printf("%d elements in nvlist", n);
 */
void freeall(Nameval *listp)
{
    Nameval *next;
    for (; listp != NULL; listp = next)
    {
        next = listp->next;
        free(listp);
    }
}

Nameval *delitem(Nameval *listp, char *name)
{
    Nameval *p, *prev;
    prev = NULL;
    for (p = listp; p != NULL; p = p->next)
    {
        if (strcmp(p->name, name) == 0)
        {
            if (prev == NULL)
                listp = p->next;
            else
                prev->next = p->next;
            free(p);
            return listp;
        }
        prev = p;
    }
    eprintf("delitem: %s not in list", name);
    return NULL;
}

Nameval *copy(Nameval *old_list)
{
    Nameval *new_list, *p;
    new_list = (Nameval *)emalloc(sizeof(Nameval));
    p = new_list;
    for (; old_list != NULL; old_list = old_list->next)
    { 
        p->next = newitem(old_list->name, old_list->value);
        p = p->next;
    }
    p->next = NULL;
    p = new_list->next;
    free(new_list);
    return p;
}

void print(Nameval *listp)
{
    Nameval *p;
    printf("{ ");
    for (p = listp; p != NULL; p = p->next)
    {
        if (p != listp)
            printf(",");
        printf("%s:%d", p->name, p->value);
    }
    printf(" }\n");
}

Nameval *create_list_for_test(int n)
{
    Nameval *head = NULL;
    int i;
    for (i = 0; i < n; i++)
    {
        char name[20];
        sprintf(name, "key_%d", i);
        head = addfront(head, newitem(name, i));
    }
    return head;
    
}
void test_copy()
{
    Nameval *head, *new;
    head = create_list_for_test(0);
    head = create_list_for_test(1);
    head = create_list_for_test(2);
    print(head);
    new = copy(head);
    print(new);
}

int main()
{ 
    test_copy();
}
