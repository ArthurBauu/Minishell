/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:18:47 by arbaudou          #+#    #+#             */
/*   Updated: 2024/10/18 20:49:16 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*d;

	i = 0;
	d = (unsigned char *)s;
	while (i < n)
	{
		d[i] = (unsigned char)c;
		i++;
	}
	s = (void *)d;
	return (s);
}
