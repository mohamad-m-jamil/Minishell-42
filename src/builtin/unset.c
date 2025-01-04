/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:43:37 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/25 15:43:37 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_env_var_to_unset(t_env **env, const char *key, t_env **previous)
{
	t_env	*current;

	current = *env;
	*previous = NULL;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (current);
		*previous = current;
		current = current->next;
	}
	return (NULL);
}

void	remove_env_var(t_env **env_list, t_env *current, t_env *previous)
{
	if (previous == NULL)
		*env_list = current->next;
	else
		previous->next = current->next;
	free(current->key);
	free(current->value);
	free(current);
}

int	unset_key_in_list(t_env **env_list, const char *key)
{
	t_env	*previous;
	t_env	*current;

	current = find_env_var_to_unset(env_list, key, &previous);
	if (current == NULL)
	{
		printf("unset: %s: no such variable\n", key);
		return (1);
	}
	remove_env_var(env_list, current, previous);
	return (0);
}

int	unset_command(t_arg *args, t_env **env_list)
{
	t_arg	*current;

	current = args->next;
	if (current == NULL)
	{
		perror("unset: not enough arguments\n");
		return (0);
	}
	if (!check_key(current->arg))
		return (is_key_invalid(current->arg));
	while (current != NULL)
	{
		unset_key_in_list(env_list, current->arg);
		current = current->next;
	}
	free_list_arg(current);
	return (0);
}
