/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:20:23 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/10 15:51:30 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	return (new_token);
}

t_token	*add_token(t_token **head, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = NULL;
	new_token = create_token(type, value);
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
		printf("Token: %-10s | Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

int	is_operator(char *word)
{
	int	i;

	i = 0;
	while (valid_operator[i] != NULL)
	{
		if (strcmp(word, valid_operator[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}