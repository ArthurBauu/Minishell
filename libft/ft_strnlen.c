/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:28:05 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/11 15:15:23 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strnlen(const char *s, size_t maxlen) {
    size_t len = 0;

    while (len < maxlen && s[len] != '\0') {
        len++;
    }

    return len;
}
