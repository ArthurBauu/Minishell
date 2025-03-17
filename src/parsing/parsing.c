/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:37:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/14 20:24:58 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_quotes(char *input)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	s = 0;
	d = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			s++;
		if (input [i] == '"')
			d++;
		i++;
	}
	if (s % 2)
		return (ft_printf_error(2, "minishell: single quote not closed\n",
			1));
		
	if (d % 2)
		return (ft_printf_error(2, "minishell: double quote not closed\n",
			1));
	return (0);
}

int	check_input(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] == '!' && input[i + 1] == '!')
			|| (input[i] == ':' && input[i + 1] == ':'))
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
	if (!check_input(input) && !check_quotes(input))
		shell->tokens = tokenize(input);
	if (shell->tokens)
	{
		shell->tokens_copy = shell->tokens;
		shell->root = parse(&shell->tokens);
		print_ast(shell->root, 0);
	}
}