/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:13:25 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:13:25 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handleheredoc(t_data *data, t_tokens *token)
{
	t_hd	hd;

	signal(SIGINT, interactivehandle_sigint);
	signal(SIGQUIT, interactivehandle_sigquit);
	hd.tmp = token;
	hd.i = 0;
	while (hd.tmp && hd.tmp->id != TOKEN_PIPE)
	{
		if (hd.tmp->id == TOKEN_HEREDOC_EOF && hd.tmp->error == 0)
		{
			inheredoc(&hd);
			if (hd.tmp && (hd.tmp->id == TOKEN_FILE) && hd.tmp->error == 0)
				infile(&hd);
			else
				break ;
			writefile(&hd, data);
		}
		hd.i++;
		if (hd.tmp && hd.tmp->id == TOKEN_PIPE)
			break ;
		if (hd.tmp)
			hd.tmp = hd.tmp->next;
	}
	signal(SIGINT, noninteractivehandle_sigint);
	signal(SIGQUIT, noninteractivehandle_sigquit);
}

int	checkheredocerror(t_data *data)
{
	t_tokens	*tmp;
	int			haserrored;

	haserrored = 0;
	tmp = data->cmdchain;
	while (tmp)
	{
		if (tmp->id == TOKEN_HEREDOC_EOF && checkheredoc(tmp))
		{
			data->cmd.status = 2;
			printerror(tmp);
			tmp->error = 1;
			tmp = getnextcommand(tmp);
			haserrored = 1;
			continue ;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (haserrored);
}

int	haserror(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	while (tmp && tmp->id != TOKEN_PIPE)
	{
		if (tmp->error == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	parseheredoc(t_data *data)
{
	t_tokens	*tmp;

	tmp = data->cmdchain;
	if (checkheredocerror(data))
	{
		while (tmp)
		{
			tmp->error = 1;
			tmp = tmp->next;
		}
		return ;
	}
	while (tmp && tmp->id != TOKEN_PIPE)
	{
		if (tmp)
			handleheredoc(data, tmp);
		if (tmp)
			while (tmp && tmp->id != TOKEN_PIPE)
				tmp = tmp->next;
		if (tmp && tmp->id == TOKEN_PIPE)
			tmp = tmp->next;
	}
}

void	initcmd(char *input, char **env, t_data *data)
{
	t_command	*command;

	if (ft_strlen(input) == 0)
		return ;
	tokenizer(input, data);
	fixuptoken(data);
	parseheredoc(data);
	concatenvtoken(data);
	remove_quotes(data->cmdchain);
	checksyntaxerror(data);
	command = getcommands(data);
	handleredirects(data, command);
	execute_pipeline(command, data);
	free_command_list(command);
	free_cmdchain(data->cmdchain);
	if (data->cmd.status > 255)
		data->cmd.status = data->cmd.status % 255;
	(void)env;
	(void)command;
	(void)data;
}
