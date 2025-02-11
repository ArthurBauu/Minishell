/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:11:11 by arthur            #+#    #+#             */
/*   Updated: 2025/01/10 12:59:53 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	len;

	if (!str)
		str = "(null)";
	len = 0;
	len = ft_strplen(str);
	return (write(1, str, len));
}
