/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:35:47 by arbaudou          #+#    #+#             */
/*   Updated: 2024/10/24 15:45:32 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*nstr;

	if (!s || !f)
		return (NULL);
	i = 0;
	nstr = ft_strdup(s);
	if (!nstr)
		return (NULL);
	while (nstr[i])
	{
		nstr[i] = f(i, nstr[i]);
		i++;
	}
	return (nstr);
}
