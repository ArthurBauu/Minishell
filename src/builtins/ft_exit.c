/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:33:36 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 13:44:39 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

int	ft_exit(char **args, t_shell *shell)
{
	int	status;
	int	temp;

	status = EXIT_SUCCESS;
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (args[1] && !ft_isnum(args[1]))
		ft_printf_error(2, "minishell: exit: %s: numeric argument required\n",
			args[1]);
	else if (args[1])
	{
		temp = ft_atoi(args[1]);
		if (temp >= 0 && temp <= 255)
			status = temp;
	}
	ft_printf("exit\n");
	reset_shell(shell);
	free_strtab(shell->envp);
	rl_clear_history();
	exit(status);
}
