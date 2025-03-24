/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:49:21 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/21 11:57:14 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	test_if_directory(char *path, t_shell *shell)
{
	struct stat	*buf;

	buf = malloc(sizeof(struct stat));
	if (stat(path, buf) == 0)
	{
		if (S_ISDIR(buf->st_mode))
		{
			free(buf);
			ft_printf_error(2, "minishell: %s: Is a directory\n", path);
			clear_all(shell);
			exit(126);
		}
		else if (S_ISREG(buf->st_mode) && access(path, X_OK))
		{
			free(buf);
			ft_printf_error(2, "minishell: %s: Permission denied\n", path);
			clear_all(shell);
			exit(126);
		}
	}
	free(buf);
}

void	exec_ext_command(char *cmd, char **args, t_shell *shell)
{
	char		*path;

	dup_files(shell->fd_in, shell->fd_out);
	test_if_directory(cmd, shell);
	if (access(cmd, X_OK) == 0)
		execve(cmd, args, shell->env_tab);
	else
	{
		path = get_path(cmd, shell->env_tab);
		if (!path)
		{
			ft_printf_error(2, "minishell: %s: command not found\n", cmd);
			clear_all(shell);
			exit(127);
		}
		if (execve(path, args, shell->env_tab) == -1)
			perror_exit("execve", shell);
	}
}

int	execute_single_command(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (node->value[0][0] == '\0')
		return (0);
	if (is_builtin(node->value[0]))
		return (execute_builtin(node->value[0], node->value, shell));
	pid = fork();
	if (pid < 0)
		perror_exit("fork", shell);
	if (pid == 0)
	{
		setup_child_signals();
		exec_ext_command(node->value[0], node->value, shell);
	}
	wait4(pid, &status, 0, NULL);
	if (WIFEXITED(status))
		g_last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_exit_code = 128 + WTERMSIG(status);
	return (g_last_exit_code);
}

int	execute_command(t_ast *node, t_shell *shell)
{
	char		*path;

	setup_child_signals();
	if (node->value[0][0] == '\0')
		return (0);
	dup_files(shell->fd_in, shell->fd_out);
	if (is_builtin(node->value[0]))
		return (execute_builtin(node->value[0], node->value, shell));
	test_if_directory(node->value[0], shell);
	if (access(node->value[0], X_OK) == 0)
		execve(node->value[0], node->value, shell->env_tab);
	path = get_path(node->value[0], shell->env_tab);
	if (!path)
	{
		ft_printf_error(2, "minishell: %s: command not found\n", node->value[0]);
		clear_all(shell);
		exit(127);
	}
	if (execve(path, node->value, shell->env_tab) == -1)
		perror_exit("execve", shell);
	return (127);
}
