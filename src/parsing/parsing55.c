/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 03:19:30 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/07 03:29:24 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>


// Structure pour stocker une adresse de nœud AST
typedef struct s_ast_node_address
{
    t_ast *node;
    struct s_ast_node_address *next;
} t_ast_node_address;

// Fonction pour ajouter une adresse de nœud à la liste
void add_node_address(t_ast_node_address **list, t_ast *node)
{
    t_ast_node_address *new_node = malloc(sizeof(t_ast_node_address));
    if (!new_node)
    {
        return;  // Erreur d'allocation
    }
    new_node->node = node;
    new_node->next = *list;
    *list = new_node;
}

// Fonction pour afficher les valeurs des nœuds à partir de leurs adresses
void print_nodes_by_address(t_ast_node_address *list)
{
    while (list)
    {
        if (list->node)
        {
            // Affiche ici les informations que tu veux, par exemple :
            printf("Node at address: %p\n", (void*)list->node);
            
            // Afficher les détails selon le type du nœud
            if (list->node->type == NODE_COMMAND)
            {
                printf("  Command: ");
                if (list->node->value)
                    printf("%s\n", *list->node->value);
                else
                    printf("No command value\n");

                if (list->node->args)
                {
                    printf("  Arguments: ");
                    for (int i = 0; list->node->args[i]; i++)
                    {
                        printf("%s ", list->node->args[i]);
                    }
                    printf("\n");
                }
            }
            
            if (list->node->file)
                printf("  File: %s\n", list->node->file);
            else
                printf("  No file associated\n");
        }
        list = list->next;
    }
}

// Fonction pour libérer la liste d'adresses des nœuds
void free_node_address_list(t_ast_node_address *list)
{
    t_ast_node_address *temp;
    while (list)
    {
        temp = list;
        list = list->next;
        free(temp);
    }
}

// Fonction pour vérifier les fuites dans l'AST et enregistrer les adresses des nœuds
void check_ast_leaks_and_store_addresses(t_ast *ast, t_ast_node_address **address_list)
{
    if (ast == NULL)
    {
        return;
    }

    // Ajouter l'adresse du nœud actuel à la liste
    add_node_address(address_list, ast);

    // Vérification récursive des enfants (si ils existent)
    if (ast->left)
    {
        check_ast_leaks_and_store_addresses(ast->left, address_list);
    }

    if (ast->right)
    {
        check_ast_leaks_and_store_addresses(ast->right, address_list);
    }

    // Vérification de chaque champ pour s'assurer qu'il est correctement libéré
    if (ast->file)
    {
        printf("AST node has a file that has not been freed: %s\n", ast->file);
    }

    // Si les arguments existent, les afficher
    if (ast->args)
    {
        for (int i = 0; ast->args[i] != NULL; i++)
        {
            printf("AST node has an argument: %s\n", ast->args[i]);
        }
    }
}

// Fonction principale de parsing
int parsing(char *input)
{    
    t_token *tokens;
    t_token *start;
    t_ast *ast;
    t_ast_node_address *address_list = NULL;

    printf("Testing: '%s'\n", input);
    start = tokenize(input);
    tokens = start;
    print_tokens(tokens);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");

        // Vérifier les fuites dans l'AST et enregistrer les adresses des nœuds
        check_ast_leaks_and_store_addresses(ast, &address_list);

        // Afficher les nœuds à partir de leurs adresses enregistrées
        print_nodes_by_address(address_list);
    } else {
        printf("Error parsing command.\n");
    }
    printf("\n");

    // Libérer les ressources
    free_all(ast, start);
    free_node_address_list(address_list);  // Libérer la liste d'adresses
    return (1);
}

