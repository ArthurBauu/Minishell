/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:32:54 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/11 16:26:32 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// t_token	*tokenize(char *input)
// {
// 	t_token	*tokens;
// 	int		i;
// 	int		start;
// 	char	*word;

// 	tokens = NULL;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == ' ')
// 		{
// 			i++;
// 			continue ;
// 		}
// 		if (input[i] == '|')
// 		{
// 			add_token(&tokens, PIPE, "|");
// 			i++;
// 		}
// 		else if (input[i] == '>')
// 		{
// 			if ((input[i + 1]) == '>')
// 			{
// 				add_token(&tokens, APPEND, ">>");
// 				i += 2;
// 			}
// 			else
// 			{
// 				add_token(&tokens, REDIR_OUT, ">");
// 				i++;
// 			}
// 		}
// 		else if (input[i] == '<')
// 		{
// 			if (input[i + 1] == '<')
// 			{
// 				add_token(&tokens, HEREDOC, "<<");
// 				i += 2;
// 			}
// 			else
// 			{
// 				add_token(&tokens, REDIR_IN, "<");
// 				i++;
// 			}
// 		}
// 		else
// 		{
// 			start = i;
// 			while (input[i] && !is_space(input[i]) && input[i] != '|'
// 				&& input[i] != '<' && input[i] != '>')
// 				i++;
// 			word = ft_strndup((input + start), (i - start));
// 			if (!word)
// 			{
// 				printf("--debug--\n");
// 			}
// 			add_token(&tokens, WORD, word);
// 			free(word);
// 		}
// 	}
// 	return (tokens);
// }

int	handle_pipe(char *input, int i, t_token **tokens)
{
	(void)input;
	add_token(tokens, PIPE, "|");
	i++;
	return (i);
}

int	handle_redirection_out(char *input, int i, t_token **tokens)
{
	if ((input[i + 1]) == '>')
	{
		add_token(tokens, APPEND, ">>");
		i += 2;
	}
	else
	{
		add_token(tokens, REDIR_OUT, ">");
		i++;
	}
	return (i);
}

int	handle_redirection_in(char *input, int i, t_token **tokens)
{
	if (input[i + 1] == '<')
	{
		add_token(tokens, HEREDOC, "<<");
		i += 2;
	}
	else
	{
		add_token(tokens, REDIR_IN, "<");
		i++;
	}
	return (i);
}

int	handle_word(char *input, int i, t_token **tokens)
{
	int start;
	char *word;
	
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
	int start;
	char *word;
	
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
	int start;
	char *word;
	
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

t_token	*tokenize(char *input)
{
	t_token *tokens = NULL;
	int i = 0;

	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '|')
			i = handle_pipe(input, i, &tokens);
		else if (input[i] == '>')
			i = handle_redirection_out(input, i, &tokens);
		else if (input[i] == '<')
			i = handle_redirection_in(input, i, &tokens);
		else if (input[i] == '"')
			i = handle_double_quote(input, i, &tokens);
		else if (input[i] == '\'')
			i = handle_single_quote(input, i, &tokens);
		else
			i = handle_word(input, i, &tokens);
	}
	return (tokens);
}