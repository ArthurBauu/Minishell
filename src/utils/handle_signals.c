/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:57:38 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 20:08:36 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// CTRL-C : clear line and prompt new line
// CTRL-\ : nothing happens
/* handle signals = different quand on est dans un child ou pas */

void	handle_sigint(int sig)
{
	if (sig == 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_last_exit_code = 130;
	}
}

void	stop_sig(int sig)
{
	(void) sig;
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
