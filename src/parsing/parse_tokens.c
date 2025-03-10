/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:21:41 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/09 23:30:55 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*parse_command(t_token **tokens)
{
	char	**args;
	int		i;

	i = 0;
	if (!tokens || !(*tokens))
		return (NULL);
	args = malloc(sizeof(char *) * (count_args(*tokens) + 1));
	if (!args)
		return (NULL);
	while (*tokens && ((*tokens)->type == WORD))
	{
		args[i++] = ft_strdup((*tokens)->value);
		if (!args)
			ft_free(args, i);
		*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return (create_command_node(args));
}



t_ast	*parse_logical_operator(t_token **tokens, t_ast *left)
{
	t_ast		*right;
	t_ast_type	type;

	if ((*tokens)->type == AND)
		type = NODE_AND;
	else if ((*tokens)->type == OR)
		type = NODE_OR;
	else
		return (NULL);
	*tokens = (*tokens)->next;
	if (!(*tokens) || (*tokens)->type != WORD)
	{
		ft_putstr_fd("minishell: missing command after logical operator\n", 2);
		return (free_ast(left), NULL);
	}
	right = parse_word(tokens, NULL);
	if (!right)
	{
		ft_putstr_fd("minishell: invalid AST node\n", 2);
		return (free_ast(left), NULL);
	}
	return (create_operator_node(type, left, right));
}
