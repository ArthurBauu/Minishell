/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:00:37 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 18:49:13 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* dans limits.h la longueur max d'un path est 4096 */
/* fonctionne meme si PWD unset */

int	ft_pwd(char **args)
{
	char	cwd[4096];

	if (args[1])
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: pwd");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
