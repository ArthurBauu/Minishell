/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:55:03 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/21 01:18:39 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* A SUPRIMER AVANT DE RENDRE */


// void print_ast(t_ast *node)
// {
//     static int level = 0;  // Niveau d'indentation

//     if (!node)
//         return;

//     // Indentation pour les niveaux d'AST
//     for (int i = 0; i < level; i++)
//         printf("  ");

//     // Affichage en fonction du type de nœud
//     if (node->type == NODE_COMMAND)
//     {
//         printf("Commande: ");
//         if (node->value) {
//             for (int i = 0; node->value[i]; i++)
//                 printf("%s ", node->value[i]);
//         }
//         printf("\n");
//     }
//     else if (node->type == NODE_PIPE)
//     {
//         printf("PIPE\n");
//     }
//     else if (node->type == NODE_REDIR_OUT)
//     {
//         printf("REDIRECTION_OUT -> ");
//         print_ast(node->left);  // Affichage de la commande avant redirection
//         if (node->value && node->value[0])
//             printf("Vers fichier: %s\n", node->value[0]);
//     }
//     else if (node->type == NODE_REDIR_IN)
//     {
//         printf("REDIRECTION_IN -> ");
//         print_ast(node->left);  // Affichage de la commande avant redirection
//         if (node->value && node->value[0])
//             printf("Depuis fichier: %s\n", node->value[0]);
//     }
//     else if (node->type == NODE_APPEND)
//     {
//         printf("REDIRECTION_APPEND -> ");
//         print_ast(node->left);  // Affichage de la commande avant redirection
//         if (node->value && node->value[0])
//             printf("Vers fichier (append): %s\n", node->value[0]);
//     }
//     else if (node->type == NODE_HEREDOC)
//     {
//         printf("HEREDOC -> ");
//         print_ast(node->left);  // Affichage de la commande avant heredoc
//         if (node->value && node->value[0])
//             printf("Depuis fichier (heredoc): %s\n", node->value[0]);
//     }
//     else if (node->type == NODE_AND)
//     {
//         printf("LOGICAL AND (&&)\n");
//     }
//     else if (node->type == NODE_OR)
//     {
//         printf("LOGICAL OR (||)\n");
//     }

//     level++;
//     // Appel récursif pour les nœuds gauche et droit (si présents)
//     print_ast(node->left);
//     print_ast(node->right);
//     level--;
// }


void print_ast(t_ast *node, int level) {
    if (!node)
        return;

    // Print indentation for the current level
    for (int i = 0; i < level; i++)
        printf("  ");

    if (node->type == NODE_COMMAND) {
        printf("Commande: ");
        for (int i = 0; node->value[i]; i++)
            printf("%s ", node->value[i]);
        printf("\n");
    } 
    else if (node->type == NODE_PIPE) {
        printf("PIPE\n");
    } 
    else if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_IN || 
             node->type == NODE_APPEND || node->type == NODE_HEREDOC) {
        if (node->type == NODE_REDIR_OUT)
            printf("REDIRECTION_OUT -> ");
        else if (node->type == NODE_REDIR_IN)
            printf("REDIRECTION_IN -> ");
        else if (node->type == NODE_APPEND)
            printf("REDIRECTION_APPEND -> ");
        else if (node->type == NODE_HEREDOC)
            printf("HEREDOC -> ");

        if (node->right && node->right->value)
            printf("%s\n", node->right->value[0]);
        else
            printf("No file\n");
    } 
    else if (node->type == NODE_AND) {
        printf("LOGICAL AND (&&)\n");
    } 
    else if (node->type == NODE_OR) {
        printf("LOGICAL OR (||)\n");
    }

    // Recursively print left and right child nodes
    if (node->left)
        print_ast(node->left, level + 1);
    if (node->right)
        print_ast(node->right, level + 1);
}
