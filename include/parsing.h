/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:52:42 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/14 14:57:21 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

typedef enum	e_token_type
{
	WORD,      /* Commande ou argument*/
	PIPE,      /*  '|'  */
	REDIR_IN,  /*  '<'  */
	REDIR_OUT, /*  '>'  */
	APPEND,    /*  '>>'  */
	HEREDOC,   /*  '<<'  */
	AND,       /*  '&&'  */
	OR,        /*  '||'  */
}				t_token_type;

typedef struct			s_token
{
	t_token_type		type; /*  Type du token (PIPE, WORD, REDIR, etc.)  */
	char				*value;       /*  Valeur du token ("ls", ">", "file.txt", etc.)  */
	struct s_token		*next;
}						t_token;

typedef enum
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_OUT,
	NODE_REDIR_IN,
}	t_ast_type;

typedef struct		s_ast
{
	t_ast_type		type;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*  PARSING  */

t_token				*tokenize(char *input);

/*  UTILS  */

t_token				*create_token(t_token_type type, char *value);
t_token				*add_token(t_token **head, t_token_type type, char *value);
int					is_space(char c);
void				print_tokens(t_token *tokens);


/* A SUPPRIMER */
void	print_ast(t_ast *node, int level);