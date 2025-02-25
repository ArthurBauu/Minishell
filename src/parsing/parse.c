/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:48:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/25 01:38:33 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

/* FONCTION TROP LONGUE IL FAUT QUE JE LA RACOURCISSE */

static t_ast	*parse_redir(t_token **tokens, t_ast *cmd)
{
	t_ast_type	type;
	t_ast		*file;
	char		**filename;

	while (*tokens && is_redirection((*tokens), 0))
	{
		if ((*tokens)->next && is_redirection((*tokens)->next, 1))
		{
			printf("minishell: syntax error near unexpected token '%s'\n",
				(*tokens)->next->value);
			return (NULL);
		}
		type = get_redir_type(*tokens);
		*tokens = (*tokens)->next;
		if (!(*tokens) || ((*tokens)->type != COMMAND
				&& (*tokens)->type != ARGUMENT))
		{
			printf("minishell: syntax error: missing filename after '%s'\n",
				get_ast_type_str(type));
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
		if (!cmd)
			cmd = create_operator_node(type, file, NULL);
		else
			cmd = create_operator_node(type, cmd, file);
	}
	return (cmd);
}

t_ast	*parse_word(t_token **tokens, t_ast *left)
{
	t_ast	*node;

	if (!tokens || !(*tokens))
		return (NULL);
	if ((*tokens)->type == COMMAND)
		node = parse_command(tokens);
	else if ((*tokens)->type == COMMAND || (*tokens)->type == ARGUMENT)
	{
		if (left)
		{
			left = add_argument_to_command(left, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		else
		{
			left = create_command_node(&(*tokens)->value);
			*tokens = (*tokens)->next;
		}
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (NULL);
	}
	node = parse_redir(tokens, node);
	return (node);
}

t_ast	*parse(t_token **tokens)
{
	t_ast	*left;

	while (*tokens)
	{
		if ((*tokens)->type == REDIR_OUT || (*tokens)->type == REDIR_IN
			|| (*tokens)->type == REDIR_APPEND || (*tokens)->type == HEREDOC)
			left = parse_redir(tokens, left);
		else if ((*tokens)->type == WORD || (*tokens)->type == COMMAND
			|| (*tokens)->type == ARGUMENT)
			left = parse_word(tokens, left);
		else if ((*tokens)->type == PIPE)
			left = parse_pipe(tokens, left);
		else if ((*tokens)->type == AND || (*tokens)->type == OR)
			left = parse_logical_operator(tokens, left);
		else
		{
			ft_putstr_fd("minishell: syntax error: invalid token\n", 2);
			return (NULL);
		}
		if (!left)
			return (NULL);
	}
	return (left);
}
