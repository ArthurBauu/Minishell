/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:12:43 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/06 16:49:31 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_split(char **split)
{
	int	i;

	if (!split)
	{
		ft_putstr_fd("minishell: split is NULL\n", 2);
		return;
	}
	i = 0;
	while (split[i])
	{
		ft_printf("%i\n", i);
		ft_printf("%s\n", split[i]);
		ft_printf("%i\n", i);
		i++;
	}
}
