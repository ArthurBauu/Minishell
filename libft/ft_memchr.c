/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:03:16 by arbaudou          #+#    #+#             */
/*   Updated: 2024/10/18 22:06:13 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*a;

	i = 0;
	a = (unsigned char *)s;
	while (i < n)
	{
		if (a[i] == (unsigned char)c)
			return ((void *)&a[i]);
		i++;
	}
	return (NULL);
}
