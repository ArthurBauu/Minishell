/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:39:28 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/21 12:22:14 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	dup_files(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	save_std_fd(int *saved_stdin, int *saved_stdout, t_shell *shell)
{
	if (shell->pipe == false)
	{
		*saved_stdin = dup(STDIN_FILENO);
		*saved_stdout = dup(STDOUT_FILENO);
	}
}

void	restore_std_fd(int saved_stdin, int saved_stdout, t_shell *shell)
{
	if (shell->pipe == false)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
}

void	reset_fd(t_shell *shell)
{
	change_fd_in(shell, STDIN_FILENO);
	change_fd_out(shell, STDOUT_FILENO);
}
