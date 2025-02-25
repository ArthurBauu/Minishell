/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:21:41 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/25 01:28:22 by arbaudou         ###   ########.fr       */
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
	while (*tokens && ((*tokens)->type == COMMAND
			|| (*tokens)->type == ARGUMENT))
	{
		args[i++] = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return (create_command_node(args));
}

t_ast	*parse_pipe(t_token **tokens, t_ast *left)
{
	t_ast	*right;

	if (!left && (*tokens)->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		return (NULL);
	}
	if (!(*tokens)->next || (*tokens)->next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '||'\n", 2);
		*tokens = (*tokens)->next;
		return (NULL);
	}
	*tokens = (*tokens)->next;
	right = parse_word(tokens, NULL);
	if (!right)
	{
		ft_putstr_fd("minishell: syntax error after '|'\n", 2);
		return (NULL);
	}
	return (create_operator_node(NODE_PIPE, left, right));
}

t_ast	*parse_logical_operator(t_token **tokens, t_ast *left)
{
	t_ast *right;
	t_ast_type type;

	if ((*tokens)->type == AND)
		type = NODE_AND;
	else if ((*tokens)->type == OR)
		type = NODE_OR;
	else
		return (NULL);
	*tokens = (*tokens)->next;
	if (!(*tokens) || ((*tokens)->type != COMMAND
			&& (*tokens)->type != ARGUMENT))
	{
		ft_putstr_fd("minishell: syntax error after logical operator\n", 2);
		return (NULL);
	}
	right = parse_word(tokens, NULL);
	if (!right)
	{
		ft_putstr_fd("minishell: syntax error after logical operator\n", 2);
		return (NULL);
	}
	return (create_operator_node(type, left, right));
}