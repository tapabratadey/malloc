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

t_malloc *small(size_t size, t_malloc *for_used, t_malloc *for_free)
{
    int max_size;
    unsigned long size_of_list;

    max_size = (SMALL * 100) + 4096 - ((SMALL * 100) % 4096);

    if (g_pointer == NULL)
        g_pointer = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    for_used = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    g_pointer->large = for_used;
    for_free = (t_malloc *)(for_used + sizeof(t_malloc) + size);
    for_used->next = for_free;
    for_free->next = NULL;
    size_of_list = sizeof(t_malloc);
    for_used->return_user = for_used + size_of_list;
    for_used->total_size = (sizeof(t_malloc) + size);
    for_free->total_size = (max_size - (size_of_list + size + size_of_list));
    return (for_used);
}

t_malloc *large(size_t size, t_malloc *for_used, t_malloc *for_free)
{
    int max_size;
    unsigned long size_of_list;

    max_size = (size) + 4096 - ((size * 100) % 4096);

    if (g_pointer == NULL)
        g_pointer = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    for_used = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    g_pointer->large = for_used;
    for_free = (t_malloc *)(for_used + sizeof(t_malloc) + size);
    for_used->next = for_free;
    for_free->next = NULL;
    size_of_list = sizeof(t_malloc);
    for_used->return_user = for_used + size_of_list;
    for_used->total_size = (sizeof(t_malloc) + size);
    for_free->total_size = (max_size - (size_of_list + size + size_of_list));
    return (for_used);
}

t_malloc *tiny(size_t size, t_malloc *for_used, t_malloc *for_free)
{
    int max_size;
    unsigned long size_of_list;

    max_size = (TINY * 100) + 4096 - ((TINY * 100) % 4096);
    if (g_pointer == NULL)
        g_pointer = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    if (g_pointer->status == 1 && g_pointer != NULL)
    {
        g_pointer->tiny->total_size = g_pointer->tiny->total_size + size;
        g_pointer->tiny->next->total_size = (max_size - (g_pointer->tiny->total_size + size));
        g_pointer->tiny->return_user = g_pointer->tiny->next->return_user;
        g_pointer->tiny->next->return_user = g_pointer->tiny->next->return_user + size;

        printf("size asked by malloc: %zu\n", size);
        printf("max_size of mem space: %d\n", max_size);
        printf("address for g_pointer->tiny: %p\n", g_pointer->tiny);
        printf("address for g_pointer->tiny->next: %p\n", g_pointer->tiny->next);
        printf("address for the user: %p\n", g_pointer->tiny->return_user);
        printf("total size used: %zu\n", g_pointer->tiny->total_size);
        printf("total size left: %zu\n", g_pointer->tiny->next->total_size);
        // printf("global used: %zu\n", g_pointer->tiny->total_size);
        // printf("global free: %zu\n", g_pointer->tiny->next->total_size);
        return (g_pointer->tiny->return_user);
    }
    for_used = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    size_of_list = sizeof(t_malloc);
    g_pointer->tiny = for_used;
    for_free = (t_malloc *)(for_used + size_of_list + size);
    for_used->next = for_free;
    for_free->next = NULL;
    for_used->return_user = for_used + size_of_list;
    for_used->total_size = (size_of_list + size);
    for_free->return_user = (t_malloc *)(for_used + size_of_list + size);
    for_free->total_size = (max_size - (size_of_list + size + size_of_list));

    add_to_end_of_list(g_pointer->tiny, for_free);
    if (g_pointer->tiny->next->total_size < (size_t)max_size)
        g_pointer->status = 1;

    printf("size asked by malloc: %zu\n", size);
    printf("max_size of mem space: %d\n", max_size);
    printf("address for used node: %p\n", for_used);
    printf("address for free node: %p\n", for_free);
    printf("address for the user: %p\n", for_used->return_user);
    printf("total size used: %zu\n", for_used->total_size);
    printf("total size left: %zu\n", for_free->total_size);
    // printf("address for the user: %p\n", for_used->return_user);
    // printf("status: %d\n", g_pointer->status);
    // printf("global used: %zu\n", g_pointer->tiny->total_size);
    // printf("global free: %zu\n", g_pointer->tiny->next->total_size);
    // printf("ADDRESS_FOR_G_POINTER->TINY: %p\n", g_pointer->tiny);
    // printf("ADDRESS_FOR_FREE: %p\n", for_free);
    // printf("size_of_list: %lu\n", size_of_list);
    return (for_used);
}

void add_to_end_of_list(t_malloc *list_head, t_malloc *add_this)
{
    t_malloc *iter;
    iter = list_head;
    while (iter)
    {
        if (iter->next == NULL)
        {
            iter->next = add_this;
            return;
        }
        iter = iter->next;
    }
}

