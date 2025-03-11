/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:01:27 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 20:10:37 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* args = tout ce qui suit la commande export et n est pas une redir */
/* shell = pointeur sur struct qui contient une copie de l'env */

static void	add_var_to_env(t_shell *shell, char *name, char *value)
{
	char	**new_env;
	char	*temp;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (is_var(shell, name))
		return (update_var(shell, name, value));
	while (shell->envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	while (i < count)
	{
		new_env[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	temp = ft_strjoin(name, "=");
	new_env[i] = ft_strjoin(temp, value);
	new_env[i + 1] = NULL;
	free_strtab(shell->envp);
	shell->envp = new_env;
	return (free(temp), free(name), free(value));
}

static int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

/* rule for var names : all char must be alphanum or '_' 
	and 1st char can't be a digit */

static int	check_var_name(char *name, char *value, char *arg)
{
	int	i;

	i = 1;
	if (!name || !value)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

// A FINIR 
/* a chaque export il faut updater le tableau shell->export, a chaque unset aussi */
/* export + pas d'arg = display shell->export par ordre ALPHABETIQUE */
/* si on export + pas d'egal ca cree un historique meme si on ajout pas a env */

int	ft_export(char **args, t_shell *shell)
{
	char	*name;
	char	*value;
	int		i;
	int		i_equal;

	i = 1;
/* 	if (!args[1])
	{
		while (shell->export[j])
	} */
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			i_equal = find_char(args[i], '=');
			name = ft_strndup(args[i], i_equal);
			value = ft_strdup(args[i] + i_equal + 1);
			if (check_var_name(name, value, args[i]))
				add_var_to_env(shell, name, value);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
