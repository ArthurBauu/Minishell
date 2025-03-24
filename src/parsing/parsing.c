/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:37:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/24 11:52:21 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_input(char *input)
{
	int	i;

	i = 0;
	if (!input[0])
		return (0);
	while (input[i])
	{
		if ((input[i] == '!' && input[i + 1] == '!') || (input[i] == ':'
				&& input[i + 1] == ':'))
			return (0);
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '!'
			&& input[i] != ':')
			return (0);
		i++;
	}
	return (1);
}

void	parsing(char *input, t_shell *shell)
{
	if (!check_input(input))
		shell->tokens = tokenize(input);
	if (shell->tokens)
	{
		shell->tokens_copy = shell->tokens;
		shell->root = parse(&shell->tokens);
		print_tokens(shell->tokens_copy);
		print_ast(shell->root, 0);
	}
	if (!shell->root)
		g_last_exit_code = EXIT_FAILURE;
}
