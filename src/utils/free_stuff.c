/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:58:06 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 16:49:22 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_strtab(char **strtab)
{
	int	i;

	i = 0;
	while (strtab[i])
		free(strtab[i++]);
	free(strtab);
}

void	reset_shell(t_shell *shell)
{
	free_all(shell->root, shell->tokens_copy);
	if (shell->fd_in != STDIN_FILENO)
	{
		close(shell->fd_in);
		shell->fd_in = STDIN_FILENO;
	}
	if (shell->fd_out != STDOUT_FILENO)
	{
		close(shell->fd_out);
		shell->fd_out = STDOUT_FILENO;
	}
}
