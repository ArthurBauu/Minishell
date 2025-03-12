/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:00:06 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/12 00:32:51 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*expand_exit_status(char *result)
{
	char *exit_status;

	exit_status = ft_itoa(g_last_exit_code);
	if (!exit_status)
		return (NULL);
	result = ft_strjoin_free(result, exit_status);
	free(exit_status);
	return (result);
}

static char *expend_env_var(char *word, int *i, char *result)
{
	int start;
	char *var_name;
	char *var_value;

	start = *i;
	while (ft_isalnum(word[*i]) || word[*i] == '_')
		(*i)++;
	var_name = ft_substr(word, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = getenv(var_name);
	if (var_value)
	{
		result = ft_strjoin_free(result, var_value);
		if (!result)
			return (NULL);
	}
	free(var_name);
	return (result);
}

char *expand_variable(char *word)
{
	char *result;
	int i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (word[i])
	{
		if (word[i++] == '$')
		{
			if (word[i] == '?')
			{
				result = expand_exit_status(result);
				i++;
			}
			else if (ft_isalpha(word[i]) || word[i] == '_')
				result = expend_env_var(word, &i, result);
			else
				result = ft_strjoin_char(result, '$');
		}
		else 
			result = ft_strjoin_char(result, word[i++]);
	}
	return (result);
}
