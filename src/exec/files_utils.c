/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:40:55 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 15:39:51 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	change_fd_in(t_shell *shell, int fd)
{
	if (shell->fd_in != STDIN_FILENO)
		close(shell->fd_in);
	shell->fd_in = fd;
}

void	change_fd_out(t_shell *shell, int fd)
{
	if (shell->fd_out != STDOUT_FILENO)
		close(shell->fd_out);
	shell->fd_out = fd;
}

int	check_infile(char *pathname, t_shell *shell)
{
	int	fd;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		perror_exit(pathname, shell);
	return (fd);
}

int	check_outfile(char *pathname, t_shell *shell)
{
	int	fd;

	if (access(pathname, F_OK) != 0)
		fd = open(pathname, O_CREAT | O_RDWR, 0644);
	else
		fd = open(pathname, O_RDWR | O_TRUNC);
	if (fd == -1)
		perror_exit(pathname, shell);
	return (fd);
}

int	check_outfile_app(char *pathname, t_shell *shell)
{
	int	fd;

	if (access(pathname, F_OK) != 0)
		fd = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(pathname, O_RDWR | O_APPEND);
	if (fd == -1)
		perror_exit(pathname, shell);
	return (fd);
}
