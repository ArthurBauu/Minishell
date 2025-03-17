/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:03 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/14 18:31:37 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* A SUPRIMER AVANT DE RENDRE */

void	print_ast(t_ast *node, int level)
{
	if (!node)
		return;
	
	// Indentation pour voir la hiérarchie
	for (int i = 0; i < level; i++)
		printf("  ");

	// Affichage selon le type de nœud
	if (node->type == NODE_COMMAND)
	{
		printf("Commande: ");
		if (node->value)
		{
			for (int i = 0; node->value[i]; i++)
				printf("%s ", node->value[i]);
		}
		else
			printf("(NULL)");
		printf("\n");
	}
	else if (node->type == NODE_PIPE)
	{
		printf("PIPE\n");
	}
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_IN
		|| node->type == NODE_APPEND || node->type == NODE_HEREDOC)
	{
		// Affichage du type de redirection
		if (node->type == NODE_REDIR_OUT)
			printf("REDIRECTION_OUT -> ");
		else if (node->type == NODE_REDIR_IN)
			printf("REDIRECTION_IN -> ");
		else if (node->type == NODE_APPEND)
			printf("REDIRECTION_APPEND -> ");
		else if (node->type == NODE_HEREDOC)
			printf("HEREDOC -> ");

		// Affiche le fichier cible de la redirection
		if (node->file)
			printf("%s\n", node->file);
		else
			printf("(NULL)\n");
	}
	else if (node->type == NODE_AND)
	{
		printf("LOGICAL AND (&&)\n");
	}
	else if (node->type == NODE_OR)
	{
		printf("LOGICAL OR (||)\n");
	}

	// Affichage des nœuds enfants
	if (node->left)
	{
		printf("%*s└── ", level * 2, ""); // Affiche une branche visuelle
		print_ast(node->left, level + 1);
	}
	if (node->right)
	{
		printf("%*s└── ", level * 2, "");
		print_ast(node->right, level + 1);
	}
}

