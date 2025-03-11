/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:37:25 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/10 16:05:41 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	**rm_var_from_env(t_shell *shell, char *var, int n)
{
	char	**new_env;
	char	*temp;
	int		count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	j = 0;
	while (shell->envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count));
	temp = ft_strjoin(var, "=");
	while (shell->envp[i])
	{
		if (ft_strncmp(temp, shell->envp[i], n))
			new_env[j++] = ft_strdup(shell->envp[i]);
		i++;
	}
	new_env[i] = NULL;
	free(temp);
	free(shell->envp);
	return (new_env);
}

int	ft_unset(char **args, t_shell *shell)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if (is_var(shell, args[i]))
			shell->envp = rm_var_from_env(shell, args[i],
					ft_strlen(args[i]) + 1);
		i++;
	}
	return (EXIT_SUCCESS);
}
