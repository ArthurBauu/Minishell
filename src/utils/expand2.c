/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:38:27 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/22 12:43:07 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*ft_charjoin_free(char *s, char c)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(s);
	new = malloc(sizeof(char) * (len + 2));
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[len] = c;
	new[len + 1] = '\0';
	free(s);
	return (new);
}

static int	count_size_quotes(char *s, char quote_type)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != quote_type)
		i++;
	return (i);
}

static void	single_no_quotes(int *i, char **new, char *s)
{
	int		size_s;
	char	*temp;
	char	*result;

	(*i)++;
	size_s = count_size_quotes(s + *i, '\'');
	temp = ft_strndup(s + *i, size_s);
	if (!temp)
		return ;
	(*i) += size_s + 1;
	result = ft_strjoin_free(*new, temp);
	if (result)
		*new = result;
	free(temp);
}

static void	double_no_quotes(int *i, char **new, char *s, t_shell *shell)
{
	int		size_s;
	char	*temp;
	char	*result;

	(*i)++;
	size_s = count_size_quotes(s + *i, '"');
	temp = double_quotes(ft_strndup(s + *i, size_s), shell);
	if (!temp)
		return ;
	(*i) += size_s + 1;
	result = ft_strjoin_free(*new, temp);
	if (result)
		*new = result;
	free(temp);
}

char	*no_quotes(char *s, t_shell *shell)
{
	int		i;
	char	*new;
	char	*result;

	i = 0;
	new = ft_strdup("");
	if (!new)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'')
			single_no_quotes(&i, &new, s);
		else if (s[i] == '"')
			double_no_quotes(&i, &new, s, shell);
		else if (s[i] == '$')
			handle_dollar(&i, &new, s, shell);
		else
		{
			result = ft_charjoin_free(new, s[i++]);
			if (result)
				new = result;
		}
	}
	free(s);
	return (new);
}
