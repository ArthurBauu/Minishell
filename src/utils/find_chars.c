/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:42:49 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/13 16:46:38 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	count_char(char *str, char c, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && i < n)
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (n);
}
