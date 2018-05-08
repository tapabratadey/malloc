/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 17:00:58 by tadey             #+#    #+#             */
/*   Updated: 2018/05/04 17:00:59 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
#include <unistd.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/mman.h>
#include "libft/libft.h"
#define TINY 128
#define SMALL 1024

typedef struct      s_malloc
{
    size_t             total_size;
    // int             status;
    void            *return_user;
    struct s_malloc   *next;
}                   t_malloc;

typedef struct      s_all
{
    t_malloc        *tiny;
    t_malloc        *small;
    t_malloc        *large;
    int             status;
}                   t_all;

t_all               *g_pointer;

void        ft_free(void *ptr);
void        *ft_malloc(size_t size);
void        *ft_realloc(void *ptr, size_t size);

t_malloc    *tiny(size_t size, t_malloc *for_used, t_malloc *for_free);
t_malloc    *small(size_t size, t_malloc *for_used, t_malloc *for_free);
t_malloc    *large(size_t size, t_malloc *for_used, t_malloc *for_free);

void        add_to_end_of_list(t_malloc *list_head, t_malloc *add_this);

// void checker(size_t size, int max_size);

#endif