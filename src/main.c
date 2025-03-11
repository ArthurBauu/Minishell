/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:34:22 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/11 16:52:47 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	g_last_exit_code;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*input;

	if (ac != 1 || !av[0])
		return (1);
	initialize_shell(&shell, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (input)
		{
			parsing(input, &shell);
			if (shell.root)
				execute_ast(shell.root, &shell);
		}
		else
		{
			printf("exit\n");
			exit(g_last_exit_code);
		}
		add_history(input);
		free(input);
		reset_shell(&shell);
	}
	return (0);
}
