/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:59:06 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/21 14:20:56 by md-harco         ###   ########.fr       */
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
		env_add_back(&copy,
			env_new(ft_strndup(envp[i], find_char(envp[i], '=')),
				ft_strdup(envp[i] + find_char(envp[i], '=') + 1), shell));
		i++;
	}
	return (copy);
}

bool	is_var(t_env *env, char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(name, current->name) == 0)
			return (true);
		current = current->next;
	}
	return (false);
}

void	update_var(t_env *env, char *name, char *value)
{
	t_env	*current_env;

	current_env = env;
	while (ft_strcmp(name, current_env->name) != 0)
		current_env = current_env->next;
	free(current_env->value);
	current_env->value = ft_strdup(value);
}

char	*ft_getenv(t_shell *shell, char *name)
{
	t_env	*current;

	current = shell->env;
	if (!is_var(shell->env, name))
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
