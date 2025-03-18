/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:58:06 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/18 18:03:27 by arbaudou         ###   ########.fr       */
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
	if (shell->root)
		free_all(shell->root, shell->tokens_copy);
	printf("exit\n");
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

void	clear_env(t_env **env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (*env)
	{
		temp = (*env)->next;
		free((*env)->name);
		free((*env)->value);
		free(*env);
		*env = temp;
	}
}
