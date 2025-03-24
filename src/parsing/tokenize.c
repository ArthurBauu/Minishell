/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:32:54 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/23 23:11:13 by arbaudou         ###   ########.fr       */
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
		ft_printf("--debug--\n");
	}
	add_token(tokens, WORD, word, 0);
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
			ft_printf("--debug--\n");
		}
		add_token(tokens, WORD, word, 2);
		free(word);
		return (i + 1);
	}
	ft_printf_error(2, "minishell: double quotes not closed\n");
	return (-1);
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
			ft_printf("--debug--\n");
		}
		add_token(tokens, WORD, word, 1);
		free(word);
		return (i + 1);
	}
	ft_printf_error(2, "minishell: single quote not closed\n");
	return (-1);
}

/* FONCTION TROP LONGUE IL FAUT QUE JE LA RACOURCISSE */

int	process_token(char *input, int i, t_token **tokens)
{
	if (input[i] == '|')
		return (handle_pipe(input, i, tokens));
	else if (input[i] == '>')
		return (handle_redirection_out(input, i, tokens));
	else if (input[i] == '<')
		return (handle_redirection_in(input, i, tokens));
	else if (input[i] == '"')
		return (handle_double_quote(input, i, tokens));
	else if (input[i] == '\'')
		return (handle_single_quote(input, i, tokens));
	else if (input[i] == '&' && input[i + 1] == '&')
		return (handle_and(input, i, tokens));
	else
		return (handle_word(input, i, tokens));
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else
		{
			i = process_token(input, i, &tokens);
			if (i == -1)
				return (free_tokens(tokens), NULL);
		}
	}
	return (tokens);
}
