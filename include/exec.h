/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:51:39 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/13 16:46:34 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "global.h"
# include "parsing.h"

/* utils */
void	free_strtab(char **strtab);
void	reset_shell(t_shell *shell);
void	initialize_shell(t_shell *shell, char **envp);
void	perror_exit(char *msg, t_shell *shell);
void	expand_node(t_ast *node, t_shell *shell);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	stop_sig(int sig);
int		find_char(char *str, char c);
int		count_char(char *str, char c, int n);

/* env tools */
t_env	*dup_env(char **envp, t_shell *shell);
bool	is_var(t_shell *shell, char *name);
void	update_var(t_shell *shell, char *name, char *value);
char	*ft_getenv(t_shell *shell, char *name);
t_env	*ft_env_new(char *name, char *value, t_shell *shell);
void	ft_env_add_back(t_env **env, t_env *new);
void	ft_sort_exp(t_env *exp);
void	print_env(t_env *exp);
void	print_exp(t_env *exp);
void	clear_env(t_env **env);

/* built-in commands */
int		ft_echo(char **args);
int		ft_cd(char **args, t_shell *shell);
int		ft_pwd(char **args);
int		ft_export(char **args, t_shell *shell);
int		ft_unset(char **args, t_shell *shell);
int		ft_env(char **args, t_shell *shell);
int		ft_exit(char **args, t_shell *shell);
int		is_builtin(char *cmd);
int		execute_builtin(char *cmd, char **args, t_shell *shell);

/* exec commands */
char	*get_path(char *cmd, char **envp);
int		execute_command(t_ast *ast, t_shell *shell);
int		execute_single_command(t_ast *node, t_shell *shell);

/* files utils */
int		check_infile(char *pathname, t_shell *shell);
int		check_outfile(char *pathname, t_shell *shell);
int		check_outfile_app(char *pathname, t_shell *shell);
void	change_fd_in(t_shell *shell, int fd);
void	change_fd_out(t_shell *shell, int fd);
void	dup_files(int fd_in, int fd_out);
void	save_std_fd(int *saved_stdin, int *saved_stdout, t_shell *shell);
void	restore_std_fd(int saved_stdin, int saved_stdout, t_shell *shell);

int		handle_redir_node(t_ast *node, t_shell *shell);
int		execute_pipe(t_ast *node, t_shell *shell);
int		execute_ast(t_ast *node, t_shell *shell);

#endif