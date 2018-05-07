/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:52:25 by tadey             #+#    #+#             */
/*   Updated: 2018/05/04 16:52:27 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void print_list_elem(t_malloc *iter)
{
    printf("Elem Addr: %p, Pointer for user: %p, Size: %lu, Status: %d, Next: %p\n", iter, iter->return_user, iter->total_size, iter->status, iter->next);
}

void print_list(t_malloc *list_head)
{
    t_malloc *iter;
    iter = list_head;
    while (iter)
    {
        print_list_elem(iter);
        iter = iter->next;
    }
}

void *ft_malloc(size_t size)
{
    t_malloc *for_used;
    t_malloc *for_free;
    int max_size;
    unsigned long size_of_list;

    max_size = 0;
    // check if size is tiny/small/large
    // based on it we will get 128/1024/size block of segments from mmap
    // based on size we will find it's max size
    // max_size = (size * 100) + 4096 - ((size * 100) % 4096)
    
    checker(size, max_size);

    if (size <= TINY)
        max_size = (TINY * 100) + 4096 - ((TINY * 100) % 4096);
    else if (TINY < size && size <= 1024)
        max_size = (SMALL * 100) + 4096 - ((SMALL * 100) % 4096);
    else
        max_size = (size) + 4096 - ((size * 100) % 4096);

    //allocate that space i.e my chocolate bar to my global
    if (g_pointer == NULL)
        g_pointer = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    for_used = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    // assign used and free nodes
    // since i want my t_list to point at the begining of the mem space
    // i can set the pointer to where store points to.
    // for_free would point to store + size_of(t_malloc) + size
    g_pointer->tiny = for_used;
    for_free = (t_malloc *)(g_pointer + sizeof(t_malloc) + size);
    for_used->next = for_free;
    for_free->next = NULL;

    // calculate the size of list t_malloc i.e sizeof(t_malloc));
    size_of_list = sizeof(t_malloc);
    

    // assign bytes asked for by malloc after allocating space for t_malloc
    for_used->return_user = g_pointer + size_of_list;
    

    // // use the global to keep upgrading the pointer
    
    // g_pointer = for_used->return_user;
    

    // find the space used (size asked for + sizeof t_list)
    for_used->total_size = (sizeof(t_malloc) + size);
   

    // find the space remaining (max_size - (size asked for + sizeof t_list))
    for_free->total_size = (max_size - (sizeof(t_malloc) + size + sizeof(t_malloc)));
    printf("Print all: ");
    print_list(g_pointer->tiny);

    //before returning memory to user check if there's space left in mem
    if (for_used->total_size < (size_t)max_size)
        for_used->status = 1;
    else
        for_used->status = 0;

    // print_list(for_used);

    // return size asked for by the user. *(pointer + t_list)
    return (for_used->return_user);
}

/*
** PRINTING
printf("ADDRESS_FOR_G_POINTER1: %p\n", g_pointer);
printf("max_size of mem space: %d\n", max_size);
printf("size asked by malloc: %zu\n", size);
printf("ADDRESS_FOR_STORE: %p\n", store);
printf("ADDRESS_FOR_G_POINTER: %p\n", g_pointer);
printf("ADDRESS_FOR_USED: %p\n", for_used);
printf("ADDRESS_FOR_FREE: %p\n", for_free);
printf("size_of_list: %lu\n", size_of_list);
printf("ADDRESS_FOR_USER: %p\n", for_used->return_user);
printf("ADDRESS_G_POINTER_UPGRD: %p\n", g_pointer);
printf("space_used: %d\n", for_used->total_size);
printf("space_free: %d\n", for_free->total_size);
printf("status: %d\n", for_used->status);
*/