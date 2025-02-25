/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:52:42 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/25 13:45:38 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "libft.h"
#include <stdio.h>

typedef enum e_token_type
{
	COMMAND,      /*  Commandes  */
	ARGUMENT,     /*  Arguments  */
	WORD,         /*  Commande ou argument*/
	PIPE,         /*  '|'  */
	REDIR_IN,     /*  '<'  */
	REDIR_OUT,    /*  '>'  */
	REDIR_APPEND, /*  '>>'  */
	HEREDOC,      /*  '<<'  */
	AND,          /*  '&&'  */
	OR,           /*  '||'  */
}					t_token_type;

typedef struct s_token
{
	t_token_type type; /*  Type du token (PIPE, WORD, REDIR, etc.)  */
	char *value;       /*  Valeur du token ("ls", ">", "file.txt", etc.)  */
	struct s_token	*next;
}					t_token;

typedef enum
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_OUT,
	NODE_APPEND,
	NODE_REDIR_IN,
	NODE_HEREDOC,
	NODE_AND,
	NODE_OR,
}					t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	char			**value;
	char			*file;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*  PARSING  */

t_token				*tokenize(char *input);
t_ast				*parse(t_token **tokens);
t_ast				*parse_command(t_token **tokens);
t_ast				*parse_word(t_token **tokens, t_ast *left);
t_ast				*parse_pipe(t_token **tokens, t_ast *left);
t_ast				*parse_logical_operator(t_token **tokens, t_ast *left);
int					handle_and(char *input, int i, t_token **tokens);
int					handle_or(char *input, int i, t_token **tokens);
int					handle_pipe(char *input, int i, t_token **tokens);
int					handle_redirection_out(char *input, int i,
						t_token **tokens);
int					handle_redirection_in(char *input, int i, t_token **tokens);

/*  NODES  */
t_ast				*create_command_node(char **args);
t_ast				*create_operator_node(t_ast_type type, t_ast *left,
						t_ast *right);

/*  UTILS  */

t_token				*create_token(t_token_type type, char *value);
t_token				*add_token(t_token **head, t_token_type type, char *value);
int					is_space(char c);
void				print_tokens(t_token *tokens);
int					is_redirection(t_token *token, int n);
const char			*get_ast_type_str(t_ast_type type);
const char			*get_token_type_str(t_token_type type);
int					count_args(t_token *tokens);
int					is_command(char *word);
int					is_operator(char *word);
void				classify_tokens(t_token *tokens);
t_ast				*add_argument_to_command(t_ast *cmd_node, char *arg);
t_ast_type			get_redir_type(t_token *token);

/* A SUPPRIMER */
void				print_ast(t_ast *node, int level);
