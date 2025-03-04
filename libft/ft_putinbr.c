/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putinbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:13:06 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/26 14:32:46 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putinbr(int nb)
{
	long	l;
	int		len;

	if (!nb)
		return (ft_putchar('0'));
	l = nb;
	len = 0;
	if (l < 0)
	{
		len += ft_putchar('-');
		l = -l;
	}
	if (l >= 10)
		len += ft_putinbr(l / 10);
	len += ft_putchar((l % 10) + '0');
	return (len);
}

int	ft_putinbr_error(int nb, int n)
{
	long	l;
	int		len;

	if (!nb)
		return (ft_putchar_fd_error('0', n));
	l = nb;
	len = 0;
	if (l < 0)
	{
		len += ft_putchar_fd_error('-', n);
		l = -l;
	}
	if (l >= 10)
		len += ft_putinbr(l / 10);
	len += ft_putchar_fd_error((l % 10) + '0', n);
	return (len);
}