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

int main()
{
    char *first;
    char *second;
    // char *third;
    printf("\n---INFO---\n\n");
    first = ft_malloc(10);
    printf("%s\n\n", ft_strcpy(first, "tapabratad"));
    second = ft_malloc(5);
    printf("%s\n\n", ft_strcpy(second, "tapdfsdfdfsfa"));
    // third = malloc(9);
    // printf("%s", ft_strcpy(first, "blahblah"));
    return (0);
}
