/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:52:29 by md-harco          #+#    #+#             */
/*   Updated: 2025/03/21 18:39:41 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	len_without_quotes(char *s, int in_dquotes, int in_squotes)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '"' && !in_squotes)
			in_dquotes = !in_dquotes;
		else if (s[i] == '\'' && !in_dquotes)
			in_squotes = !in_squotes;
		else
			len++;
		i++;
	}
	return (len);
}

static void	get_new_word(char *new, char *s, int in_dquotes, int in_squotes)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (in_squotes)
			ft_printf("s[i] = %c on est entre single quotes\n", s[i]);
		if (in_dquotes)
			ft_printf("s[i] = %c on est entre double quotes\n", s[i]);
		if (s[i] == '"' && !in_squotes)
			in_dquotes = !in_dquotes;
		else if (s[i] == '\'' && !in_dquotes)
			in_squotes = !in_squotes;
		else
			new[j++] = s[i];
		i++;
	}
	new[j] = '\0';
}

char	*ft_rm_quotes(char *s)
{
	char	*new;
	int		len;
	int		in_dquotes;
	int		in_squotes;

	in_dquotes = 0;
	in_squotes = 0;
	len = len_without_quotes(s, in_dquotes, in_squotes);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	get_new_word(new, s, in_dquotes, in_squotes);
	return (free(s), new);
}
