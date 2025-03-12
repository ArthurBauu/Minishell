/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:37:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/12 00:15:08 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_input(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (-1);
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (1);
		i++;
	}
	return (-1);
}

void	parsing(char *input, t_shell *shell)
{
	if (check_input(input) == -1)
		exit(EXIT_FAILURE);
			/* pareil ici il faut re donner le prompt sans exit*/
	shell->tokens = tokenize(input);
	if (shell->tokens == NULL)
		exit(EXIT_FAILURE);
	/* je sais pas comment exit vu que j'ai pas exactement compris comment ca fonctionnais
	ta partie mais en gros si c'est nul faut juste renvoyer le promp a la place du exit*/
	shell->tokens_copy = shell->tokens;
	shell->root = parse(&shell->tokens);
	/* 	if (shell->root) {
			print_ast(shell->root, 0);
		} */
}