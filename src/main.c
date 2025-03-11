/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:34:22 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/11 03:15:51 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	g_exit_status = 42;


int main() {
    char *input;


	// // // Test 0 : test  : 
	// input = " echo hello <<<";
	// parsing(input);

    // // Test 1: Command with input redirection
    // input = " echo hi && << EOF grep hi ";
    // parsing(input);

    // // Test 2: Command with output redirection
    input = " echo hello | < out.txt test1 test etstet st ett | test tets ";
    parsing(input);

    // // Test 3: Command with output redirection (append)
    // input = " echo hello >> out.txt ";
    // parsing(input);

    // // Test 4: Pipe with input redirection
    // input = " cat < infile | grep hello ";
    // parsing(input);

    // // Test 5: Pipe with multiple output redirections
    // input = " ls > file | grep test >> output.txt ";
	// parsing(input);

    // // Test 6: Command with redirection and logical AND
    // input = " ls > file && echo Done ";
    // parsing(input);

    // // Test 7: Command with redirection and logical OR
    // input = " ls > file || echo Error ";
    // parsing(input);

    // // Test 8: Pipe with output redirection and logical AND
    // input = " ls | grep test > result.txt && echo Done ";
    // parsing(input);

    // // Test 9: Syntax error in redirection
    // input = " ls > | file echo";
	// parsing(input);

    // // Test 10: Multiple redirections and pipes in chain
    // input = " cat < infile | grep test > out.txt | wc -l ";
	// parsing(input);

    return 0;
}

/* MAIN TEST CLASSIC */

// int main(void) {
//     char *input;
//     t_token *tokens;
// 	t_token *start;
//     t_ast *ast;
// 	t_ast *ast_start;

//     // Test 1: Simple command without error
//     input = " < infile grep 'hello' | wc -l";
//     ft_printf_error( 2, "Testing: '%s'\n", input);
// 	input = expand_variable(input);
// 	ft_printf_error( 2, "Testing: '%s'\n", input);
//     start = tokenize(input);
// 	tokens = start;
//     print_tokens(tokens);
//     ast_start = parse(&tokens);
// 	ast = ast_start;
//     if (ast) {
//         print_ast(ast, 0);
//         ft_printf_error( 2, "No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");
// 	free(input);
// 	free_all(ast_start, start);

//     // Test 2: Command with simple redirection (output)
//     input = " > outfile pwd ";
//     printf("Testing: '%s'\n", input);
//     tokens = tokenize(input);
//     print_tokens(tokens);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");
// 	free(input);
// 	free_all(ast, tokens);

//     // Test 3: Command with append redirection (>>)
//     input = "echo Hello > file.txt";
//     printf("Testing: '%s'\n", input);
//     tokens = tokenize(input);
//     print_tokens(tokens);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");

//     // Test 4: Command with pipe
//     input = "echo Hello | grep Hello";
//     printf("Testing: '%s'\n", input);
//     tokens = tokenize(input);
//     print_tokens(tokens);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");

//     // Test 5: Command with logical AND (&&)
//     input = "echo Hello && echo World";
//     printf("Testing: '%s'\n", input);
//     tokens = tokenize(input);
//     print_tokens(tokens);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");

//     // Test 6: Command with logical OR (||)
//     input = "echo Hello || echo World";
//     printf("Testing 6: '%s'\n", input);
//     tokens = tokenize(input);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");

//     // Test 7: Command with missing redirection argument
//     input = "echo Hello >";
//     printf("Testing 7 : '%s'\n", input);
//     tokens = tokenize(input);
//     if (tokens) {
//         ast = parse(&tokens);
//         if (ast) {
//             print_ast(ast, 0);
//             printf("No errors, AST created successfully.\n");
//         } else {
//             // printf("minishell: syntax error near unexpected token '>'\n");
//         }
//         printf("\n");
//     }
//     printf("\n");

//     // Test 8: Command with logical OR at the end
//     input = "echo Hello ||";
//     printf("Testing 8 : '%s'\n", input);
//     tokens = tokenize(input);
//     if (tokens) {
//         ast = parse(&tokens);
//         if (ast) {
//             print_ast(ast, 0);
//             printf("No errors, AST created successfully.\n");
//         }
//         printf("\n");
//     }
//     printf("\n");

//     // Test 9: Command with unknown operator '>>>'
//     input = "echo Hello >>> file.txt";
//     printf("Testing 9 : '%s'\n", input);
//     tokens = tokenize(input);
//     if (tokens) {
//         ast = parse(&tokens);
//         if (ast) {
//             print_ast(ast, 0);
//             printf("No errors, AST created successfully.\n");
//         }
//         printf("\n");
//     }
//     printf("\n");

//     // Test 10: Empty command
//     input = "";
//     printf("Testing 10 : '%s'\n", input);
//     tokens = tokenize(input);
//     if (tokens) {
//         ast = parse(&tokens);
//         if (ast) {
//             print_ast(ast, 0);
//             printf("No errors, AST created successfully.\n");
//         }
//         printf("\n");
//     }
//     printf("\n");

