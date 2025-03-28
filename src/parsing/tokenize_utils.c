/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:20:23 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/24 01:08:41 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*create_token(t_token_type type, char *value, int is_quoted)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->is_quoted = is_quoted;
	new_token->next = NULL;
	return (new_token);
}

t_token	*add_token(t_token **head, t_token_type type, char *value,
		int is_quoted)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = NULL;
	new_token = create_token(type, value, is_quoted);
	if (!new_token)
		return (NULL);
	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	return (new_token);
}

/* A SUPPRIMER */

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: %-10s | Type: %d | is_quoted: %i\n", tokens->value,
			tokens->type, tokens->is_quoted);
		tokens = tokens->next;
	}
}

int	is_operator(char *word)
{
    if (!word)
        return (0);
    if (ft_strcmp(word, "<") == 0 ||
        ft_strcmp(word, "<<") == 0 ||
        ft_strcmp(word, ">") == 0 ||
        ft_strcmp(word, ">>") == 0 ||
        ft_strcmp(word, "|") == 0 ||
        ft_strcmp(word, "||") == 0 ||
        ft_strcmp(word, "&&") == 0)
        return (1);
    return (0);
}
