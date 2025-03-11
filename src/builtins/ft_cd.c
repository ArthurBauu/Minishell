/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:59:49 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 18:45:13 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*find_home(t_shell *shell)
{
	char	*home;

	home = ft_getenv(shell, "HOME");
	if (!home)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	return (home);
}

static char	*find_previous(t_shell *shell)
{
	char	*previous;

	previous = ft_getenv(shell, "OLDPWD");
	if (!previous)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	return (previous);
}

int	ft_cd(char **args, t_shell *shell)
{
	char	cwd[4096];
	char	*path;

	path = NULL;
	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2),
			EXIT_FAILURE);
	if (!args[1])
		path = find_home(shell);
	else if (ft_strcmp(args[1], "-") == 0)
		path = find_previous(shell);
	else
		path = ft_strdup(args[1]);
	if (path && chdir(path) == -1)
		return (free(path), perror("minishell: cd"), EXIT_FAILURE);
	update_var(shell, "OLDPWD", ft_getenv(shell, "PWD"));
	update_var(shell, "PWD", getcwd(cwd, sizeof(cwd)));
	if (path)
		free(path);
	return (EXIT_SUCCESS);
}
