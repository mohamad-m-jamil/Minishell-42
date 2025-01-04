/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:12:17 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:12:22 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokens	*getprev(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	while (tmp && tmp->id == TOKEN_SPACE)
		tmp = tmp->previous;
	return (tmp);
}

t_tokens	*getnext(t_tokens *token)
{
	if (token && token->next && token->next->id == TOKEN_SPACE)
		token = token->next;
	if (token && token->next)
		return (token->next);
	return (NULL);
}

int	checkpipe(t_tokens *token)
{
	if (!getnext(token->next) || (getnext(token->next)->id != TOKEN_WORD
			&& getnext(token->next)->id != TOKEN_COMMAND)
		|| !getprev(token->previous)
		|| (getprev(token->previous)->id != TOKEN_WORD
			&& getprev(token->previous)->id != TOKEN_COMMAND))
	{
		if (getprev(token->previous))
			getprev(token->previous)->error = 1;
		if (getnext(token->next))
			getnext(token->next)->error = 1;
		return (1);
	}
	return (0);
}

int	checkfileoutappend(t_tokens *token)
{
	if (!getnext(token->next) || getnext(token->next)->id != TOKEN_WORD)
		return (1);
	return (0);
}

int	checkheredoc(t_tokens *token)
{
	t_tokens	*next_token;

	next_token = getnext(token->next);
	if (!next_token || (next_token->id != TOKEN_FILE))
		return (1);
	return (0);
}