void *ft_malloc(size_t size)
{
    t_malloc *for_used = NULL;
    t_malloc *for_free = NULL;
    if (size <= TINY)
        for_used = tiny(size, for_used, for_free);
    else if (TINY < size && size <= 1024)
        for_used = small(size, for_used, for_free);
    else
        for_used = large(size, for_used, for_free);
    return (for_used->return_user);
}

// void print_list_elem(t_malloc *iter)
// {
//     printf("Elem Addr: %p, Pointer for user: %p, Size: %lu, Status: %d, Next: %p\n", iter, iter->return_user, iter->total_size, iter->status, iter->next);
// }

// void print_list(t_malloc *list_head)
// {
//     t_malloc *iter;
//     iter = list_head;
//     while (iter)
//     {
//         print_list_elem(iter);
//         iter = iter->next;
//     }
// }

// void *ft_malloc(size_t size)
// {
//     t_malloc *for_used;
//     t_malloc *for_free;
//     int max_size;
//     unsigned long size_of_list;

//     max_size = 0;
//     // check if size is tiny/small/large
//     // based on it we will get 128/1024/size block of segments from mmap
//     // based on size we will find it's max size
//     // max_size = (size * 100) + 4096 - ((size * 100) % 4096)

//     if (size <= TINY)
//         max_size = (TINY * 100) + 4096 - ((TINY * 100) % 4096);
//     else if (TINY < size && size <= 1024)
//         max_size = (SMALL * 100) + 4096 - ((SMALL * 100) % 4096);
//     else
//         max_size = (size) + 4096 - ((size * 100) % 4096);

//     //allocate that space i.e my chocolate bar to my global
//     if (g_pointer == NULL)
//         g_pointer = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
//     for_used = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

//     // assign used and free nodes
//     // since i want my t_list to point at the begining of the mem space
//     // i can set the pointer to where store points to.
//     // for_free would point to store + size_of(t_malloc) + size
//     g_pointer->tiny = for_used;
//     for_free = (t_malloc *)(for_used + sizeof(t_malloc) + size);
//     for_used->next = for_free;
//     for_free->next = NULL;

//     // calculate the size of list t_malloc i.e sizeof(t_malloc));
//     size_of_list = sizeof(t_malloc);

//     // assign bytes asked for by malloc after allocating space for t_malloc
//     for_used->return_user = g_pointer + size_of_list;

//     // // use the global to keep upgrading the pointer

//     // g_pointer = for_used->return_user;

//     // find the space used (size asked for + sizeof t_list)
//     for_used->total_size = (sizeof(t_malloc) + size);

//     // find the space remaining (max_size - (size asked for + sizeof t_list))
//     for_free->total_size = (max_size - (size_of_list + size + size_of_list));
//     // printf("Print all: ");
//     // print_list(g_pointer->tiny);

//     //before returning memory to user check if there's space left in mem
//     // if (for_used->total_size < (size_t)max_size)
//     //     for_used->status = 1;
//     // else
//     //     for_used->status = 0;

//     // print_list(for_used);
//     printf("size asked by malloc: %zu\n", size);
//     printf("max_size of mem space: %d\n", max_size);
//     printf("ADDRESS_FOR_G_POINTER: %p\n", g_pointer);
//     printf("ADDRESS_FOR_USED: %p\n", for_used);
//     printf("ADDRESS_FOR_G_POINTER->TINY: %p\n", g_pointer->tiny);
//     printf("ADDRESS_FOR_FREE: %p\n", for_free);
//     printf("size_of_list: %lu\n", size_of_list);
//     printf("ADDRESS_FOR_USER: %p\n", for_used->return_user);
//     printf("ADDRESS_G_POINTER_UPGRD: %p\n", g_pointer);
//     printf("space_used: %zu\n", for_used->total_size);
//     printf("space_free: %zu\n\n", for_free->total_size);

//     // return size asked for by the user. *(pointer + t_list)
//     return (for_used->return_user);
// }

/*
** PRINTING

    printf("size asked by malloc: %zu\n", size);
    printf("max_size of mem space: %d\n", max_size);
    printf("ADDRESS_FOR_G_POINTER: %p\n", g_pointer);
    printf("ADDRESS_FOR_USED: %p\n", for_used);
    printf("ADDRESS_FOR_G_POINTER->TINY: %p\n", g_pointer->tiny);
    printf("ADDRESS_FOR_FREE: %p\n", for_free);
    printf("size_of_list: %lu\n", size_of_list);
    printf("ADDRESS_FOR_USER: %p\n", for_used->return_user);
    printf("space_used: %zu\n", for_used->total_size);
    printf("space_free: %zu\n\n", for_free->total_size);
*/