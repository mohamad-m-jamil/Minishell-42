/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:26:27 by oabdelka          #+#    #+#             */
/*   Updated: 2024/12/25 16:26:29 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenizer(char *input, t_data *data)
{
	t_tk	tk;

	inittk(input, &tk, data);
	while (input[tk.i] != '\0')
	{
		if (tk.quote)
			tk_quote(input, &tk, data);
		else if (input[tk.i] == '\'' || input[tk.i] == '\"')
			tk_isquote(input, &tk, data);
		else if (ft_strchr("|<> ", input[tk.i]))
			tk_redir(input, &tk, data);
		else
			tk_default(input, &tk, data);
		if (input[tk.i] == '|')
			tk.foundcmd = 0;
		tk.i++;
	}
	tk_bufposo(input, &tk, data);
	free(tk.buffer);
	free(input);
}
