/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:48:13 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/21 01:11:35 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast *parse_command(t_token **tokens)
{
    char **args;
    int i = 0;

    args = malloc(sizeof(char *) * (count_args(*tokens) + 1)); // Compte tous les arguments
    if (!args)
        return (NULL);
    
    while (*tokens && (*tokens)->type == WORD)
    {
        args[i++] = ft_strdup((*tokens)->value);
        *tokens = (*tokens)->next;
    }
    args[i] = NULL;

    return (create_command_node(args));
}

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
	if (token->type == AND)
		return (NODE_AND);
	if (token->type == OR)
		return (NODE_OR);
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

static t_ast	*parse_redir(t_token **tokens, t_ast *cmd)
{
	t_ast_type	type;
	t_ast		*file;
	char		**filename;

	while (*tokens && is_redirection((*tokens), 0))
	{
		// Vérifie si une autre redirection suit immédiatement (syntaxe invalide)
		if ((*tokens)->next && is_redirection((*tokens)->next, 1))
		{
			printf("minishell: syntax error near unexpected token '%s'\n", (*tokens)->next->value);
			return (NULL);
		}

		type = get_redir_type(*tokens);
		*tokens = (*tokens)->next;

		// Vérification de l'existence d'un fichier après la redirection
		if (!(*tokens) || (*tokens)->type != WORD)
		{
			printf("minishell: syntax error: missing filename after '%s'\n", get_ast_type_str(type));
			return (NULL);
		}

		// Allocation et vérification du nom de fichier
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

		// Si `cmd` est NULL (pas encore de commande), on crée un nœud de redirection sans commande associée
		if (!cmd)
			cmd = create_operator_node(type, file, NULL);
		else
			cmd = create_operator_node(type, cmd, file);
	}

	return (cmd);
}


t_ast *parse_word(t_token **tokens, t_ast *left)
{
    t_ast *node;

    (void)left;
    if (is_command((*tokens)->value))
    {
        node = parse_command(tokens);
    }
    else
    {
        node = create_command_node(&(*tokens)->value);
        *tokens = (*tokens)->next;
    }
    node = parse_redir(tokens, node);
    return (node);
}

t_ast *parse_pipe(t_token **tokens, t_ast *left)
{
    t_ast *right;

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

t_ast *parse_logical_operator(t_token **tokens, t_ast *left)
{
    t_ast *right;
    t_ast_type type;

    if ((*tokens)->type == AND)
        type = NODE_AND;
    else if ((*tokens)->type == OR)
        type = NODE_OR;
    else
        return (NULL); // Gestion de cas inattendus
    
    // Avancer dans la liste de tokens après le opérateur logique
    *tokens = (*tokens)->next;
    
    // Vérifie si un autre token valide suit
    if (!(*tokens) || (*tokens)->type != WORD)
    {
        ft_putstr_fd("minishell: syntax error after logical operator\n", 2);
        return (NULL);
    }

    // Parse la commande de droite
    right = parse_word(tokens, NULL);
    if (!right)
    {
        ft_putstr_fd("minishell: syntax error after logical operator\n", 2);
        return (NULL);
    }

    // Créer le nœud de l'AST pour l'opérateur logique
    return (create_operator_node(type, left, right));
}

t_ast *parse(t_token **tokens)
{
    t_ast *left = NULL;

    while (*tokens)
    {
        if ((*tokens)->type == REDIR_OUT || (*tokens)->type == REDIR_IN
            || (*tokens)->type == REDIR_APPEND || (*tokens)->type == HEREDOC)
            left = parse_redir(tokens, left);
        else if ((*tokens)->type == WORD)
            left = parse_word(tokens, left);
        else if ((*tokens)->type == PIPE)
            left = parse_pipe(tokens, left);
        else if ((*tokens)->type == AND || (*tokens)->type == OR)
            left = parse_logical_operator(tokens, left);
        else
        {
            ft_putstr_fd("minishell: syntax error: invalid token\n", 2);
            return (NULL); // Si un token invalide est trouvé
        }
    
        if (!left)
            return (NULL);
	}
    return (left);
}
