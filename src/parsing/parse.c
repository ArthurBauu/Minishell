/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:48:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/06 04:09:11 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static char	**allocate_filename(t_token *token)
// {
// 	char	**filename;

// 	filename = malloc(sizeof(char *) * 2);
// 	if (!filename)
// 		return (NULL);
// 	filename[0] = ft_strdup(token->value);
// 	if (!filename[0])
// 	{
// 		free(filename);
// 		return (NULL);
// 	}
// 	filename[1] = NULL;
// 	return (filename);
// }

/* FONCTION TROP LONGUE IL FAUT QUE JE LA RACOURCISSE */

static t_ast	*parse_redir(t_token **tokens, t_ast *node)
{
	t_ast_type	type;

	while (*tokens && is_redirection((*tokens), 0))
	{
		if ((*tokens)->next && is_redirection((*tokens)->next, 1))
			return (free_ast(node), NULL); /* utiliser return pour les mains qui test plein de de chose */
		 // exit(1); /* Sinon utiliser exit sera plus simple je pense (permet d'eviter les doubles msg d'erreur)*/
		type = get_redir_type(*tokens);
		*tokens = (*tokens)->next;
		if (!(*tokens) || ((*tokens)->type != ARGUMENT))
			return (NULL);
		if (!node)
			node = create_operator_node(type, NULL, NULL);
		else
			node = create_operator_node(type, node, NULL);
		node->file = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
		if ((*tokens) && ((*tokens)->type == COMMAND || (*tokens)->type == ARGUMENT))
			node->left = parse_word(tokens, node);
	}
	return (node);
}

t_ast	*parse_word(t_token **tokens, t_ast *left)
{
	t_ast	*node;

	if (!tokens || !(*tokens))
		return (NULL);
	node = left;
	if ((*tokens)->type == COMMAND)
		node = parse_command(tokens);
	else if ((*tokens)->type == ARGUMENT)
	{
		if (node)
			node = add_argument_to_command(left, (*tokens)->value);
		else
			node = create_command_node(&(*tokens)->value);
		*tokens = (*tokens)->next;
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (free_ast(left), NULL);
	}
	node = parse_redir(tokens, node);
	return (node);
}

t_ast	*parse(t_token **tokens)
{
	t_ast	*left;

	left = NULL;
	if ((*tokens)->type == 3 || (*tokens)->type == 8 || (*tokens)->type == 9)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->type == REDIR_OUT || (*tokens)->type == REDIR_IN
			|| (*tokens)->type == REDIR_APPEND || (*tokens)->type == HEREDOC)
			left = parse_redir(tokens, left);
		else if ((*tokens)->type == COMMAND || (*tokens)->type == ARGUMENT)
			left = parse_word(tokens, left);
		else if ((*tokens)->type == PIPE)
			left = parse_pipe(tokens, left);
		else if ((*tokens)->type == AND || (*tokens)->type == OR)
			left = parse_logical_operator(tokens, left);
		else
		{
			ft_putstr_fd("minishell: syntax error: invalid token\n", 2);
			return (free_ast(left), NULL);
		}
		if (!left)
			return (NULL);
	}
	return (left);
}
