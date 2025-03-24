/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:05:30 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/21 12:23:03 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execute_ast(t_ast *node, t_shell *shell)
{
	if (!node)
		return (g_last_exit_code);
	expand_node(node, shell);
	if (node->type == NODE_COMMAND)
	{
		if (shell->pipe == true)
			return (execute_command(node, shell));
		else
			return (execute_single_command(node, shell));
	}
	else if (node->type == NODE_PIPE)
		return (execute_pipe(node, shell));
	else if (node->type >= NODE_REDIR_IN && node->type <= NODE_HEREDOC)
		return (handle_redir_node(node, shell));
	else if (node->type == NODE_AND)
	{
		if (execute_ast(node->left, shell) == 0)
			return (reset_fd(shell), execute_ast(node->right, shell));
	}
	else if (node->type == NODE_OR)
	{
		if (execute_ast(node->left, shell) != 0)
			return (reset_fd(shell), execute_ast(node->right, shell));
	}
	return (g_last_exit_code);
}
