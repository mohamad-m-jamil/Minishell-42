/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_variable_counter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:11:17 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:18:54 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_non_alpha_var(char *input, int i)
{
	if (input[i] == '$' && !ft_isalpha(input[i + 1]))
	{
		i++;
		while (input[i] != ' ' && input[i] != '\0' && input[i] != '\"')
			i++;
	}
	return (i);
}

static int	toggle_in_quote(char c, int inq)
{
	if (c == '"')
		return (!inq);
	return (inq);
}

static int	skip_single_quote_section(char *input, int i)
{
	if (input[i] == '\'')
	{
		i++;
		while (input[i] != '\'' && input[i] != '\0')
			i++;
		if (input[i] == '\'')
			i++;
	}
	return (i);
}

int	isquote(char c)
{
	return (c == '\'' || c == '\"');
}

int	dollarcount(char *input)
{
	int	i;
	int	count;
	int	inq;

	inq = 0;
	i = 0;
	count = 0;
	while (input[i] != '\0')
	{
		i = skip_non_alpha_var(input, i);
		if (input[i] == '$')
			count++;
		inq = toggle_in_quote(input[i], inq);
		i = skip_single_quote_section(input, i);
		i++;
	}
	return (count);
}
