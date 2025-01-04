/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:38:36 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/25 16:38:36 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//convert_args_to_array
char	**argtochar(t_arg *arg)
{
	t_arg	*tmp;
	char	**args;
	int		i;

	i = 0;
	tmp = arg;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	args = (char **)malloc((i + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	tmp = arg;
	i = 0;
	while (tmp != NULL)
	{
		args[i] = ft_strdup(tmp->arg);
		printf("args[i]:%s\n", args[i]);
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (free_list_arg(tmp), args);
}

//count_arguments
int	getac(t_arg *arg)
{
	t_arg	*tmp;
	int		i;

	tmp = arg;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	free_list_arg(tmp);
	return (i);
}

//validate_export_arg
int	is_valid_export_argument(char *arg)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	split_envp(arg, &key, &value);
	if (!key || ft_strlen(key) == 0 || is_key_invalid(key))
	{
		free_resources(key, value);
		return (0);
	}
	free_resources(key, value);
	return (1);
}

//add_or_update_env_variable
int	set_export_variable(t_env **env_list, char *arg)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	split_envp(arg, &key, &value);
	if (!key || ft_strlen(key) == 0 || is_key_invalid(key))
		return (free_resources(key, value), -1);
	if (value == NULL)
	{
		if (set_env(env_list, key, NULL, 1) != 0)
			return (free_resources(key, value), -1);
	}
	else
	{
		if (set_env(env_list, key, value, 0) != 0)
			return (free_resources(key, value), -1);
	}
	free_resources(key, value);
	return (0);
}

//handle_export_command
int	export_command(t_env **env_list, t_arg *arg)
{
	t_arg	*tmparg;
	int		status;

	status = 0;
	tmparg = arg->next;
	if (tmparg == NULL)
	{
		print_sorted_env_list(*env_list);
		return (status);
	}
	while (tmparg)
	{
		if (!is_valid_export_argument(tmparg->arg))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(tmparg->arg, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = 1;
		}
		else if (set_export_variable(env_list, tmparg->arg) != 0)
			status = 1;
		tmparg = tmparg->next;
	}
	return (status);
}
