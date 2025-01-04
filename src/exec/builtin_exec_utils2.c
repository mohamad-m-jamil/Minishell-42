/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:12:41 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:19:38 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec3(t_command *command, t_data *data)
{
	if (!ft_strcmp(command->args->arg, "env"))
		return (execenv(command, data));
	if (!ft_strcmp(command->args->arg, "pwd"))
		return (execpwd(command, data));
	return (-1);
}

int	exec4(t_command *command, t_data *data)
{
	if (!ft_strcmp(command->args->arg, "echo"))
		return (exececho(command, data));
	if (!ft_strcmp(command->args->arg, "exit"))
		return (execexit(command, data));
	return (-1);
}

int	execute_builtin_command(t_command *command, t_data *data)
{
	int	returnstatus;

	returnstatus = -1;
	if (ft_strlen(command->args->arg) == 2)
		returnstatus = (execcd(command, data));
	if (ft_strlen(command->args->arg) == 3)
		returnstatus = (exec3(command, data));
	if (ft_strlen(command->args->arg) == 4)
		returnstatus = (exec4(command, data));
	if (ft_strlen(command->args->arg) == 5)
		returnstatus = (execunset(command, data));
	if (ft_strlen(command->args->arg) == 6)
		returnstatus = (execexport(command, data));
	return (returnstatus);
}

void	dupexecnofork(t_command *command)
{
	if (command->outfile != -1)
		dup2(command->outfile, STDOUT_FILENO);
	if (command->infile != -1)
		dup2(command->infile, STDIN_FILENO);
}

void	ex1(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		exit(1);
	}
}
