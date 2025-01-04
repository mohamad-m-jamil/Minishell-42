/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:49:33 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/25 13:49:33 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//print_environment_vars
int	env_command(t_env *env)
{
	t_env	*current_var;

	if (env == NULL)
	{
		perror("Error: The environment list is empty\n");
		return (1);
	}
	current_var = env;
	while (current_var != NULL)
	{
		if (current_var->hidden == 0)
			printf("%s=%s\n", current_var->key, current_var->value);
		current_var = current_var->next;
	}
	free_env_list(current_var);
	return (0);
}
