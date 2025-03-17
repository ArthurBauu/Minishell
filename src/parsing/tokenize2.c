/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:27:05 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/14 20:19:37 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	handle_and(char *input, int i, t_token **tokens)
{
	(void)input;
	add_token(tokens, AND, "&&");
	i += 2;
	return (i);
}

int	handle_or(char *input, int i, t_token **tokens)
{
	(void)input;
	add_token(tokens, OR, "||");
	i += 2;
	return (i);
}

int	handle_pipe(char *input, int i, t_token **tokens)
{
	if (input[i] == '|' && input[i + 1] == '|')
	{
		add_token(tokens, OR, "||");
		i += 2;
		return (i);
	}
	else
		add_token(tokens, PIPE, "|");
	i++;
	return (i);
}

int    handle_redirection_out(char *input, int i, t_token **tokens)
{
	if (input[i + 1] == '>')
	{
		if (input[i + 2] != '|' && input[i + 2] != '\0')
		{
			add_token(tokens, REDIR_APPEND, ">>");
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
		add_token(tokens, REDIR_OUT, ">");
		i++;
	}
	return (i);
}

int    handle_redirection_in(char *input, int i, t_token **tokens)
{
	if (input[i + 1] == '<')
	{
		if (input[i + 2] != '|' && input[i + 2] != '\0')
		{
			add_token(tokens, HEREDOC, "<<");
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
		add_token(tokens, REDIR_IN, "<");
		i++;
	}
	return (i);
}
