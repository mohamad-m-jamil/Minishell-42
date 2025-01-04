/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:11:28 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:19:01 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_env(t_env **head, const char *key, const char *value, int hidden)
{
	t_env	*current;
	t_env	*prev;
	t_env	*new_node;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0
			&& ft_strlen(current->key) == ft_strlen(key))
		{
			free(current->value);
			current->value = NULL;
			if (value != NULL)
				current->value = ft_strdup(value);
			current->hidden = hidden;
			return (0);
		}
		prev = current;
		current = current->next;
	}
	new_node = create_envp_node((char *)key, (char *)value, hidden);
	if (!new_node)
		return (-1);
	prev->next = new_node;
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_list(t_env *head)
{
	t_env	*current;

	while (head)
	{
		current = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = current;
	}
}

void	print_list(t_env *env_head)
{
	t_env	*current_env;
	char	*current_value;

	current_env = env_head;
	while (current_env)
	{
		printf("Key: %s\n", current_env->key);
		current_value = current_env->value;
		printf("Values: ");
		printf("%s", current_value);
		printf("\n\n");
		current_env = current_env->next;
	}
}
