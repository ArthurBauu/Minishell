/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:59:06 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 18:43:14 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**dup_env(char **env)
{
	char	**copy;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (env[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

bool	is_var(t_shell *shell, char *name)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	temp = ft_strjoin(name, "=");
	len = ft_strlen(temp);
	while (shell->envp[i])
	{
		if (ft_strncmp(temp, shell->envp[i], len) == 0)
		{
			free(temp);
			return (true);
		}
		i++;
	}
	free(temp);
	return (false);
}

void	update_var(t_shell *shell, char *name, char *value)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strjoin(name, "=");
	while (ft_strncmp(temp, shell->envp[i], ft_strlen(temp)) != 0)
		i++;
	free(shell->envp[i]);
	shell->envp[i] = ft_strjoin(temp, value);
	free(temp);
}

char	*ft_getenv(t_shell *shell, char *name)
{
	int		i;
	char	*value;
	char	*temp;

	i = 0;
	if (!is_var(shell, name))
		return (NULL);
	temp = ft_strjoin(name, "=");
	while (ft_strncmp(shell->envp[i], temp, ft_strlen(temp)) != 0)
		i++;
	value = ft_strdup(shell->envp[i] + ft_strlen(temp));
	free(temp);
	return (value);
}
