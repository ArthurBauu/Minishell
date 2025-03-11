/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:48:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/11 14:56:52 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


t_ast	*parse_redir(t_token **tokens, t_ast *node)
{
	t_ast_type	type;

	while (*tokens && is_redirection((*tokens), 0))
	{
		if ((*tokens)->next && is_redirection((*tokens)->next, 1))
			return (free_ast(node), NULL);
		type = get_redir_type(*tokens);
		*tokens = (*tokens)->next;
		if (!(*tokens) || ((*tokens)->type != WORD))
			return (NULL);
		if (!node)
			node = create_operator_node(type, NULL, NULL);
		else
			node = create_operator_node(type, node, NULL);
		node->file = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
		if ((*tokens) && ((*tokens)->type == WORD))
			node->left = parse_word(tokens, node);
	}
	return (node);
}

t_ast	*parse_pipe(t_token **tokens, t_ast *left)
{
	t_ast	*right;
	t_ast	*redir;

	right = NULL;
	redir = NULL;
	if (!(*tokens)->next || ((*tokens)->next->type == PIPE
			|| (*tokens)->next->type == OR || (*tokens)->next->type == AND))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		return (free_ast(left), NULL);
	}
	*tokens = (*tokens)->next;
	if (*tokens && is_redirection((*tokens), 0))
	{
		printf("test123\n");
		redir = parse_redir(tokens, redir);
		if (!redir)
			return (free_ast(left), free_ast(right), NULL);
		return (create_operator_node(NODE_PIPE, left, redir));
	}
	if (*tokens && (*tokens)->type == WORD)
	{
		printf("test123\n");
		right = parse_command(tokens);
		if (redir)
		{
			if (!redir->left)
				redir->left = right;
			right = redir;
		}
	}
	if (!right)
	{
		ft_putstr_fd("minishell: syntax error after '|'\n", 2);
		return (free_ast(left), free_ast(redir), NULL);
	}
	return (create_operator_node(NODE_PIPE, left, right));
}

t_ast	*parse_word(t_token **tokens, t_ast *left)
{
	t_ast	*node;

	if (!tokens || !(*tokens))
		return (NULL);
	node = left;
	if ((*tokens)->type == WORD)
		node = parse_command(tokens);
	else if ((*tokens)->type == WORD)
	{
		if (node)
			node = add_argument_to_command(left, (*tokens)->value);
		else
			node = create_command_node(&(*tokens)->value);
		*tokens = (*tokens)->next;
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (free_ast(left), NULL);
	}
	node = parse_redir(tokens, node);
	return (node);
}

t_ast	*parse(t_token **tokens)
{
	t_ast	*left;

	left = NULL;
	
	if (check_error(tokens) == -1)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->type == REDIR_OUT || (*tokens)->type == REDIR_IN
			|| (*tokens)->type == REDIR_APPEND || (*tokens)->type == HEREDOC)
			left = parse_redir(tokens, left);
		else if ((*tokens)->type == WORD)
			left = parse_word(tokens, left);
		else if ((*tokens)->type == PIPE)
			left = parse_pipe(tokens, left);
		else if ((*tokens)->type == AND || (*tokens)->type == OR)
			left = parse_logical_operator(tokens, left);
		else
		{
			ft_putstr_fd("minishell: syntax error: invalid token\n", 2);
			return (free_ast(left), NULL);
		}
		if (!left)
			return (NULL);
	}
	return (left);
}
