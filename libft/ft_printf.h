/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:18:38 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/27 15:23:02 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define BASE_TEN "0123456789"
# define LHEXBASE "0123456789abcdef"
# define UHEXBASE "0123456789ABCDEF"

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putinbr(int nb);
int	ft_putnbr_base(unsigned int nb, char *base);
int	ft_putadrr_base(void *n, char *base);

int	ft_printf_error(int n, const char *format, ...);
int	ft_putstr_fd_error(char *s, int fd);
int	ft_putinbr_error(int nb, int n);
int	ft_putnbr_base_error(unsigned int nbr, char *base, int n);
int	ft_putadrr_base_error(void *n, char *base, int fd);
int	ft_putchar_fd_error(char c, int fd);

#endif