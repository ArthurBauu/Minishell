/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:44:35 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/18 15:17:26 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "libft.h"
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <dirent.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_last_exit_code;

typedef enum e_token_type
{
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
	t_token_type	type; /*  Type du token (PIPE, WORD, REDIR, etc.)  */
	char			*value;       /*  Valeur du token ("ls", ">", "file.txt", etc.)  */
	int				is_quoted;
	struct s_token	*next;
}					t_token;

typedef enum
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_AND,
	NODE_OR,
}					t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	char			**value;
	int				*value_quoted;
	char			*file;
	int				file_quoted;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	**env_tab;
	t_env	*env;
	t_env	*exp;
	char	*input;
	t_token	*tokens;
	t_token *tokens_copy;
	t_ast	*root;
	int		fd_in;
	int		fd_out;
	int		cmd_count;
	bool	pipe;
	int		**pipes;
	pid_t	*pids;
}	t_shell;

#endif