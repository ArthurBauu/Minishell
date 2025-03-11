/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:32:54 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/12 00:01:04 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_word(char *input, int i, t_token **tokens)
{
	int		start;
	char	*word;

	start = i;
	while (input[i] && !is_space(input[i]) && input[i] != '|' && input[i] != '<'
		&& input[i] != '>')
		i++;
	word = ft_strndup(&input[start], (i - start));
	if (!word)
	{
		printf("--debug--\n");
	}
	add_token(tokens, WORD, word);
	free(word);
	return (i);
}

int	handle_double_quote(char *input, int i, t_token **tokens)
{
	int		start;
	char	*word;

	i++;
	start = i;
	while (input[i] && input[i] != '"')
		i++;
	if (input[i] == '"')
	{
		word = ft_strndup(&input[start], (i - start));
		if (!word)
		{
			printf("--debug--\n");
		}
		add_token(tokens, WORD, word);
		free(word);
		return (i + 1);
	}
	printf("Error : double quote not closed.\n");
	return (i);
}

int	handle_single_quote(char *input, int i, t_token **tokens)
{
	int		start;
	char	*word;

	i++;
	start = i;
	while (input[i] && input[i] != '\'')
		i++;
	if (input[i] == '\'')
	{
		word = ft_strndup(&input[start], (i - start));
		if (!word)
		{
			printf("--debug--\n");
		}
		add_token(tokens, WORD, word);
		free(word);
		return (i + 1);
	}
	printf("Error : single quote not closed.\n");
	return (i);
}

/* FONCTION TROP LONGUE IL FAUT QUE JE LA RACOURCISSE */

t_token	*tokenize(char *input)
{
	t_token *tokens = NULL;
	int i = 0;

	if (!input[i])
		ft_putstr_fd("minishell: no command found\n", 2);
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '|')
			i = handle_pipe(input, i, &tokens);
		else if (input[i] == '>')
		{
			i = handle_redirection_out(input, i, &tokens);
			if (i == -1)
				return (free_tokens(tokens), NULL);
		}
		else if (input[i] == '<')
		{
			i = handle_redirection_in(input, i, &tokens);
			if (i == -1)
				return (free_tokens(tokens), NULL);
		}
		else if (input[i] == '"')
			i = handle_double_quote(input, i, &tokens);
		else if (input[i] == '\'')
			i = handle_single_quote(input, i, &tokens);
		else if (input[i] == '&' && input[i + 1] == '&')
			i = handle_and(input, i, &tokens);
		else
			i = handle_word(input, i, &tokens);
	}
	return (tokens);
}
