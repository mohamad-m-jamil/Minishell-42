/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:12:12 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:12:14 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkfileout(t_tokens *token)
{
	t_tokens	*next_token;

	next_token = getnext(token);
	if (!next_token || (next_token->id != TOKEN_FILE))
		return (1);
	return (0);
}

int	checkfilein(t_tokens *token)
{
	t_tokens	*next_token;

	next_token = getnext(token);
	if (!next_token || (next_token->id != TOKEN_FILE))
		return (1);
	return (0);
}

void	printerror(t_tokens *token)
{
	if (token == NULL)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (token->id == TOKEN_DIRECTORY)
		printf("bash: %s: Is a directory\n", getnext(token)->content);
	else
	{
		if (getnext(token) && getnext(token)->content)
			printf("bash: syntax error near unexpected token `%s'\n",
				getnext(token)->content);
		else if (token->next)
			printf("bash: syntax error near unexpected token `%s'\n",
				token->next->content);
		else
			printf("bash: syntax error near unexpected token `newline'\n");
	}
}

int	is_command(t_tokens *token)
{
	return (access(token->content, F_OK) == 0 && access(token->content,
			X_OK) == 0);
}

int	isdirectory(t_tokens *token)
{
	DIR	*dir;

	printf("%s\n", token->content);
	dir = opendir(token->content);
	if (dir && (ft_strcmp(token->content, "/") || ft_strcmp(token->content,
				".")))
	{
		token->id = TOKEN_DIRECTORY;
		closedir(dir);
		return (1);
	}
	return (0);
}
