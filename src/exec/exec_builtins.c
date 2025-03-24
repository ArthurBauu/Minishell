/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:36:01 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/20 13:36:25 by md-harco         ###   ########.fr       */
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
	int	result;
	int	saved_stdin;
	int	saved_stdout;

	save_std_fd(&saved_stdin, &saved_stdout, shell);
	dup_files(shell->fd_in, shell->fd_out);
	n = ft_strlen(cmd) + 1;
	if (ft_strncmp(cmd, "echo", n) == 0)
		result = ft_echo(args);
	else if (ft_strncmp(cmd, "cd", n) == 0)
		result = ft_cd(args, shell);
	else if (ft_strncmp(cmd, "pwd", n) == 0)
		result = ft_pwd(args);
	else if (ft_strncmp(cmd, "export", n) == 0)
		result = ft_export(args, shell);
	else if (ft_strncmp(cmd, "unset", n) == 0)
		result = ft_unset(args, shell);
	else if (ft_strncmp(cmd, "env", n) == 0)
		result = ft_env(args, shell);
	else
		result = ft_exit(args, shell);
	restore_std_fd(saved_stdin, saved_stdout, shell);
	g_last_exit_code = result;
	return (result);
}
