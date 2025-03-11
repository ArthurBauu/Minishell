/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:46:44 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/10 16:04:09 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_echo(char **args)
{
	int		i;
	bool	newline;

	if (ft_strncmp(args[1], "-n", 3) == 0)
	{
		i = 2;
		newline = false;
	}
	else
	{
		i = 1;
		newline = true;
	}
	while (args[i] && args[i + 1])
		ft_printf("%s ", args[i++]);
	if (newline == true)
		ft_printf("%s\n", args[i]);
	else
		ft_printf("%s", args[i]);
	return (EXIT_SUCCESS);
}
