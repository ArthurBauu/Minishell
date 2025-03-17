/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:48:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/14 19:21:13 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*parse_redir(t_token **tokens, t_ast *node)
{
	t_ast_type	type;
	t_ast		*new_node;

	while (*tokens && is_redirection((*tokens), 0))
	{
		if ((*tokens)->next && is_redirection((*tokens)->next, 1))
			return (free_ast(node), NULL);
		type = get_redir_type(*tokens);
		*tokens = (*tokens)->next;
		new_node = create_operator_node(type, NULL, NULL);
		new_node->file = ft_strdup((*tokens)->value);
		if (node)
			new_node->left = node;
		node = new_node;
		*tokens = (*tokens)->next;
	}
	return (node);
}

t_ast	*parse_word(t_token **tokens, t_ast *left)
{
	t_ast	*node;

	if (!tokens || !(*tokens))
		return (NULL);
	if (left)
		node = left;
	else if ((*tokens)->type == WORD)
		node = parse_command(tokens);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (free_ast(left), NULL);
	}
	if (*tokens && is_redirection(*tokens, 0))
		node = parse_redir(tokens, node);
	return (node);
}

t_ast	*parse(t_token **tokens)
{
	t_ast	*left;
	t_ast	*cmd_node;
	t_ast	*temp;

	left = NULL;
	if (check_error(tokens) == -1)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->type == WORD)
		{
			cmd_node = parse_command(tokens);
			if (*tokens && is_redirection(*tokens, 0))
				cmd_node = parse_redir(tokens, cmd_node);
			if (!left)
				left = cmd_node;
			else
			{
				temp = create_operator_node(NODE_PIPE, left, cmd_node);
				left = temp;
			}
		}
		else if (is_redirection(*tokens, 0))
			left = parse_redir(tokens, left);
		else if ((*tokens)->type == PIPE)
			left = parse_pipe(tokens, left);
		else if ((*tokens)->type == AND || (*tokens)->type == OR)
			left = parse_logical_operator(tokens, left);
		else
			return (print_errors(7), free_ast(left), NULL);
		if (!left)
			return (NULL);
	}
	return (left);
}
