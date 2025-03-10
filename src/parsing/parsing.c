/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:37:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/10 00:28:25 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int parsing(char *input)
{	
	t_token *tokens;
	t_token *start;
    t_ast *ast;
	
	printf("Testing: '%s'\n", input);
	start = tokenize(input);
	if (start == NULL)
		return (0);
	tokens = start;
	print_tokens(tokens);
	ast = parse(&tokens);
	if (ast) {
		print_ast(ast, 0);
		printf("No errors, AST created successfully.\n");
	} else {
		printf("Error parsing command.\n");
	}
	printf("\n");
	free_all(ast, start);
	return (1);
}