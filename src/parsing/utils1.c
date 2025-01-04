/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:13:46 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:13:48 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*bte5od char w bta3mel create la arg node that will be appended to the args list in the cmd node*/
t_arg	*create_arg_node(char *arg)
{
	t_arg	*new_arg;

	new_arg = (t_arg *)malloc(sizeof(t_arg));
	if (!new_arg)
		return (NULL);
	new_arg->arg = ft_strdup(arg);
	new_arg->next = NULL;
	return (new_arg);
}
/*take a command and a arg node and append the arg node to the arg list in the command*/
void	add_argument(t_command *cmd, char *arg)
{
	t_arg	*new_arg;
	t_arg	*temp;

	if (!cmd || !arg)
		return ;
	new_arg = create_arg_node(arg);
	if (!cmd->args)
	{
		cmd->args = new_arg;
	}
	else
	{
		temp = cmd->args;
		while (temp->next)
			temp = temp->next;
		temp->next = new_arg;
	}
}
/*when we encounter a command or a node we creade a command node that's null inorder to fill it later with the handle word command*/
t_command	*create_command_node(void)
{
	t_command	*new_cmd;

	new_cmd = (t_command *)malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->infile = STDIN_FILENO;
	new_cmd->outfile = STDOUT_FILENO;
	new_cmd->next = NULL;
	new_cmd->error = 0;
	return (new_cmd);
}
/*append the command node to the command list, this is done while parsing the tokens list*/
void	append_command_node(t_command **cmd_list, t_command *new_cmd)
{
	t_command	*temp;

	if (!cmd_list || !new_cmd)
		return ;
	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
	}
	else
	{
		temp = *cmd_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
	}
}
/*see if the command is valid*/
int	hasaccess(t_tokens *token, t_data *data)
{
	if (!ft_strcmp(token->content, "/"))
		return (1);
	if (!ft_strcmp(token->content, "."))
		return (1);
	if (access(get_path(token->content, data->env_list), X_OK))
		return (1);
	printf("bash: %s: commandsda not found\n", token->content);
	data->cmd.status = 127;
	return (0);
}
