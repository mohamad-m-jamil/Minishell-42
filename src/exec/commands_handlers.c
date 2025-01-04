/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:12:56 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:12:58 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	getcommandssecond(t_command **cmd_list, t_command **current_cmd,
		t_tokens **tmp)
{
	if ((*tmp)->id == TOKEN_WORD || (*tmp)->id == TOKEN_COMMAND)
	{
		if (!(*current_cmd))
		{
			*current_cmd = create_command_node();
			if (!*current_cmd)
				return ;
		}
		add_argument(*current_cmd, (*tmp)->content);
	}
	else if ((*tmp)->id == TOKEN_PIPE)
	{
		if (*current_cmd)
		{
			append_command_node(cmd_list, *current_cmd);
			*current_cmd = NULL;
		}
	}
}

t_command	*getcommands(t_data *data)
{
	t_command	*cmd_list;
	t_command	*current_cmd;
	t_tokens	*tmp;

	tmp = data->cmdchain;
	current_cmd = NULL;
	cmd_list = NULL;
	tmp = getcommandsfirst(&current_cmd, tmp);
	while (tmp)
	{
		getcommandssecond(&cmd_list, &current_cmd, &tmp);
		if (tmp && tmp->error == 1 && current_cmd)
			current_cmd->error = 1;
		if (tmp)
			tmp = tmp->next;
	}
	if (current_cmd)
		append_command_node(&cmd_list, current_cmd);
	return (cmd_list);
}

t_tokens	*handleinfile(t_data *data, t_command **current_cmd, t_tokens *tmp)
{
	tmp = tmp->next;
	if (tmp && tmp->id == TOKEN_SPACE)
		tmp = tmp->next;
	if (tmp && (tmp->id == TOKEN_FILE))
	{
		(*current_cmd)->infile = open(tmp->content, O_RDONLY);
		if ((*current_cmd)->infile == -1)
		{
			printf("bash: %s: Permission denied\n", tmp->content);
			(*current_cmd)->error = 1;
			data->cmd.status = 1;
			tmp = NULL;
		}
	}
	if (tmp)
		tmp = tmp->next;
	return (tmp);
}

t_tokens	*handleoutfile(t_data *data, t_command **current_cmd,
		t_tokens *tmp)
{
	tmp = tmp->next;
	if (tmp && tmp->id == TOKEN_SPACE)
		tmp = tmp->next;
	if (tmp && (tmp->id == TOKEN_FILE))
	{
		(*current_cmd)->outfile = open(tmp->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((*current_cmd)->outfile == -1)
		{
			printf("bash: %s: Permission denied\n", tmp->content);
			(*current_cmd)->error = 1;
			data->cmd.status = 1;
			tmp = NULL;
		}
	}
	if (tmp)
		tmp = tmp->next;
	return (tmp);
}

t_tokens	*handleoutafile(t_data *data, t_command **current_cmd,
		t_tokens *tmp)
{
	tmp = tmp->next;
	if (tmp && tmp->id == TOKEN_SPACE)
		tmp = tmp->next;
	if (tmp && (tmp->id == TOKEN_FILE))
	{
		(*current_cmd)->outfile = open(tmp->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((*current_cmd)->outfile == -1)
		{
			printf("bash: %s: Permission denied\n", tmp->content);
			data->cmd.status = 1;
			(*current_cmd)->error = 1;
			tmp = NULL;
		}
	}
	if (tmp)
		tmp = tmp->next;
	return (tmp);
}
