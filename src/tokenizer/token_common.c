/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:27:05 by oabdelka          #+#    #+#             */
/*   Updated: 2025/01/04 14:14:20 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tk_bufpos(char *input, t_tk *tk, t_data *data)
{
	if (tk->buf_i > 0)
	{
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
	(void)input;//(unused parameter)
}

void	tk_bufposo(char *input, t_tk *tk, t_data *data)
{
	if (tk->buf_i > 0)
	{
		tk->buffer[tk->buf_i] = '\0';
		if (!tk->foundcmd)
		{
			append(&data->cmdchain, tk->buffer, TOKEN_COMMAND);
			tk->foundcmd = 1;
		}
		else
			append(&data->cmdchain, tk->buffer, TOKEN_WORD);
	}
	(void)input;
}

void	tk_default(char *input, t_tk *tk, t_data *data)
{
	if (tk->last_was_space)
	{
		tk->buffer[0] = input[tk->i];
		tk->buffer[1] = '\0';
		append(&data->cmdchain, tk->buffer, get_delimiter_type(tk->buffer));
	}
	else
	{
		tk->buffer[tk->buf_i++] = input[tk->i];
	}
	tk->last_was_space = (input[tk->i] == ' ');
}
t_token	get_delimiter_type(char *str)
{
	if (ft_strcmp(str, " ") == 0)
		return (TOKEN_SPACE);
	else if (ft_strcmp(str, "<<") == 0)
		return (TOKEN_HEREDOC_EOF);
	else if (ft_strcmp(str, ">>") == 0)
		return (TOKEN_OUT_A_FILE);
	else if (ft_strcmp(str, "<") == 0)
		return (TOKEN_IN_FILE);
	else if (ft_strcmp(str, ">") == 0)
		return (TOKEN_OUT_FILE);
	else if (ft_strcmp(str, "|") == 0)
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}
