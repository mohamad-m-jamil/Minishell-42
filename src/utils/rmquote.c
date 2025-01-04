/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:14:50 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:14:53 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(t_tokens *tokens)
{
	char	*src;
	char	*dst;
	char	quote;

	while (tokens)
	{
		quote = 0;
		src = tokens->content;
		dst = tokens->content;
		while (*src)
		{
			if (!quote && (*src == '\'' || *src == '\"'))
				quote = *src;
			else if (quote && *src == quote)
				quote = 0;
			else
			{
				*dst = *src;
				dst++;
			}
			src++;
		}
		*dst = '\0';
		tokens = tokens->next;
	}
}
