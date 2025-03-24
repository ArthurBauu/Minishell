/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:11:08 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/23 22:38:28 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && !is_operator(tokens->value))
	{
		if (tokens->type == WORD)
		{
			count++;
		}
		tokens = tokens->next;
	}
	return (count);
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
    if (!cmd_node->value)
        return (init_args(cmd_node, arg));
    while (cmd_node->value[i])
        i++;
    new_args = malloc(sizeof(char *) * (i + 2));
    if (!new_args)
        return (free(new_args), NULL);
    i = 0;
    while (cmd_node->value[i])
    {
        new_args[i] = cmd_node->value[i];
        i++;
    }
    new_args[i] = ft_strdup(arg);
    if (!new_args[i])
    {
        free(new_args);
        return (NULL);
    }
    new_args[i + 1] = NULL;
    free(cmd_node->value);
    cmd_node->value = new_args;
    return (cmd_node);
}
