/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:13:51 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:13:55 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokens	*nexttoken(t_tokens *tokens)
{
	while (tokens != NULL && tokens->id != TOKEN_PIPE)
		tokens = tokens->next;
	return (tokens);
}

t_tokens	*getnextspace(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	if (token == NULL)
		return (NULL);
	while (tmp && tmp->id == TOKEN_SPACE)
		tmp = tmp->next;
	return (tmp);
}
/*men3ayyetla lamma l token tkon word or command, eza l command null bta3ml creat la command node,
else bta3ml append lal content te3 l token bl list of agrs te3 l command using add_argument()*/
void	handle_word_command_token(t_tokens *tmp, t_command **current_cmd)
{
	if (!(*current_cmd))
	{
		*current_cmd = create_command_node();
		if (!(*current_cmd))
			return ;
	}
	add_argument(*current_cmd, tmp->content);
}

void	handle_pipe_token(t_command **cmd_list, t_command **current_cmd)
{
	if (*current_cmd)
	{
		append_command_node(cmd_list, *current_cmd);
		*current_cmd = NULL;
	}
}

t_tokens	*handle_in_file_token(t_tokens *tmp, t_command *current_cmd)
{
	tmp = tmp->next;
	if (tmp && tmp->id == TOKEN_SPACE)
		tmp = tmp->next;
	if (tmp && (tmp->id == TOKEN_WORD || tmp->id == TOKEN_COMMAND)
		&& current_cmd && !current_cmd->error)
	{
		current_cmd->infile = open(tmp->content, O_RDONLY);
	}
	return (nexttoken(tmp));
}
