/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:18:27 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/25 16:18:27 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//swap_env_nodes
// void	swap_nodes(t_env *a, t_env *b)
// {
// 	char	*temp_key;
// 	char	*temp_value;
// 	int		temphidden;

// 	temp_key = a->key;
// 	temp_value = a->value;
// 	temphidden = a->hidden;
// 	a->hidden = b->hidden;
// 	a->key = b->key;
// 	a->value = b->value;
// 	b->hidden = temphidden;
// 	b->key = temp_key;
// 	b->value = temp_value;
// }

//sort_environment_variables
// void	sort_env_list(t_env *head)
// {
// 	int		swapped;
// 	t_env	*ptr1;
// 	t_env	*lptr;

// 	lptr = NULL;
// 	if (head == NULL)
// 		return ;
// 	swapped = 1;
// 	while (swapped)
// 	{
// 		swapped = 0;
// 		ptr1 = head;
// 		while (ptr1->next != lptr)
// 		{
// 			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
// 			{
// 				swap_nodes(ptr1, ptr1->next);
// 				swapped = 1;
// 			}
// 			ptr1 = ptr1->next;
// 		}
// 		lptr = ptr1;
// 	}
// }

//strip_quotes
// void	remove_quotes_from_str(char *str)
// {
// 	char	*src;
// 	char	*dst;
// 	char	quote;

// 	quote = 0;
// 	src = str;
// 	dst = str;
// 	while (*src)
// 	{
// 		if (!quote && (*src == '\'' || *src == '\"'))
// 			quote = *src;
// 		else if (quote && *src == quote)
// 			quote = 0;
// 		else
// 		{
// 			*dst = *src;
// 			dst++;
// 		}
// 		src++;
// 	}
// 	*dst = '\0';
// 	free(src);
// 	free(dst);
// }

//is_valid_key
int	check_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		return (0);
	}
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

// Function to count environment variables and create an array of pointers
t_env	**count_env(t_env *env_list, int *count)
{
	t_env	**array;
	t_env	*current;
	int		i;

	*count = 0;
	current = env_list;
	while (current)
	{
		(*count)++;
		current = current->next;
	}
	array = (t_env **)malloc(sizeof(t_env *) * (*count));
	if (!array)
		return (NULL);
	current = env_list;
	i = 0;
	while (i < *count)
	{
		array[i] = current;
		current = current->next;
		i++;
	}
	return (array);
}

// Function to sort the array of environment variables
void	sort_env_array(t_env **sorted_array, int count)
{
	t_env	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted_array[j]->key, sorted_array[j + 1]->key) > 0)
			{
				temp = sorted_array[j];
				sorted_array[j] = sorted_array[j + 1];
				sorted_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// Function to print the environment variables in the required format
void	print_env_array(t_env **sorted_array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(sorted_array[i]->key, STDOUT_FILENO);
		if (sorted_array[i]->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(sorted_array[i]->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putendl_fd("", STDOUT_FILENO);
		i++;
	}
}

// Main function to handle sorting and printing
void	print_sorted_env_list(t_env *env_list)
{
	int		count;
	t_env	**sorted_array;

	sorted_array = count_env(env_list, &count);
	if (!sorted_array)
		return ;
	sort_env_array(sorted_array, count);
	print_env_array(sorted_array, count);
	free(sorted_array);
}
