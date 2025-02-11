/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:05:29 by arbaudou          #+#    #+#             */
/*   Updated: 2024/10/24 16:59:44 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*nstr;
	size_t	i;

	i = 0;
	nstr = malloc(nmemb * size);
	if (!nstr)
		return (NULL);
	while (i < nmemb * size)
	{
		nstr[i] = 0;
		i++;
	}
	return (nstr);
}
