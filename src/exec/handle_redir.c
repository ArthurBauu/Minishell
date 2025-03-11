/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:55:57 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/11 13:47:38 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_heredoc(t_ast *node, t_shell *shell)
{
	int		heredoc_pipe[2];
	char	*line;
	char	*delim;

	if (pipe(heredoc_pipe) < 0)
		perror_exit("pipe", shell);
	delim = ft_strdup(node->file);
	delim = ft_strjoin_free(delim, "\n");
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strcmp(line, delim) == 0)
			break ;
		ft_putstr_fd(line, heredoc_pipe[1]);
		free(line);
	}
	close (heredoc_pipe[1]);
	change_fd_in(shell, heredoc_pipe[0]);
	if (line)
		free(line);
	if (delim)
		free(delim);
}

int	handle_redir_node(t_ast *node, t_shell *shell)
{
	if (node->type == NODE_HEREDOC)
		handle_heredoc(node, shell);
	else if (node->type == NODE_REDIR_IN)
		change_fd_in(shell, check_infile(node->file, shell));
	else if (node->type == NODE_REDIR_OUT)
		change_fd_out(shell, check_outfile(node->file, shell));
	else if (node->type == NODE_APPEND)
		change_fd_out(shell, check_outfile_app(node->file, shell));
	if (node->left)
		return (execute_ast(node->left, shell));
	else if (node->right)
		return (execute_ast(node->right, shell));
	return (EXIT_SUCCESS);
}
