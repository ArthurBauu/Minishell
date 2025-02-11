/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:42:28 by arbaudou          #+#    #+#             */
/*   Updated: 2025/01/10 12:58:01 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_tablen(char **tab)
{
	size_t	len;

	len = 0;
	if (tab != NULL)
	{
		while (tab[len] != NULL)
			len++;
	}
	return (len);
}
