/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:21:39 by mahautdharc       #+#    #+#             */
/*   Updated: 2025/03/18 16:24:32 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// NON UTILISE

char	*ft_strdup_mini(const char *s)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (len + 1 != 0)
	{
		while (i < len && s[i])
		{
			if (s[i] != '\'' && s[i] != '"')
			{
				str[j] = s[i];
				j++;
			}
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
