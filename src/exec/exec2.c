/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:49:21 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/03 17:35:42 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(char *cmd)
{
	int	n;

	n = ft_strlen(cmd) + 1;
	if (ft_strncmp(cmd, "echo", n) == 0 || ft_strncmp(cmd, "cd", n) == 0
		|| ft_strncmp(cmd, "pwd", n) == 0 || ft_strncmp(cmd, "export", n) == 0
		|| ft_strncmp(cmd, "unset", n) == 0 || ft_strncmp(cmd, "env", n) == 0
		|| ft_strncmp(cmd, "exit", n) == 0)
		return (1);
	return (0);
}

int	execute_builtin(char *cmd, char **args, t_shell *shell)
{
	int	n;

	n = ft_strlen(cmd) + 1;
	if (ft_strncmp(cmd, "echo", n) == 0)
		return (ft_echo(args));
	if (ft_strncmp(cmd, "cd", n) == 0)
		return (ft_cd(args, shell));
	if (ft_strncmp(cmd, "pwd", n) == 0)
		return (ft_pwd(args));
	if (ft_strncmp(cmd, "export", n) == 0)
		return (ft_export(args, shell));
	if (ft_strncmp(cmd, "unset", n) == 0)
		return (ft_unset(args, shell));
	if (ft_strncmp(cmd, "env", n) == 0)
		return (ft_env(args, shell));
	return (ft_exit(args, shell));
}

void	error_command(char *cmd, t_shell *shell)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	free_shell(shell);
	exit(127);
}
