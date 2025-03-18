/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:03 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/07 20:42:36 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* A SUPRIMER AVANT DE RENDRE */

void	print_ast(t_ast *node, int level)
{
	if (!node)
		return ;
	
	// Print indentation for the current level
	for (int i = 0; i < level; i++)
		printf("  ");
	
	if (node->type == NODE_COMMAND)
	{
		printf("Commande: ");
		for (int i = 0; node->value[i]; i++)
			printf("%s ", node->value[i]);
		printf("\n");
	}
	else if (node->type == NODE_PIPE)
	{
		printf("PIPE\n");
	}
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_IN
		|| node->type == NODE_APPEND || node->type == NODE_HEREDOC)
	{
		if (node->type == NODE_REDIR_OUT)
			printf("REDIRECTION_OUT -> ");
		else if (node->type == NODE_REDIR_IN)
			printf("REDIRECTION_IN -> ");
		else if (node->type == NODE_APPEND)
			printf("REDIRECTION_APPEND -> ");
		else if (node->type == NODE_HEREDOC)
			printf("HEREDOC -> ");

		// Affiche le fichier de redirection
		if (node->file)
			printf("%s\n", node->file);
		else
			printf("No file\n");
	}
	else if (node->type == NODE_AND)
	{
		printf("LOGICAL AND (&&)\n");
	}
	else if (node->type == NODE_OR)
	{
		printf("LOGICAL OR (||)\n");
	}

	// Recursively print left and right child nodes
	if (node->left)
		print_ast(node->left, level + 1);
	if (node->right)
		print_ast(node->right, level + 1);
}
