/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:48:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/24 11:41:26 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*parse_redir(t_token **tokens, t_ast *node)
{
	t_ast_type	type;
	t_ast		*new_node;
	t_ast		*last;
	t_ast		*cmd;

	if ((*tokens)->next && is_redirection((*tokens)->next, 1))
	{
		return (free_ast(node), NULL);
	}
	type = get_redir_type(*tokens);
	*tokens = (*tokens)->next;
	new_node = create_operator_node(type, NULL, NULL);
	new_node->file = ft_strdup((*tokens)->value);
	new_node->file_quoted = (*tokens)->is_quoted;
	*tokens = (*tokens)->next;
	if (!node)
		return (new_node);
	if (node && node->type == NODE_COMMAND)
	{
		new_node->left = node;
		return (new_node);
	}
	else
	{
		last = node;
		while (last->left && last->left->type != NODE_COMMAND)
			last = last->left;
		cmd = last->left;
		last->left = new_node;
		new_node->left = cmd;
		return (node);
	}
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


