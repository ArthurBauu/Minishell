/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:11:08 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/25 01:39:10 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			count++;
		}
		tokens = tokens->next;
	}
	return (count);
}

int	is_command(char *word)
{
	int	i;

	i = 0;
	while (valid_commands[i] != NULL)
	{
		if (strcmp(word, valid_commands[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	classify_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			if (is_command(tokens->value))
				tokens->type = COMMAND;
			else
				tokens->type = ARGUMENT;
		}
		tokens = tokens->next;
	}
}

t_ast	*init_args(t_ast *cmd_node, char *arg)
{
	cmd_node->args = malloc(sizeof(char *) * 2);
	if (!cmd_node->args)
		return (NULL);
	cmd_node->args[0] = ft_strdup(arg);
	cmd_node->args[1] = NULL;
	return (cmd_node);
}

t_ast	*add_argument_to_command(t_ast *cmd_node, char *arg)
{
	char	**new_args;
	int		i;

	i = 0;
	if (!cmd_node || !arg)
		return (NULL);
	if (!cmd_node->args)
		return (init_args(cmd_node, arg));
	while (cmd_node->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (cmd_node->args[i])
	{
		new_args[i] = cmd_node->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free(cmd_node->args);
	cmd_node->args = new_args;
	return (cmd_node);
}
