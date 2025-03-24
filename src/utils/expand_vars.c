/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:43:24 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/20 11:08:50 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*expand_exit_status(char *result, int *i)
{
	char	*exit_status;

	exit_status = ft_itoa(g_last_exit_code);
	if (!exit_status)
		return (NULL);
	result = ft_strjoin_free(result, exit_status);
	free(exit_status);
	(*i)++;
	return (result);
}

static char	*expand_env_var(t_shell *shell, char *word, char *result, int *i)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i;
	while (ft_isalnum(word[*i]) || word[*i] == '_')
		(*i)++;
	var_name = ft_substr(word, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = ft_getenv(shell, var_name);
	if (var_value)
		result = ft_strjoin_free(result, var_value);
	return (result);
}

/* cas $12334 a gerer? */

static char	*expand_variable(char *word, t_shell *shell)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	if (!result)
		perror_exit("malloc", shell);
	while (word[i])
	{
		if (word[i] == '$')
		{
			i++;
			if (word[i] == '?')
				result = expand_exit_status(result, &i);
			else if (ft_isalpha(word[i]) || word[i] == '_')
				result = expand_env_var(shell, word, result, &i);
			else
				result = ft_strjoin_char(result, '$');
		}
		else
			result = ft_strjoin_char(result, word[i++]);
	}
	return (free(word), result);
}

void	expand_node(t_ast *node, t_shell *shell)
{
	int	i;
	int	i_dollar;

	i = 0;
	if (node->type == NODE_COMMAND)
	{
		while (node->value[i])
		{
			i_dollar = find_char(node->value[i], '$');
			if (i_dollar != -1 && node->value_quoted[i] == 0)
				node->value[i] = expand_variable(node->value[i], shell);
			i++;
		}
	}
	else if (node->type >= NODE_REDIR_OUT && node->type <= NODE_HEREDOC)
	{
		i_dollar = find_char(node->file, '$');
		if (i_dollar != -1 && node->file_quoted == 0)
			node->file = expand_variable(node->file, shell);
	}
}
