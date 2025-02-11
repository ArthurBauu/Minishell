/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:33:43 by arbaudou          #+#    #+#             */
/*   Updated: 2024/10/24 15:50:57 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_a_space(char c, char const *sep)
{
	size_t	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

static void	ft_copystr(const char *s, char *tempstr,
	unsigned int start, unsigned int end)
{
	unsigned int	i;

	i = 0;
	while (start <= end)
	{
		tempstr[i] = s[start];
		start++;
		i++;
	}
	tempstr[i] = '\0';
}

char	*ft_strtrim(const char *s, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*tempstr;

	if (!s)
		return (NULL);
	i = 0;
	while (ft_is_a_space(s[i], set))
		i++;
	if (s[i] == '\0')
		return (ft_strdup(""));
	j = (unsigned int)(ft_strlen(s) - 1);
	while (j > i && ft_is_a_space(s[j], set))
		j--;
	tempstr = malloc(sizeof(char) * (j - i + 2));
	if (!tempstr)
		return (NULL);
	ft_copystr(s, tempstr, i, j);
	return (tempstr);
}
