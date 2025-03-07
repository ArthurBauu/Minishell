/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:33:15 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/06 17:06:04 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	print_error(t_token *tokens)
{
	ft_printf_error(2, "minishell: invalid token '%s' in first position\n",
		tokens->value);
	return (1);
}

int check_error(t_token **tokens)
{
	if ((*tokens)->type == 3 || (*tokens)->type == 8 || (*tokens)->type == 9)
		return (print_error(*tokens), -1);
	if ((*tokens)->type == 1 && ((*tokens)->next->type == 8 || (*tokens)->next->type == 9))
		return (print_error(*tokens), -1);
	return (1);
}