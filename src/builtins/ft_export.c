/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:01:27 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/18 16:16:29 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* args = tout ce qui suit la commande export et n est pas une redir */
/* shell = pointeur sur struct qui contient une copie de l'env */

static void	add_var_to_env(t_shell *shell, char *name, char *value)
{
	if (is_var(shell, name))
		return (update_var(shell, name, value));
	if (value)
		ft_env_add_back(&shell->env, ft_env_new(name, value, shell));
	ft_env_add_back(&shell->exp, ft_env_new(name, value, shell));
	ft_sort_exp(shell->exp);
}

/* rule for var names : all char must be alphanum or '_' 
	and 1st char can't be a digit */

static int	check_var_name(char *name, char *arg)
{
	int	i;

	i = 1;
	if (!name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		ft_printf_error(2, "minishell: export: '%s': not a valid identifier\n",
			arg);
		return (0);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_printf_error(2, "minishell: export: '%s': not a valid identifier\n",
				arg);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(char **args, t_shell *shell)
{
	char	*name;
	char	*value;
	int		i;
	int		i_equal;

	i = 1;
	if (shell->exp)
		ft_sort_exp(shell->exp);
	if (!args[1])
		print_exp(shell->exp);
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			i_equal = find_char(args[i], '=');
			name = ft_strndup(args[i], i_equal);
			value = ft_strdup(args[i] + i_equal + 1);
			if (check_var_name(name, args[i]))
				add_var_to_env(shell, name, value);
		}
		else if (check_var_name(args[i], args[i]))
			ft_env_add_back(&shell->exp, ft_env_new(args[i], NULL, shell));
		i++;
	}
	return (EXIT_SUCCESS);
}
