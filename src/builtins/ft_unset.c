/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:37:25 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/13 15:35:13 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	rm_var_from_list(t_env **head_ptr, char *name)
{
	t_env	*current;
	t_env	*temp;

	if (!head_ptr || !*head_ptr || !name)
		return;
    if (ft_strcmp((*head_ptr)->name, name) == 0)
	{
		temp = *head_ptr;
		*head_ptr = (*head_ptr)->next;
		return (free(temp->name), free(temp->value), free(temp));
	}
	current = *head_ptr;
	while (current->next)
	{
		if (ft_strcmp(current->next->name, name) == 0)
		{
			temp = current->next;
			current->next = temp->next;
			free(temp->name);
			free(temp->value);
			free(temp);
			return;
        }
		current = current->next;
	}
}

int ft_unset(char **args, t_shell *shell)
{
	int	i;

	if (!args || !shell)
		return (EXIT_FAILURE);
	i = 1;
	while (args[i])
	{
		if (is_var(shell, args[i]))
        {
			rm_var_from_list(&shell->env, args[i]);
			rm_var_from_list(&shell->exp, args[i]);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
