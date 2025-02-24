/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:00:50 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/20 23:51:16 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static t_ast	*parse_command(t_token **tokens)
// {
// 	t_ast	*cmd;
// 	char	**args;
// 	int		i;

// 	args = malloc(sizeof(char *) * 10);
// 	if (!args)
// 		return (NULL);
// 	i = 0;
// 	while (*tokens && (*tokens)->type == WORD)
// 	{
// 		args[i] = ft_strdup((*tokens)->value);
// 		*tokens = (*tokens)->next;
// 		i++;
// 	}
// 	args[i] = NULL;
// 	cmd = create_command_node(args);
// 	return (cmd);
// }

t_ast_type	get_redir_type(t_token *token)
{
	if (token->type == REDIR_OUT)
		return (NODE_REDIR_OUT);
	if (token->type == REDIR_APPEND)
		return (NODE_APPEND);
	if (token->type == REDIR_IN)
		return (NODE_REDIR_IN);
	if (token->type == HEREDOC)
		return (NODE_HEREDOC);
	return (NODE_PIPE);
}

static char	**allocate_filename(t_token *token)
{
	char	**filename;

	filename = malloc(sizeof(char *) * 2);
	if (!filename)
		return (NULL);
	filename[0] = ft_strdup(token->value);
	if (!filename[0])
	{
		free(filename);
		return (NULL);
	}
	filename[1] = NULL;
	return (filename);
}

static t_ast	*parse_redir(t_token **tokens, t_ast *left)
{
	t_ast_type	type;
	t_ast		*file;
	char		**filename;

	while (*tokens && is_redirection((*tokens), 0))
	{
		if (*tokens && (*tokens)->next && (*tokens)->next->next
			&& (is_redirection((*tokens)->next, 1)
			|| is_redirection((*tokens)->next->next, 1)))
			return (NULL);
		type = get_redir_type(*tokens);
		*tokens = (*tokens)->next;
		if (!(*tokens) || (*tokens)->type != WORD)
		{
			if ((*tokens))
				printf("minishell: syntax error near expected token %s\n", get_ast_type_str(type));
			else
				printf("minishell: syntax error missing command after token %s\n", get_ast_type_str(type));
			return (NULL);
		}
		filename = allocate_filename(*tokens);
		if (!filename)
			return (*tokens = (*tokens)->next, NULL);
		file = create_command_node(filename);
		if (!file)
		{
			free(filename[0]);
			free(filename);
			*tokens = (*tokens)->next;
			return (NULL);
		}
		*tokens = (*tokens)->next;
		if (!left)
			left = file;
		else
			left = create_operator_node(type, left, file);
	}
	return (left);
}

t_ast	*parse_word(t_token **tokens, t_ast *left)
{
	t_ast	*node;

	node = parse_command(tokens);
	if (!left)
		return (node);
	else
		return (create_operator_node(NODE_PIPE, left, node));
}

t_ast	*parse_pipe(t_token **tokens, t_ast *left)
{
	t_ast	*right;

	if (!left && (*tokens)->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		return (NULL);
	}
	if (!(*tokens)->next || (*tokens)->next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '||'\n", 2);
		*tokens = (*tokens)->next;
		return (NULL);
	}
	*tokens = (*tokens)->next;
	right = parse_word(tokens, NULL);
	if (!right)
	{
		ft_putstr_fd("minishell: syntax error after '|'\n", 2);
		return (NULL);
	}
	return (create_operator_node(NODE_PIPE, left, right));
}

static t_ast	*parse_logical_operators(t_token **tokens, t_ast *left)
{
	t_ast	*right;
	t_token	*token;

	while (*tokens && ((*tokens)->type == AND || (*tokens)->type == OR))
	{
		token = *tokens;
		*tokens = (*tokens)->next;

		right = parse_pipe(tokens, NULL);
		if (!right)
		{
			ft_putstr_fd("minishell: syntax error after logical operator\n", 2);
			return (NULL);
		}
		left = create_operator_node((token->type == AND) ? NODE_AND : NODE_OR, left, right);
	}
	return (left);
}

t_ast	*parse(t_token **tokens)
{
	t_ast	*left = parse_redir(tokens, NULL);

	// Après avoir géré les redirections, on passe à la gestion des logiques
	left = parse_logical_operators(tokens, left);

	// Finalement, on gère les pipes
	if (*tokens && (*tokens)->type == PIPE)
		left = parse_pipe(tokens, left);

	return (left);
}

// t_ast	*parse(t_token **tokens)
// {
// 	t_ast	*left;

// 	left = NULL;
// 	while (*tokens)
// 	{
// 		if ((*tokens)->type == REDIR_OUT || (*tokens)->type == REDIR_IN
// 			|| (*tokens)->type == REDIR_APPEND || (*tokens)->type == HEREDOC)
// 			left = parse_redir(tokens, left);
// 		else if ((*tokens)->type == WORD)
// 			left = parse_word(tokens, left);
// 		else if ((*tokens)->type == PIPE)
// 			left = parse_pipe(tokens, left);
// 		else
// 		{
// 			ft_putstr_fd("minishell: syntax error: invalid token\n", 2);
// 			return (NULL); // Si un token invalide est trouvé
// 		}
// 		if (!left)
// 			return (NULL); // Si l'AST n'est pas correctement formée
// 	}
// 	return (left);
// }
