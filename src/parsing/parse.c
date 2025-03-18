/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:48:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/18 17:53:48 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*parse_redir(t_token **tokens, t_ast *node)
{
    t_ast_type	type;
    t_ast		*new_node;
    t_ast       *root = NULL;
    t_ast       *current;

    // Stocker toutes les redirections dans une liste temporaire
    t_ast **redir_list = NULL;
    int count = 0;
    int i;

    // Compter d'abord le nombre de redirections
    t_token *temp = *tokens;
    while (temp && is_redirection(temp, 0))
    {
        count++;
        temp = temp->next ? temp->next->next : NULL;
    }

    // Allouer la liste
    redir_list = malloc(sizeof(t_ast *) * count);
    if (!redir_list)
        return (free_ast(node), NULL);
    
    // Remplir la liste dans l'ordre normal
    i = 0;
    while (*tokens && is_redirection((*tokens), 0) && i < count)
    {
        if ((*tokens)->next && is_redirection((*tokens)->next, 1))
        {
            free(redir_list);
            return (free_ast(node), NULL);
        }
        
        type = get_redir_type(*tokens);
        *tokens = (*tokens)->next;
        new_node = create_operator_node(type, NULL, NULL);
        new_node->file = ft_strdup((*tokens)->value);
        redir_list[i++] = new_node;
        *tokens = (*tokens)->next;
    }

    // Reconstruire l'arbre dans l'ordre inverse
    if (count > 0)
    {
        root = redir_list[0];
        current = root;
        for (i = 1; i < count; i++)
        {
            current->left = redir_list[i];
            current = current->left;
        }
        // Attacher le nœud de commande à la dernière redirection
        current->left = node;
        free(redir_list);
        return root;
    }

    free(redir_list);
    return node;
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
        else if ((*tokens)->type == PIPE)
        {
            if (!left || !(*tokens)->next)
                return (print_errors(4), free_ast(left), NULL);
            *tokens = (*tokens)->next;
            if ((*tokens)->type == WORD)
            {
                cmd_node = parse_command(tokens);
                if (*tokens && is_redirection(*tokens, 0))
                    cmd_node = parse_redir(tokens, cmd_node);
                    
                temp = create_operator_node(NODE_PIPE, left, cmd_node);
                left = temp;
            }
            else if (is_redirection(*tokens, 0))
            {
                cmd_node = parse_redir(tokens, NULL);
                temp = create_operator_node(NODE_PIPE, left, cmd_node);
                left = temp;
            }
            else
                return (print_errors(5), free_ast(left), NULL);
        }
        else if (is_redirection(*tokens, 0))
        {
            if (!left)
                return (print_errors(6), NULL);
            left = parse_redir(tokens, left);
        }
        else if ((*tokens)->type == AND || (*tokens)->type == OR)
            left = parse_logical_operator(tokens, left);
        else
            return (print_errors(7), free_ast(left), NULL);
            
        if (!left)
            return (NULL);
    }
    return (left);
}
