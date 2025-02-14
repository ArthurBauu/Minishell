/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:34:22 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/14 14:57:54 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int	main(void)
{
	// char input[] = "ls -l | grep txt > output.txt";
	char input2[] = "echo 'Hello world' | grep \"path/to/dir\" > output.txt";
	// t_token *tokens = tokenize(input);
	t_token *tokens2 = tokenize(input2);
	// print_tokens(tokens);
	print_tokens(tokens2);
	return (0);
}


// int main() {
//     // Exemple : `echo "Hello" | grep Hello > output.txt`
//     t_token *tokens = tokenize("echo \"Hello\" | grep Hello > output.txt");

//     printf("\n=== TOKENS ===\n");
//     print_tokens(tokens);

//     printf("\n=== PARSING ===\n");
//     t_ast *ast = parse(&tokens);

//     printf("\n=== AST ===\n");
//     print_ast(ast, 0);

//     return 0;
// }
