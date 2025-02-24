/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:34:22 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/21 01:28:20 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main(void) {
    char *input;
    t_token *tokens;
    t_ast *ast;

    // Test 1: Simple command without error
    input = "echo 'Hello World'";
    printf("Testing: '%s'\n", input);
    tokens = tokenize(input);
	print_tokens(tokens);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");
    } else {
        printf("Error parsing command.\n");
    }
    printf("\n");

    // Test 2: Command with simple redirection (output)
    input = "echo Hello > file.txt";
    printf("Testing: '%s'\n", input);
    tokens = tokenize(input);
	print_tokens(tokens);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");
    } else {
        printf("Error parsing command.\n");
    }
    printf("\n");

    // Test 3: Command with append redirection (>>)
    input = "echo Hello >> file.txt";
    printf("Testing: '%s'\n", input);
	print_tokens(tokens);
    tokens = tokenize(input);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");
    } else {
        printf("Error parsing command.\n");
    }
    printf("\n");

    // Test 4: Command with pipe
    input = "echo Hello | grep Hello";
    printf("Testing: '%s'\n", input);
    tokens = tokenize(input);
	print_tokens(tokens);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");
    } else {
        printf("Error parsing command.\n");
    }
    printf("\n");

    // Test 5: Command with logical AND (&&)
    input = "echo Hello && echo World";
    printf("Testing: '%s'\n", input);
    tokens = tokenize(input);
	print_tokens(tokens);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");
    } else {
        printf("Error parsing command.\n");
    }
    printf("\n");

    // Test 6: Command with logical OR (||)
    input = "echo Hello || echo World";
    printf("Testing: '%s'\n", input);
    tokens = tokenize(input);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");
    } else {
        printf("Error parsing command.\n");
    }
    printf("\n");

    // Test 7: Command with missing redirection argument
    input = "echo Hello >";
    printf("Testing: '%s'\n", input);
    tokens = tokenize(input);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");
    } else {
        printf("minishell: syntax error near unexpected token '>'\n");
    }
    printf("\n");

    // Test 8: Command with logical OR at the end
    input = "echo Hello ||";
    printf("Testing: '%s'\n", input);
    tokens = tokenize(input);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");
    } else {
        printf("minishell: syntax error after logical operator\n");
    }
    printf("\n");

    // Test 9: Command with unknown operator '>>>'
    input = "echo Hello >>> file.txt";
    printf("Testing: '%s'\n", input);
    tokens = tokenize(input);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");
    } else {
        printf("minishell: unknown operator '>>>'\n");
    }
    printf("\n");

    // Test 10: Empty command
    input = "";
    printf("Testing: '%s'\n", input);
    tokens = tokenize(input);
    ast = parse(&tokens);
    if (ast) {
        print_ast(ast, 0);
        printf("No errors, AST created successfully.\n");
    } else {
        printf("Error parsing command.\n");
    }
    printf("\n");

    return 0;
}

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