/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:59:58 by tadey             #+#    #+#             */
/*   Updated: 2018/05/04 17:00:00 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// void    tiny(size_t size, t_malloc *assign)
// {
//     void    *store;
//     int max_size;
//     unsigned long size_of_list;

//     max_size = (TINY * 100) + 4096 - ((TINY * 100) % 4096);

//     store = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
//     assign = (t_malloc*)store;
//     size_of_list = sizeof(t_malloc);
//     assign->for_user = store + size_of_list;
//     assign->space_used = (sizeof(t_malloc) + size);
//     assign->space_free = (max_size - (size + sizeof(t_malloc)));
//     printf("%d", assign->space_used);
// }

// void    *ft_malloc(size_t size)
// {
//     t_malloc *assign;

//     assign = NULL;
//     if (size <= TINY)
//         tiny(size, assign);
//     // else if (TINY < size && size <= 1024)
//     //     small(assign);
//     // else
//     //     large(assign);
//     return (assign->for_user);
// }

/*void    ft_small(t_malloc *assign)
{
    void    *store;
    int max_size;
    unsigned long size_of_list;

    max_size = (SMALL * 100) + 4096 - ((SMALL * 100) % 4096);

    store = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    assign = (t_malloc*)store;
    size_of_list = sizeof(t_malloc);
    assign->for_user = store + size_of_list;
    g_pointer = assign->for_user;
    assign->space_used = (sizeof(t_malloc) + size);
    assign->space_free = (max_size - (size + sizeof(t_malloc)));
}*/

/*void    ft_large(t_malloc *assign)
{
    void    *store;
    int max_size;
    unsigned long size_of_list;

    max_size = (size) + 4096 - ((size * 100) % 4096);

    store = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    assign = (t_malloc*)store;
    size_of_list = sizeof(t_malloc);
    assign->for_user = store + size_of_list;
    g_pointer = assign->for_user;
    assign->space_used = (sizeof(t_malloc) + size);
    assign->space_free = (max_size - (size + sizeof(t_malloc)));
}*/

/*
    void    *ft_malloc(size_t size)
    {
        void            *store;
        t_malloc        *for_used;
        t_malloc        *for_free;
        int             max_size;
        unsigned long   size_of_list;
    
        
        checker(size, max_size);

        store = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

        g_pointer = store;
        
        for_used = (t_malloc*)store;

        for_free = (t_malloc*)(store + sizeof(t_malloc) + size);

        for_used->next = for_free;
        
        for_free->next = NULL;

        size_of_list = sizeof(t_malloc);

        for_used->return_user = *(store + size_of_list); 

        g_pointer = for_used->return_user;

        for_used->total_size = (sizeof(t_malloc) + size);

        for_free->total_size = (max_size - (sizeof(t_malloc) + size + sizeof(t_malloc)));

        return (for_used->return_user);
    }
*/

void checker(size_t size, int max_size)
{
    if (size <= TINY)
        max_size = (TINY * 100) + 4096 - ((TINY * 100) % 4096);
    else if (TINY < size && size <= 1024)
        max_size = (SMALL * 100) + 4096 - ((SMALL * 100) % 4096);
    else
        max_size = (size) + 4096 - ((size * 100) % 4096);
}

// void    *ft_malloc(size_t size)
// {
//     t_malloc *for_used;
//     t_malloc *for_free;
//     int      max_size = 0;
//     unsigned long   size_of_list;
    
//     checker(size, max_size);

//     if (g_pointer == NULL)
//         g_pointer = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
//     for_used = mmap(0, max_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

//     g_pointer->tiny = for_used;
//     for_free = (t_malloc*)(g_pointer + sizeof(t_malloc) + size);
//     for_used->next = for_free;
//     for_free->next = NULL;
//     size_of_list = sizeof(t_malloc);
//     for_used->return_user = g_pointer + size_of_list;
//     for_used->total_size = (sizeof(t_malloc) + size);
//     for_free->total_size = (max_size - (sizeof(t_malloc) + size + sizeof(t_malloc)));
//     return (for_used->return_user);
}



int main()
{
    char *first;
    // char *second;
    // char *third;

    first = ft_malloc(10);
    printf("%s\n", ft_strcpy(first, "tapabratad"));
    // second = ft_malloc(5);
    // printf("%s\n\n", ft_strcpy(first, "tapdfsdfdfsfa"));
    // third = malloc(9);
    // printf("%s", ft_strcpy(first, "blahblah"));
    return (0);
}
