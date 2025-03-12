/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:21:41 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/12 01:07:45 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char **get_arguments(t_token **tokens)
{
    char **args;
    int i = 0;

    args = malloc(sizeof(char *) * (count_args(*tokens) + 1));
    if (!args)
        return NULL;
    while (*tokens && ((*tokens)->type == WORD))
    {
        args[i++] = ft_strdup((*tokens)->value);
        if (!args[i-1])
        {
            ft_free(args, i);
            return NULL;
        }
        *tokens = (*tokens)->next;
    }
    args[i] = NULL;
    return args;
}

t_ast *word_redir(t_token **tokens, t_ast *cmd_node)
{
    t_ast *new_redir;

    while (*tokens && is_redirection(*tokens, 0))
    {
        new_redir = parse_redir(tokens, NULL);
        if (!new_redir)
            return (free_ast(cmd_node), NULL);
        if (!new_redir->left)
            new_redir->left = cmd_node;
        else
            free_ast(cmd_node);
        cmd_node = new_redir;
    }
    return cmd_node;
}

t_ast *parse_command(t_token **tokens)
{
    char **args;
    t_ast *cmd_node = NULL;

    if (!tokens || !(*tokens))
        return NULL;
    args = get_arguments(tokens);
    if (!args)
        return NULL;
    cmd_node = create_command_node(args);
    if (!cmd_node)
    {
        ft_free(args, count_args(*tokens));
        return NULL;
    }
    cmd_node = word_redir(tokens, cmd_node);
    return cmd_node;
}


t_ast	*parse_logical_operator(t_token **tokens, t_ast *left)
{
	t_ast		*right;
	t_ast_type	type;

	right = NULL;
	if ((*tokens)->type == AND)
		type = NODE_AND;
	else if ((*tokens)->type == OR)
		type = NODE_OR;
	else
		return (NULL);
	*tokens = (*tokens)->next;
	if (!(*tokens) || ((*tokens)->type != WORD && is_redirection((*tokens),
				0) != 1))
		return (print_errors(1), free_ast(left), NULL);
	if (is_redirection((*tokens), 0))
		right = parse_redir(tokens, left);
	else if ((*tokens)->type == WORD)
		right = parse_word(tokens, NULL);
	if (!right)
		return (print_errors(2), free_ast(left), NULL);
	return (create_operator_node(type, left, right));
}
