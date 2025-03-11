/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:49:21 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 19:38:33 by md-harco         ###   ########.fr       */
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

void	exec_ext_command(char *cmd, char **args, t_shell *shell)
{
	char	*path;

	dup_files(shell->fd_in, shell->fd_out);
	if (access(cmd, X_OK) == 0)
		execve(cmd, args, shell->envp);
	else
	{
		path = get_path(cmd, shell->envp);
		if (!path)
		{
			ft_printf_error(2, "minishell: %s: command not found\n", cmd);
			reset_shell(shell);
			exit(127);
		}
		if (execve(path, args, shell->envp) == -1)
			perror_exit("execve", shell);
	}
}

int	execute_single_command(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (is_builtin(node->value[0]))
		return (execute_builtin(node->value[0], node->value, shell));
	pid = fork();
	if (pid < 0)
		perror_exit("fork", shell);
	if (pid == 0)
	{
		signal(SIGINT, &stop_sig);
		exec_ext_command(node->value[0], node->value, shell);
	}
	wait4(pid, &status, 0, NULL);
	signal(SIGINT, &handle_sigint);
	if (WIFEXITED(status))
		g_last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_exit_code = 128 + WTERMSIG(status);
	return (g_last_exit_code);
}

int	execute_command(t_ast *node, t_shell *shell)
{
	char	*path;

	dup_files(shell->fd_in, shell->fd_out);
	if (is_builtin(node->value[0]))
		return (execute_builtin(node->value[0], node->value, shell));
	if (access(node->value[0], X_OK) == 0)
		execve(node->value[0], node->value, shell->envp);
	path = get_path(node->value[0], shell->envp);
	if (!path)
	{
		ft_printf_error(2, "minishell: %s: command not found\n", node->value[0]);
		reset_shell(shell);
		exit(127);
	}
	if (execve(path, node->value, shell->envp) == -1)
		perror_exit("execve", shell);
	return (127);
}
