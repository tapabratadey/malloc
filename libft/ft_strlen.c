/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 10:53:33 by tadey             #+#    #+#             */
/*   Updated: 2017/12/06 17:47:59 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**returns the length of char string str.
*/

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	return (i);
}
