/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadrrbase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:23:34 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/27 15:20:54 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putadrr_base(void *n, char *base)
{
	unsigned int		size;
	int					len;
	unsigned long long	nbr;

	if (!n)
		return (ft_putstr("(nil)"));
	size = ft_strlen(base);
	len = 0;
	nbr = (unsigned long long)n;
	if (nbr >= size)
		len += ft_putadrr_base((void *)(nbr / size), base);
	if (len == 0)
		len += ft_putstr("0x");
	len += write(1, &base[nbr % size], 1);
	return (len);
}

int	ft_putadrr_base_error(void *n, char *base, int fd)
{
	unsigned int		size;
	int					len;
	unsigned long long	nbr;

	if (!n)
		return (ft_putstr_fd_error("(nil)", fd));
	size = ft_strlen(base);
	len = 0;
	nbr = (unsigned long long)n;
	if (nbr >= size)
		len += ft_putadrr_base_error((void *)(nbr / size), base, fd);
	if (len == 0)
		len += ft_putstr("0x");
	len += write(fd, &base[nbr % size], 1);
	return (len);
}