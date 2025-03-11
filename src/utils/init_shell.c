/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:19:23 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 19:48:35 by md-harco         ###   ########.fr       */
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
	shell->pipe = false;
	shell->cmd_count = 0;
}
