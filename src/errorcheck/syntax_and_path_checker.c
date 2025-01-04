/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_path_checker.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:12:07 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:34:32 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path(t_tokens *token, t_data *data)
{
    struct stat statbuf;
    char        *resolved;// Resolved path from get_path

    if (strcmp(token->content, "..") == 0)
    {
        printerrnocmd(token, data);
        return (1);
    }
    if (strcmp(token->content, ".") == 0)
    {
        printf("bash: .: filename argument required\n");
        data->cmd.status = 2;
        token->error = 1;
        return (1);
    }
    if (is_builtin_command(token->content))
        return (0);
    resolved = get_path(token->content, data->env_list);//$PATH
    if (resolved)
    {
        if (access(resolved, X_OK) == 0)//valid and executable
        {
			return (free(resolved), 0);
        }
        printerrnofdir(token, data);//No such file or directory
		return (free(resolved), 1);
    }
    if (stat(token->content, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
    {
        printerrnodir(token, data);//is a directory
        return (1);
    }
    printerrnocmd(token, data);//"command not found"
    return (1);
}

t_tokens	*getnextcommand(t_tokens *tmp)
{
	while (tmp && tmp->id != TOKEN_PIPE)
		tmp = tmp->next;
	return (tmp);
}

void	handleerr(t_data *data, t_tokens **tmp, t_tokens **tmpprint)
{
	data->cmd.status = 2;
	printf("%d\n", (*tmp)->error);
	printerror(*tmpprint);
	(*tmp)->error = 1;
	*tmp = getnextcommand(*tmp);
}

void	handleerrpipe(t_data *data, t_tokens **tmp, t_tokens **tmpprint)
{
	t_tokens	*tmptk;

	tmptk = data->cmdchain;
	data->cmd.status = 2;
	printf("bash: syntax error near unexpected token `|'\n");
	while (tmptk)
	{
		tmptk->error = 1;
		tmptk = tmptk->next;
	}
	(void)tmpprint;
	(void)tmp;
}

int	checksyntaxerror(t_data *data)
{
	t_tokens	*tmp;

	checkpipeerr(data);
	tmp = data->cmdchain;
	while (tmp)
	{
		if (casenext(&tmp))
			continue ;
		if (tmp->id == TOKEN_IN_FILE && checkfilein(tmp))
			handleerr(data, &tmp, &tmp);
		else if ((tmp->id == TOKEN_OUT_FILE || tmp->id == TOKEN_OUT_A_FILE)
			&& checkfileout(tmp))
			handleerr(data, &tmp, &(tmp->next));
		else if (tmp->id == TOKEN_COMMAND && check_path(tmp, data))
		{
			tmp->error = 1;
			tmp = getnextcommand(tmp);
			continue ;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}
