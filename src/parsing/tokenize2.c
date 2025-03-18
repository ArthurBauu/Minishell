/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:27:05 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/18 15:13:32 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	handle_and(char *input, int i, t_token **tokens)
{
	(void)input;
	add_token(tokens, AND, "&&", 0);
	i += 2;
	return (i);
}

int	handle_or(char *input, int i, t_token **tokens)
{
	(void)input;
	add_token(tokens, OR, "||", 0);
	i += 2;
	return (i);
}

int	handle_pipe(char *input, int i, t_token **tokens)
{
	if (input[i] == '|' && input[i + 1] == '|')
	{
		add_token(tokens, OR, "||", 0);
		i += 2;
		return (i);
	}
	else
		add_token(tokens, PIPE, "|", 0);
	i++;
	return (i);
}

int    handle_redirection_out(char *input, int i, t_token **tokens)
{
	if (input[i + 1] == '>')
	{
		if (input[i + 2] != '|')
		{
			add_token(tokens, REDIR_APPEND, ">>", 0);
			i += 2;
		}
		else
		return (print_errors(5), -1);
	}
	else
	{
		if (input[i + 1] == '\0' || input[i + 1] == '|'
			|| input[i + 1] == '&')
			return (print_errors(6), -1);
		add_token(tokens, REDIR_OUT, ">", 0);
		i++;
	}
	return (i);
}

int    handle_redirection_in(char *input, int i, t_token **tokens)
{
	if (input[i + 1] == '<')
	{
		if (input[i + 2] != '|')
		{
			add_token(tokens, HEREDOC, "<<", 0);
			i += 2;
		}
		else
			return (print_errors(3), -1);
	}
	else
	{
		if (input[i + 1] == '\0' || input[i + 1] == '|'
			|| input[i + 1] == '&')
			return (print_errors(4), -1);
		add_token(tokens, REDIR_IN, "<", 0);
		i++;
	}
	return (i);
}
