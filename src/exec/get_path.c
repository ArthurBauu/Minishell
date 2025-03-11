/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:54:20 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 13:47:31 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*freejoin(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin((const char *) s1, (const char *) s2);
	if (temp)
		free(s1);
	return (temp);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*pathname;
	int		i;

	i = 0;
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	paths = ft_split(*envp + 5, ':');
	while (paths[i] != NULL)
	{
		pathname = ft_strjoin(paths[i], "/");
		pathname = freejoin(pathname, cmd);
		if (access(pathname, X_OK) == 0)
		{
			free_strtab(paths);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	free_strtab(paths);
	return (NULL);
}
