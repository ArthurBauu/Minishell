/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:20:23 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/21 01:24:23 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	return (new_token);
}

t_token	*add_token(t_token **head, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = create_token(type, value);
	if (!new_token)
		return (NULL);
	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	return (new_token);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: %-10s | Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_redirection(t_token *token, int n)
{
	if (!token)
		return (0);
	if (token->type == REDIR_OUT || token->type == REDIR_IN
		|| token->type == REDIR_APPEND || token->type == HEREDOC)
	{
		if (n == 1 && (token->type == REDIR_OUT || token->type == REDIR_IN))
			ft_putstr_fd("minishell: syntax error near unexpected token '<'\n",
				2);
		else if (n == 1 && token->type == REDIR_APPEND)
			ft_putstr_fd("minishell: syntax error near unexpected token '>>'\n",
				2);
		else if (n == 1 && token->type == HEREDOC)
			ft_putstr_fd("minishell: syntax error near unexpected token '<<'\n",
				2);
		return (1);
	}
	else if (token->type == PIPE)
	{
		if (n == 1)
			ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",
				2);
		return (1);
	}
	return (0);
}

const char	*get_ast_type_str(t_ast_type type)
{
	if (type == NODE_PIPE)
		return ("|");
	else if (type == NODE_REDIR_IN)
		return ("<");
	else if (type == NODE_REDIR_OUT)
		return (">");
	else if (type == NODE_APPEND)
		return (">>");
	else if (type == NODE_HEREDOC)
		return ("<<");
	else if (type == NODE_AND)
		return ("&&");
	else if (type == NODE_OR)
		return ("||");
	return ("unknown");
}

const char	*get_token_type_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("|");
	else if (type == REDIR_IN)
		return ("<");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == REDIR_APPEND)
		return (">>");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == AND)
		return ("&&");
	else if (type == OR)
		return ("||");
	return ("unknown");
}

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			count++;
		}
		tokens = tokens->next;
	}
	return (count);
}

int	is_command(char *word)
{
	int	i;

	i = 0;
	while (valid_commands[i] != NULL)
	{
		if (strcmp(word, valid_commands[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	classify_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			if (is_command(tokens->value))
				tokens->type = COMMAND; // C'est une commande
			else
				tokens->type = ARGUMENT; // C'est un argument
		}
		tokens = tokens->next;
	}
}