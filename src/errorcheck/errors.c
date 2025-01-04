/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:12:01 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:35:00 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	contains_dot_or_slash(const char *str)
{
	while (*str)
	{
		if (*str == '.' || *str == '/')
		{
			return (1);
		}
		str++;
	}
	return (0);
}

void	printerrnocmd(t_tokens *token, t_data *data)
{
	data->cmd.status = 127;
	token->error = 1;
	printf("bash: %s: command not found\n", token->content);
}

void	printerrnodir(t_tokens *token, t_data *data)
{
	data->cmd.status = 126;
	token->error = 1;
	printf("bash: %s: is a directory\n", token->content);
}

void	printerrnofdir(t_tokens *token, t_data *data)
{
	data->cmd.status = 127;
	token->error = 1;
	printf("bash: %s: No such file or directory\n", token->content);
}
