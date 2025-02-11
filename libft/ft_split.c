/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:43:46 by arbaudou          #+#    #+#             */
/*   Updated: 2024/11/21 16:43:42 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **tab, int index)
{
	while (index > 0)
		free(tab[--index]);
	free (tab);
	return ;
}

static int	count_words(char *str, char sep)
{
	int	i;
	int	nbw;

	i = 0;
	nbw = 0;
	if (sep != str[i] && str[i])
		nbw++;
	while (str[i])
	{
		if (sep == str[i] && str[i + 1] && sep != str[i + 1])
			nbw++;
		i++;
	}
	return (nbw);
}

static char	**split_str(char **tab, char *str, char sep, int index)
{
	int	len;
	int	i;

	i = 0;
	while (str[i] && sep != str[i])
		i++;
	len = i;
	tab[index] = malloc(sizeof(char) * (len + 1));
	if (!tab[index])
	{
		ft_free(tab, index);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		tab[index][i] = str[i];
		i++;
	}
	tab[index][i] = '\0';
	(index)++;
	return (tab);
}

static char	**create_tab(char **tab, char *str, char sep, int nbw)
{
	int	i;
	int	index;

	i = ((index = 0));
	while (str[i] && index < nbw)
	{
		if (str[i] && sep == str[i])
			i++;
		if (str[i] && sep != str[i])
		{
			if (!split_str(tab, &str[i], sep, index))
				return (NULL);
			index++;
			while (str[i] && sep != str[i])
				i++;
		}
	}
	tab[nbw] = NULL;
	return (tab);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		nbw;

	if (!s)
		return (NULL);
	nbw = count_words(s, c);
	tab = malloc(sizeof(char *) * (nbw + 1));
	if (!tab)
	{
		return (NULL);
	}
	if (!create_tab(tab, s, c, nbw))
		return (NULL);
	return (tab);
}
