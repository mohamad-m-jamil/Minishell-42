/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:26:51 by oabdelka          #+#    #+#             */
/*   Updated: 2025/01/04 14:14:28 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tk_quote(char *input, t_tk *tk, t_data *data)
{
	tk->buffer[tk->buf_i++] = input[tk->i];
	if (input[tk->i] == tk->quote)
	{
		tk->quote = 0;
		tk->buffer[tk->buf_i] = '\0';
		if (!tk->foundcmd)
		{
			append(&data->cmdchain, tk->buffer, TOKEN_COMMAND);
			tk->foundcmd = 1;
		}
		else
			append(&data->cmdchain, tk->buffer, TOKEN_WORD);
		tk->buf_i = 0;
	}
	tk->last_was_space = 0;
}

void	tk_isquote(char *input, t_tk *tk, t_data *data)
//not already inside quotes
{
	if (tk->buf_i > 0)
	{
		tk->buffer[tk->buf_i] = '\0';
		if (!tk->foundcmd && data->cmdchain
			&& data->cmdchain->previous->id != TOKEN_START
			&& data->cmdchain->previous->id != TOKEN_COMMAND)
		{
			append(&data->cmdchain, tk->buffer, TOKEN_COMMAND);
			tk->foundcmd = 1;
		}
		else
			append(&data->cmdchain, tk->buffer, TOKEN_WORD);
		tk->buf_i = 0;
	}
	tk->quote = input[tk->i];
	tk->buffer[tk->buf_i++] = input[tk->i];
	tk->last_was_space = 0;
}
