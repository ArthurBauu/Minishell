/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:19:23 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/14 20:31:09 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
	shell->envp = dup_env(envp);
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	shell->root = NULL;
	shell->tokens = NULL;
	shell->tokens_copy = NULL;
	shell->pipe = false;
	shell->cmd_count = 0;
}
