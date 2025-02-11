/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:48:42 by arbaudou          #+#    #+#             */
/*   Updated: 2024/10/24 19:13:03 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*nstr;

	slen = ft_strlen(s);
	if (!s)
		return (NULL);
	i = 0;
	if (start >= (unsigned int)slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = (ft_strlen(s + start));
	nstr = malloc(sizeof(char) * (len + 1));
	if (!nstr)
		return (NULL);
	while (i < len)
	{
		nstr[i] = s[start];
		i++;
		start++;
	}
	nstr[i] = '\0';
	return (nstr);
}
