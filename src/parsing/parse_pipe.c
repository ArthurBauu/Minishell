/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:49:40 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/12 00:53:42 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_pipe_syntax(t_token **tokens, t_ast *left)
{
	if (!(*tokens)->next || ((*tokens)->next->type == PIPE
			|| (*tokens)->next->type == OR || (*tokens)->next->type == AND))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		return (free_ast(left), 0);
	}
	return (1);
}

t_ast	*pipe_redir(t_token **tokens, t_ast *left)
{
	t_ast	*redir;

	redir = NULL;
	if (*tokens && is_redirection(*tokens, 0))
	{
		redir = parse_redir(tokens, redir);
		if (!redir)
			return (free_ast(left), NULL);
		return (create_operator_node(NODE_PIPE, left, redir));
	}
	return (NULL);
}

t_ast	*pipe_word(t_token **tokens, t_ast *redir)
{
	t_ast	*right;

	right = NULL;
	if (*tokens && (*tokens)->type == WORD)
	{
		right = parse_command(tokens);
		if (redir)
		{
			if (!redir->left)
				redir->left = right;
			right = redir;
		}
	}
	return (right);
}
t_ast	*parse_pipe(t_token **tokens, t_ast *left)
{
	t_ast	*right;
	t_ast	*redir;

	right = NULL;
	redir = NULL;
	if (!check_pipe_syntax(tokens, left))
		return (NULL);
	*tokens = (*tokens)->next;
	redir = pipe_redir(tokens, left);
	if (redir)
		return (redir);
	right = pipe_word(tokens, redir);
	if (!right)
	{
		ft_putstr_fd("minishell: syntax error after '|'\n", 2);
		return (free_ast(left), free_ast(redir), NULL);
	}
	return (create_operator_node(NODE_PIPE, left, right));
}
