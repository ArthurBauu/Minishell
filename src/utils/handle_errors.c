/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:58:34 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/20 16:13:06 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	perror_exit(char *msg, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
	if (shell->pipe == false)
	{
		reset_shell(shell);
		free_strtab(shell->env_tab);
		clear_env(&shell->env);
		clear_env(&shell->exp);
	}
	exit(EXIT_FAILURE);
}