//     // --- New Tests --- //

//     // Test 11: Redirection without filename
//     input = "echo Hello >";
//     printf("Testing 11: '%s'\n", input);
//     tokens = tokenize(input);
//     if (tokens) {
//         ast = parse(&tokens);
//         if (ast) {
//             print_ast(ast, 0);
//             printf("No errors, AST created successfully.\n");
//         } else {
//             // printf("minishell: syntax error: missing filename after '>'\n");
//         }
//     }
//     printf("\n");

//     // Test 12: Redirection with invalid token after it
//     input = "echo Hello > |";
//     printf("Testing 12: '%s'\n", input);
//     tokens = tokenize(input);
//     if (tokens) {
//         ast = parse(&tokens);
//         if (ast) {
//             print_ast(ast, 0);
//             printf("No errors, AST created successfully.\n");
//         } else {
//             // printf("minishell: syntax error near unexpected token '|'\n");
//         }
//     }
//     printf("\n");

//     // Test 13: Missing command before pipe
//     input = "| echo Hello";
//     printf("Testing 13: '%s'\n", input);
//     tokens = tokenize(input);
//     if (tokens) {
//         ast = parse(&tokens);
//         if (ast) {
//             print_ast(ast, 0);
//             printf("No errors, AST created successfully.\n");
//         } else {
//             // printf("minishell: syntax error: missing command before '|'\n");
//         }
//     }
//     printf("\n");

//     // Test 14: Logical AND without second command
//     input = "echo Hello &&";
//     printf("Testing 14: '%s'\n", input);
//     tokens = tokenize(input);
//     if (tokens) {
//         ast = parse(&tokens);
//         if (ast) {
//             print_ast(ast, 0);
//             printf("No errors, AST created successfully.\n");
//         } else {
//             // printf("minishell: syntax error after logical operator\n");
//         }
//     }
//     printf("\n");

//     // Test 15: Logical OR with invalid command
//     input = "echo Hello || &&";
//     printf("Testing 15: '%s'\n", input);
//     tokens = tokenize(input);
//     if (tokens) {
//         ast = parse(&tokens);
//         if (ast) {
//             print_ast(ast, 0);
//             printf("No errors, AST created successfully.\n");
//         } else {
//             // printf("minishell: syntax error after logical operator\n");
//         }
//     }
//     printf("\n");

//     return 0;
// }


// int main(void) {
//     char *input;
//     t_token *tokens;
//     t_ast *ast;

//     // Test 1: Simple command without error
//     input = "echo 'Hello World'";
//     printf("Testing: '%s'\n", input);
//     tokens = tokenize(input);
// 	print_tokens(tokens);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");

//     // Test 2: Command with simple redirection (output)
//     input = "echo Hello > file.txt";
//     printf("Testing: '%s'\n", input);
//     tokens = tokenize(input);
// 	print_tokens(tokens);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");

//     // Test 3: Command with append redirection (>>)
//     input = "echo Hello >> file.txt";
//     printf("Testing: '%s'\n", input);
//     tokens = tokenize(input);
// 	print_tokens(tokens);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");

//     // Test 4: Command with pipe
//     input = "echo Hello | grep Hello";
//     printf("Testing: '%s'\n", input);
//     tokens = tokenize(input);
// 	print_tokens(tokens);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");

//     // Test 5: Command with logical AND (&&)
//     input = "echo Hello && echo World";
//     printf("Testing: '%s'\n", input);
//     tokens = tokenize(input);
// 	print_tokens(tokens);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");

//     // Test 6: Command with logical OR (||)
//     input = "echo Hello || echo World";
//     printf("Testing 6: '%s'\n", input);
//     tokens = tokenize(input);
//     ast = parse(&tokens);
//     if (ast) {
//         print_ast(ast, 0);
//         printf("No errors, AST created successfully.\n");
//     } else {
//         printf("Error parsing command.\n");
//     }
//     printf("\n");

//     // Test 7: Command with missing redirection argument
//     input = "echo Hello >";
//     printf("Testing 7 : '%s'\n", input);
//     tokens = tokenize(input);
// 	if (tokens)
// 	{
// 		ast = parse(&tokens);
// 		if (ast) {
// 			print_ast(ast, 0);
// 			printf("No errors, AST created successfully.\n");
// 		} else {
// 			printf("minishell: syntax error near unexpected token '>'\n");
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");


//     // Test 8: Command with logical OR at the end
//     input = "echo Hello ||";
//     printf("Testing 8 : '%s'\n", input);
//     tokens = tokenize(input);
// 	if (tokens)
// 	{
// 		ast = parse(&tokens);
// 		if (ast) {
// 			print_ast(ast, 0);
// 			printf("No errors, AST created successfully.\n");
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");

//     // Test 9: Command with unknown operator '>>>'
//     input = "echo Hello >>> file.txt";
//     printf("Testing 9 : '%s'\n", input);
//     tokens = tokenize(input);
// 	if (tokens)
// 	{
// 		ast = parse(&tokens);
// 		if (ast) {
// 			print_ast(ast, 0);
// 			printf("No errors, AST created successfully.\n");
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");

