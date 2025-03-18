/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:19:23 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/18 16:14:00 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	**dup_env_tab(char **env)
{
	char	**copy;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (env[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	initialize_shell(t_shell *shell, char **envp)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->tokens_copy = NULL;
	shell->root = NULL;
	shell->env_tab = dup_env_tab(envp);
	shell->env = dup_env(envp, shell);
	shell->exp = dup_env(envp, shell);
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	shell->pipe = false;
	shell->cmd_count = 0;
}
