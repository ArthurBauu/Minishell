/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:59:06 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/18 16:48:37 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_env	*dup_env(char **envp, t_shell *shell)
{
	t_env	*copy;
	int		i;

	i = 0;
	copy = NULL;
	if (!envp || !envp[0])
		return (NULL);
	while (envp[i])
	{
		ft_env_add_back(&copy,
			ft_env_new(ft_strndup(envp[i], find_char(envp[i], '=')),
			ft_strdup(envp[i] + find_char(envp[i], '=') + 1), shell));
		i++;
	}
	return (copy);
}

bool	is_var(t_shell *shell, char *name)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		if (ft_strcmp(name, current->name) == 0)
			return (true);
		current = current->next;
	}
	return (false);
}

void	update_var(t_shell *shell, char *name, char *value)
{
	t_env	*current_env;
	t_env	*current_exp;

	current_env = shell->env;
	current_exp = shell->exp;
	if (value)
	{
		while (ft_strcmp(name, current_env->name) != 0)
			current_env = current_env->next;
		free(current_env->value);
		current_env->value = ft_strdup(value);
	}
	while (ft_strcmp(name, current_exp->name) != 0)
		current_exp = current_exp->next;
	free(current_exp->value);
	if (value)
		current_exp->value = ft_strdup(value);
	
}

char	*ft_getenv(t_shell *shell, char *name)
{
	t_env	*current;

	current = shell->env;
	if (!is_var(shell, name))
		return (NULL);
	while (ft_strcmp(current->name, name) != 0)
		current = current->next;
	return (current->value);
}

void	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}
