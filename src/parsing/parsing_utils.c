/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:33:15 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/10 00:23:32 by arbaudou         ###   ########.fr       */
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
	if ((*tokens)->type == 1 || (*tokens)->type == 6 || (*tokens)->type == 7)
	{
		if ((*tokens)->type == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		if ((*tokens)->type == 6)
		ft_putstr_fd("minishell: syntax error near unexpected token '&&'\n", 2);
		if ((*tokens)->type == 7)
		ft_putstr_fd("minishell: syntax error near unexpected token '||'\n", 2);
		return (-1);
	}
	return (1);
}