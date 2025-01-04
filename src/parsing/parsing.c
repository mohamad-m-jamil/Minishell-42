/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksayour <ksayour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:05:11 by zmourtab          #+#    #+#             */
/*   Updated: 2024/12/26 11:59:26 by ksayour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*helper function that will take the token "> or >>" and create the outfile and store it in the current command node attrs,
the int append is a flag to distinguish btw > or >>*/
t_tokens	*handle_out_file_token(t_tokens *tmp, t_command *current_cmd,
			int append)
{
	tmp = tmp->next;
	if (tmp->id == TOKEN_SPACE)
		tmp = tmp->next;
	if (tmp && (tmp->id == TOKEN_WORD || tmp->id == TOKEN_COMMAND)
		&& current_cmd && !current_cmd->error)
	{
		if (append)
		{
			current_cmd->outfile = open(tmp->content,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
		{
			current_cmd->outfile = open(tmp->content,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		current_cmd->append = append;
	}
	return (nexttoken(tmp));
}
/*ba3ml initialize lal command list bl awwal w btkoun null, ba3den kl ma le2i word aw command token
ba3ml append lal command 3al list w b3abbiyya lal command atrr (args)*/
t_command	*initialize_command_list(t_tokens *tokens)
{
	t_command	*current_cmd;

	current_cmd = NULL;
	if (tokens && (tokens->id == TOKEN_WORD || tokens->id == TOKEN_COMMAND))
		handle_word_command_token(tokens, &current_cmd);
	return (current_cmd);
}
/*process the entire tokens list, whenever it encounters one of the tokes it apply the specified helper funtion
if it's word or command it makes a new command node, if it's file it handels it, if pipe it append cmd to list and create a new command = to null*/
void	process_token(t_tokens **tmp, t_command **cmd_list,
		t_command **current_cmd)
{
	if ((*tmp)->error == 1 && *current_cmd)
		(*current_cmd)->error = 1;
	if ((*tmp)->id == TOKEN_WORD || (*tmp)->id == TOKEN_COMMAND)
		handle_word_command_token(*tmp, current_cmd);
	else if ((*tmp)->id == TOKEN_PIPE)
		handle_pipe_token(cmd_list, current_cmd);
	else if ((*tmp)->id == TOKEN_IN_FILE)
		*tmp = handle_in_file_token(*tmp, *current_cmd);
	else if ((*tmp)->id == TOKEN_OUT_FILE)
		*tmp = handle_out_file_token(*tmp, *current_cmd, 0);
	else if ((*tmp)->id == TOKEN_OUT_A_FILE)
		*tmp = handle_out_file_token(*tmp, *current_cmd, 1);
	if (*tmp != NULL)
		*tmp = (*tmp)->next;
}
/*loop through the tokens list and apply the process_token() for each token*/
void	process_tokens_loop(t_tokens *tokens, t_command **cmd_list,
		t_command **current_cmd)
{
	t_tokens	*tmp;

	tmp = tokens->next;
	while (tmp)
	{
		process_token(&tmp, cmd_list, current_cmd);
	}
}
/*main parsing function, takes the tokens list lli n3amlt bl tokenizer, and creates the command list
shouf l attrb te3on l command bl header file...
*/
t_command	*parse_tokens(t_tokens *tokens)
{
	t_command	*cmd_list;
	t_command	*current_cmd;

	cmd_list = NULL;
	current_cmd = initialize_command_list(tokens);
	process_tokens_loop(tokens, &cmd_list, &current_cmd);
	if (current_cmd)
		append_command_node(&cmd_list, current_cmd);
	free_command_list(current_cmd);
	return (cmd_list);
}