//     // Test 10: Empty command
//     input = "";
//     printf("Testing 10 : '%s'\n", input);
//     tokens = tokenize(input);
// 	if (tokens)
// 	{
// 		ast = parse(&tokens);
// 		if (ast) {
// 			print_ast(ast, 0);
// 			printf("No errors, AST created successfully.\n");
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");

//     return 0;
// }

// int	main(void)
// {
// 	char *input;
// 	t_token *tokens;
// 	t_ast *ast;

// 	// Test 1: Commande simple sans erreur
// 	input = "echo Hello World";
// 	printf("Testing: '%s'\n", input);
// 	tokens = tokenize(input);
// 	ast = parse(&tokens);
// 	if (ast)
// 	{
// 		print_ast(ast);
// 		printf("No errors, AST created successfully.\n");
// 	}
// 	else
// 		printf("Error parsing command.\n");
// 	printf("\n");

// 	// Test 2: Commande avec redirection simple (sortie)
// 	input = "echo Hello > file.txt";
// 	printf("Testing: '%s'\n", input);
// 	tokens = tokenize(input);
// 	ast = parse(&tokens);
// 	if (ast)
// 	{
// 		print_ast(ast);
// 		printf("No errors, AST created successfully.\n");
// 	}
// 	else
// 		printf("Error parsing command.\n");
// 	printf("\n");

// 	// Test 3: Commande avec redirection double (append)
// 	input = "echo Hello >> file.txt";
// 	printf("Testing: '%s'\n", input);
// 	tokens = tokenize(input);
// 	ast = parse(&tokens);
// 	if (ast)
// 	{
// 		print_ast(ast);
// 		printf("No errors, AST created successfully.\n");
// 	}
// 	else
// 		printf("Error parsing command.\n");
// 	printf("\n");

// 	// Test 4: Commande avec pipe
// 	input = "echo Hello | grep Hello";
// 	printf("Testing: '%s'\n", input);
// 	tokens = tokenize(input);
// 	ast = parse(&tokens);
// 	if (ast)
// 	{
// 		print_ast(ast);
// 		printf("No errors, AST created successfully.\n");
// 	}
// 	else
// 		printf("Error parsing command.\n");
// 	printf("\n");

// 	// Test 5: Commande avec opérateur logique AND
// 	input = "echo Hello && echo World";
// 	printf("Testing: '%s'\n", input);
// 	tokens = tokenize(input);
// 	ast = parse(&tokens);
// 	if (ast)
// 	{
// 		print_ast(ast);
// 		printf("No errors, AST created successfully.\n");
// 	}
// 	else
// 		printf("Error parsing command.\n");
// 	printf("\n");

// 	// Test 6: Commande avec opérateur logique OR
// 	input = "echo Hello || echo World";
// 	printf("Testing: '%s'\n", input);
// 	tokens = tokenize(input);
// 	ast = parse(&tokens);
// 	if (ast)
// 	{
// 		print_ast(ast);
// 		printf("No errors, AST created successfully.\n");
// 	}
// 	else
// 		printf("Error parsing command.\n");
// 	printf("\n");

// 	// Test 7: Commande avec erreur de syntaxe (redirection manquante)
// 	input = "echo Hello >";
// 	printf("Testing: '%s'\n", input);
// 	tokens = tokenize(input);
// 	ast = parse(&tokens);
// 	if (ast)
// 	{
// 		print_ast(ast);
// 		printf("No errors, AST created successfully.\n");
// 	}
// 	else
// 		printf("Error parsing command.\n");
// 	printf("\n");

// 	// Test 8: Commande avec erreur de syntaxe (pipe mal placé)
// 	input = "echo Hello ||";
// 	printf("Testing: '%s'\n", input);
// 	tokens = tokenize(input);
// 	ast = parse(&tokens);
// 	if (ast)
// 	{
// 		print_ast(ast);
// 		printf("No errors, AST created successfully.\n");
// 	}
// 	else
// 		printf("Error parsing command.\n");
// 	printf("\n");

// 	// Test 9: Commande avec erreur de syntaxe (double redirection)
// 	input = "echo Hello >>> file.txt";
// 	printf("Testing: '%s'\n", input);
// 	tokens = tokenize(input);
// 	ast = parse(&tokens);
// 	if (ast)
// 	{
// 		print_ast(ast);
// 		printf("No errors, AST created successfully.\n");
// 	}
// 	else

// 		printf("Error parsing command.\n");
// 	printf("\n");

// 	// Test 10: Commande vide
// 	input = "";
// 	printf("Testing: '%s'\n", input);
// 	tokens = tokenize(input);
// 	ast = parse(&tokens);
// 	if (ast)
// 	{
// 		print_ast(ast);
// 		printf("No errors, AST created successfully.\n");
// 	}
// 	else
// 		printf("Error parsing command.\n");
// 	printf("\n");

// 	// Clean up
// 	// free_tokens(tokens);
// 	// free_ast(ast);

// 	return (0);
// }