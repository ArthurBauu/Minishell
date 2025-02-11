/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:29:11 by arbaudou          #+#    #+#             */
/*   Updated: 2024/10/24 16:27:30 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy_memory(unsigned char *dest, const unsigned char *src,
	size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = ((unsigned char *)dest);
	s = ((unsigned char *)src);
	if (d < s)
		ft_copy_memory(d, s, n);
	else
	{
		while (i < n)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (dest);
}
