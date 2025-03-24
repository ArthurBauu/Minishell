/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:00:43 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/22 12:46:20 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_env	*env_new(char *name, char *value, t_shell *shell)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		perror_exit("malloc", shell);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!env || !new)
		return ;
	if (*env == NULL)
		*env = new;
	else
	{
		last = *env;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	g_last_exit_code = EXIT_SUCCESS;
}

void	ft_sort_exp(t_env *exp)
{
	t_env	*current1;
	t_env	*current2;
	char	*temp;

	current1 = exp;
	if (!exp)
		return ;
	while (current1->next)
	{
		current2 = current1->next;
		while (current2)
		{
			if (ft_strcmp(current1->name, current2->name) > 0)
			{
				temp = current1->name;
				current1->name = current2->name;
				current2->name = temp;
				temp = current1->value;
				current1->value = current2->value;
				current2->value = temp;
			}
			current2 = current2->next;
		}
		current1 = current1->next;
	}
}

void	print_exp(t_env *exp)
{
	t_env	*current;

	current = exp;
	ft_sort_exp(exp);
	while (current)
	{
		if (current->value)
			ft_printf("export %s=\"%s\"\n", current->name, current->value);
		else
			ft_printf("export %s\n", current->name, current->value);
		current = current->next;
	}
}

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
