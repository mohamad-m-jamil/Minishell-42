/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:27:12 by oabdelka          #+#    #+#             */
/*   Updated: 2025/01/04 14:20:43 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append2(t_tokens **tmp, char *data, int type)
{
	t_tokens	*new_node;

	new_node = NULL;
	if ((*tmp)->id == TOKEN_SPACE && type == TOKEN_SPACE)
		return ; //for double space
	if (((*tmp)->id == TOKEN_COMMAND || (*tmp)->id == TOKEN_WORD)
		&& (type == TOKEN_WORD || type == TOKEN_COMMAND))
		(*tmp)->content = ft_strjoingnl((*tmp)->content, data); //Merge if same type
	else if ((type != TOKEN_SPACE && (type == TOKEN_WORD
				|| type == TOKEN_COMMAND) && (*tmp)->id != TOKEN_SPACE))
	{
		new_node = newnode(ft_strdup(" "), TOKEN_SPACE);
		new_node->error = 0;
		(*tmp)->next = new_node;
		new_node->previous = (*tmp);
		(*tmp) = (*tmp)->next;
		addnode(tmp, data, type);
	}
	else
		addnode(tmp, data, type);
}

void	append(t_tokens **cmds, char *data, int type)
{
	t_tokens	*tmp;
	t_tokens	*new_node;
	char* 		dup_data= NULL;
	new_node = NULL;
	if ((!ft_strcmp(data, "\'\'") || !ft_strcmp(data, "\"\""))
		&& ft_strlen(data) == 2)
		{
 		    dup_data = ft_strdup("");
    		if (!dup_data)
        		return;
    		data = dup_data;
		}

	if (*cmds == NULL)
	{
		new_node = newnode(data, type);
		new_node->previous = newnode("START", TOKEN_START);
		new_node->error = 0;
		*cmds = new_node;
		if (dup_data)
			{
    			free(dup_data);
    			dup_data = NULL;
			}
		return ;
	}
	tmp = *cmds;
	while (tmp->next != NULL)
		tmp = tmp->next;
	append2(&tmp, data, type);
	if (dup_data)
			{
    			free(dup_data);
    			dup_data = NULL;
			}
}

t_tokens	*newnode(char *data, int type)
{
	t_tokens	*ptr;

	ptr = malloc(sizeof(t_tokens));
	if (ptr == NULL)
		return (NULL);
	ptr->content = ft_strdup(data);
	if (ptr->content == NULL)
	{
		free(ptr);
		return (NULL);
	}
	ptr->id = type;
	ptr->next = NULL;
	ptr->previous = NULL;
	ptr->error = 0;
	return (ptr);
}

void	addnode(t_tokens **tmp, char *data, int type)
{
	t_tokens	*new_node;

	new_node = newnode(data, type);
	new_node->error = 0;
	(*tmp)->next = new_node;
	new_node->previous = (*tmp);
}

