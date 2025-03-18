/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:48:54 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/18 18:09:29 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*create_command_node(char **args)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->file = NULL;
	node->value_quoted = NULL;
	node->value = args;
	node->args = NULL;
	return (node);
}

t_ast	*create_operator_node(t_ast_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->value = NULL;
	node->value_quoted = NULL;
	node->file = NULL;
	node->args = NULL;
	return (node);
}

t_ast	*init_ast(t_ast *node)
{
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = 0;
	node->value = NULL;
	node->value_quoted = NULL;
	node->file = NULL;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
