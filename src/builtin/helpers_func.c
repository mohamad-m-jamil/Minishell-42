/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:26:46 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/25 15:26:46 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//check_empty_input
int	is_input_null(char **input)
{
	return (input[1] == NULL);
}

//check_invalid_key
int	is_key_invalid(char *key)
{
	if (check_key(key) == 0)
	{
		printf("Invalid key: %s\n", key);
		return (1);
	}
	return (0);
}

//cleanup_resources
void	free_resources(char *key, char *value)
{
	free(value);
	free(key);
}

//free_argument_list
void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
