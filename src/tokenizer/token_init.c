/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:26:57 by oabdelka          #+#    #+#             */
/*   Updated: 2024/12/25 16:26:59 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	inittk(char *input, t_tk *tk, t_data *data)
{
	tk->i = 0;
	tk->buf_i = 0;
	tk->quote = 0;
	tk->last_was_space = 0;
	tk->foundcmd = 0;
	data->cmdchain = NULL;
	tk->buffer = ft_calloc(ft_strlen(input) + 1, sizeof(char));
}