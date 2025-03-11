/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:59:58 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/03 17:18:58 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* pour compter le nombre de pipes de chaque segment de la ligne de commande
	entre operateur && ou || et fin/debut de la commande */

void	get_segment_info(t_ast *ast, t_shell *shell)
{
	t_ast	*current;

	current = ast;
	shell->nbpipes = 0;
	while (current && current->type != NODE_AND && current->type != NODE_OR)
	{
		if (current->type == NODE_PIPE)
			shell->nbpipes++;
		current = current->right;
	}
	shell->nbproc = shell->nbpipes + 1;
	shell->pids = malloc(sizeof(pid_t) * shell->nbproc);
	if (shell->nbpipes)
		shell->pipes = malloc(sizeof(int[2]) * shell->nbpipes);
}

/* void	get_cmd_info(t_ast *ast, t_shell *shell) */