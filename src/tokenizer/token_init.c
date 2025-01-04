/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:26:57 by oabdelka          #+#    #+#             */
/*   Updated: 2025/01/04 14:14:24 by mjamil           ###   ########.fr       */
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