/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:36:15 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/24 20:36:15 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//change_to_home_directory
int	cd_to_home(t_env *env_list)
{
	char	*home;
	char	*current_pwd;

	home = get_env(env_list, "HOME");
	current_pwd = get_env(env_list, "PWD");
	if (!home)
	{
		fprintf(stderr, "cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("cd: error changing to home directory");
		free(home);
		free(current_pwd);
		return (1);
	}
	set_env(&env_list, "OLDPWD", current_pwd, 0);
	set_env(&env_list, "PWD", home, 0);
	free(home);
	free(current_pwd);
	return (0);
}

//go_to_previous_directory
int	cd_to_oldpwd(t_env *env_list)
{
	char	*old_pwd;
	char	*current_pwd;
	char	*new_pwd;

	old_pwd = get_env(env_list, "OLDPWD");
	current_pwd = get_env(env_list, "PWD");
	if (old_pwd == NULL || chdir(old_pwd) != 0)
	{
		perror("cd: error changing to previous directory");
		return (1);
	}
	set_env(&env_list, "OLDPWD", current_pwd, 0);
	printf("%s\n", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("cd: error getting current directory");
		return (1);
	}
	set_env(&env_list, "PWD", new_pwd, 0);
	free(new_pwd);
	free(old_pwd);
	free(current_pwd);
	return (0);
}

//change_directory_to_path
int	cd_to_path(char *path, t_env *env_list)
{
	char	*current_pwd;
	char	*new_pwd;

	current_pwd = get_env(env_list, "PWD");
	if (chdir(path) != 0)
	{
		perror("cd: error changing directory");
		env_list->two_point += 1;
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("cd: error getting current directory");
		env_list->two_point += 1;
		return (1);
	}
	env_list->two_point = 0;
	set_env(&env_list, "OLDPWD", current_pwd, 0);
	set_env(&env_list, "PWD", new_pwd, 0);
	free(new_pwd);
	free(current_pwd);
	return (0);
}

//change_working_directory
int	change_dir(t_arg *args, t_env *env_list)
{
	t_arg	*current;

	current = args->next;
	if (current == NULL || current->arg[0] == '~')
	{
		return (cd_to_home(env_list));
	}
	if ((current->arg[0] == '-' && current->arg[1] == '\0')
		|| (current->arg[0] == '-' && current->arg[1] == '-'
			&& current->arg[2] == '\0'))
	{
		return (cd_to_oldpwd(env_list));
	}
	if (current->next == NULL)
	{
		return (cd_to_path(current->arg, env_list));
	}
	perror("cd: too many arguments\n");
	free_list_arg(current);
	return (1);
}

//free_argument_list
void	free_list_arg(t_arg *node)
{
	t_arg	*current_node;

	while (node != NULL)
	{
		current_node = node;
		node = node->next;
		free(current_node->arg);
		free(current_node);
	}
}
