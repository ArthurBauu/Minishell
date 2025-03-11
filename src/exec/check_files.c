/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:55:57 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/03 17:48:43 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_infile(char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		perror_exit(pathname);
	return (fd);
}

int	check_outfile(char *pathname)
{
	int	fd;

	if (access(pathname, F_OK) != 0)
		fd = open(pathname, O_CREAT | O_RDWR, 0644);
	else
		fd = open(pathname, O_RDWR);
	if (fd == -1)
		perror_exit(pathname);
	return (fd);
}

int check_outfile_app(char *pathname)
{
	int	fd;

	if (access(pathname, F_OK) != 0)
		fd = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(pathname, O_RDWR | O_APPEND);
	if (fd == -1)
		perror_exit(pathname);
	return (fd);
}

/* DANS TOUTE LA LIGNE, IL FAUT REGARDER SI IL Y A UN OU 
PLUSIEURS HEREDOC OU UN OU PLUSIEURS REDIR IN */
/* pour l instant je teste que s il y en a un au debut,
alors qu il faut faire un find */

int	identify_infile(int	i, t_ast *ast, t_shell *shell)
{
	t_ast	*current;

	current = ast;
	
	if (current->type == NODE_HEREDOC)
	{
		ft_printf("c'est un heredoc\n");
	}
	else if (current->type == NODE_REDIR_IN)
	{
		ft_printf("REDIR_IN et file =%s\n", current->file);
		return (close(shell->pipes[i][0]), check_infile(current->file));
	}
	else if (current->type == COMMAND && current->left && current->left->type == NODE_PIPE)
	{
		ft_printf("on lit depuis le pipe\n");
		return (shell->pipes[i][0]);
	}
	ft_printf("on lit depuis l'entree standard\n");
	return(STDIN_FILENO);
}

int	identify_outfile(int i, t_ast *ast, t_shell *shell)
{
	t_ast	*current;

	current = ast;
	if (current->type == NODE_APPEND)
	{
		ft_printf("REDIR_OUT et file =%s\n", current->file);
		return (close(shell->pipes[i][1]), check_outfile_app(current->file));
	}
	else if (current->type == NODE_REDIR_OUT)
	{
		ft_printf("REDIR_OUT et file =%s\n", current->file);
		return (close(shell->pipes[i][1]), check_outfile(current->file));
	}
	else if (current->type == COMMAND && current->right && current->right->type == NODE_PIPE)
	{
		ft_printf("on ecrit dans le prochain pipe\n");
		return (shell->pipes[i + 1][1]);
	}
	ft_printf("on ecrit dans la sortie standard\n");
	return (STDOUT_FILENO);
}
