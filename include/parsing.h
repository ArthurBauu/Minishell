/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:52:42 by arbaudou          #+#    #+#             */
/*   Updated: 2025/02/11 15:37:49 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

typedef enum e_token_type
{
	WORD,      /* Commande ou argument*/
	PIPE,      /*  '|'  */
	REDIR_IN,  /*  '<'  */
	REDIR_OUT, /*  '>'  */
	APPEND,    /*  '>>'  */
	HEREDOC,   /*  '<<'  */
	AND,       /*  '&&'  */
	OR,        /*  '||'  */
}					t_token_type;

typedef struct s_token
{
	t_token_type type; /*  Type du token (PIPE, WORD, REDIR, etc.)  */
	char *value;       /*  Valeur du token ("ls", ">", "file.txt", etc.)  */
	struct s_token	*next;
}					t_token;

/*  PARSING  */

t_token				*tokenize(char *input);

/*  UTILS  */

t_token				*create_token(t_token_type type, char *value);
t_token				*add_token(t_token **head, t_token_type type, char *value);
int					is_space(char c);
void				print_tokens(t_token *tokens);
