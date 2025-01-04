/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:12:28 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:12:30 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	casenext(t_tokens **tmp)
{
	if ((*tmp)->error == 1)
	{
		(*tmp) = getnextcommand((*tmp));
		if (*tmp)
			(*tmp) = (*tmp)->next;
		return (1);
	}
	return (0);
}

void	checkpipeerr(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->cmdchain;
	while (tmp)
	{
		if (casenext(&tmp))
			continue ;
		if (tmp->id == TOKEN_PIPE && checkpipe(tmp))
			handleerrpipe(data, &tmp, &tmp);
		tmp = tmp->next;
	}
}
