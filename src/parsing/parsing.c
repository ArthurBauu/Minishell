/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:37:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/11 03:04:43 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int parsing(char *input)
{	
	t_token *tokens;
	t_token *start;
    t_ast *ast;
	t_ast *start_ast;
	
	printf("Testing: '%s'\n", input);
	start = tokenize(input);
	if (start == NULL)
		return (0);
	tokens = start;
	print_tokens(tokens);
	start_ast = parse(&tokens);
	ast = start_ast;
	if (ast) {
		print_ast(ast, 0);
		printf("No errors, AST created successfully.\n");
	} else {
		printf("Error parsing command.\n");
	}
	printf("\n");
	free_all(start_ast, start);
	return (1);
}