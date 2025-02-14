/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:03 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/14 14:56:50 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* A SUPRIMER AVANT DE RENDRE */

void	print_ast(t_ast *node, int level)
{
	if (!node)
		return ;
	for (int i = 0; i < level; i++)
		printf("  "); // Indentation
	if (node->type == NODE_COMMAND)
	{
		printf("Commande: ");
		for (int i = 0; node->args[i]; i++)
			printf("%s ", node->args[i]);
		printf("\n");
	}
	else if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_REDIR_OUT)
		printf("REDIRECTION_OUT\n");
	else if (node->type == NODE_REDIR_IN)
		printf("REDIRECTION_IN\n");
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}
