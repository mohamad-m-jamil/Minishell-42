/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:26:45 by oabdelka          #+#    #+#             */
/*   Updated: 2024/12/25 16:26:47 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tk_heredocument(char *input, t_tk *tk, t_data *data)
{
	if (input[tk->i] == '<' && input[tk->i + 1] == '<')
	{
		append(&data->cmdchain, "<<", TOKEN_HEREDOC_EOF);
		tk->i++;
		tk->last_was_space = 0;
		return (1);
	}
	return (0);
}
int	tk_outappend(char *input, t_tk *tk, t_data *data)
{
	if (input[tk->i] == '>' && input[tk->i + 1] == '>')
	{
		append(&data->cmdchain, ">>", TOKEN_OUT_A_FILE);
		tk->i++;
		tk->last_was_space = 0;
		return (1);
	}
	return (0);
}

void	tk_appendfo(char *input, t_tk *tk, t_data *data)
{
	append(&data->cmdchain, ">", TOKEN_OUT_FILE);
	tk->last_was_space = 0;
	(void)input;
}

void	tk_appendfin(char *input, t_tk *tk, t_data *data)
{
	append(&data->cmdchain, "<", TOKEN_IN_FILE);
	tk->last_was_space = 0;
	(void)input;
}

void	tk_redir(char *input, t_tk *tk, t_data *data)
{
	tk_bufpos(input, tk, data);
	if (tk_heredocument(input, tk, data))
		;
	else if (tk_outappend(input, tk, data))
		;
	else if (input[tk->i] == '>')
		tk_appendfo(input, tk, data);
	else if (input[tk->i] == '<')
		tk_appendfin(input, tk, data);
	else if (input[tk->i] == '|')
	{
		append(&data->cmdchain, "|", TOKEN_PIPE);
		tk->last_was_space = 0;
	}
	else if (input[tk->i] == ' ')
	{
		append(&data->cmdchain, " ", TOKEN_SPACE);
		tk->last_was_space = 0;
	}
}