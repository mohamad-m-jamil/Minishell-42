/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:13:40 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/25 13:13:40 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//check_n_option
bool	is_valid_n_flag(const char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

//echo_print
//echo_output
int	echo_command(t_arg *args)
{
	int		newline;
	t_arg	*current;

	newline = 1;
	current = args->next;
	while (current != NULL && is_valid_n_flag(current->arg))
	{
		newline = 0;
		current = current->next;
	}
	while (current)
	{
		if (current->arg == NULL)
		{
			perror("Error: Null argument encountered.\n");
			return (1);
		}
		printf("%s", current->arg);
		if (current->next)
			printf(" ");
		current = current->next;
	}
	if (newline)
		printf("\n");
	return (free_list_arg(current), 0);
}
