/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_status_reader.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:11:45 by mjamil            #+#    #+#             */
/*   Updated: 2025/01/04 14:17:53 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_pid_line(int fd)
{
	static char	buffer[256];
	ssize_t		bytes_read;

	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	return (strstr(buffer, "Pid:"));
}

ssize_t	read_status_file(char *buffer, size_t size)
{
	int		fd;
	ssize_t	bytes_read;

	fd = open("/proc/self/status", O_RDONLY);
	bytes_read = -1;
	if (fd != -1)
	{
		bytes_read = read(fd, buffer, size - 1);
		close(fd);
	}
	return (bytes_read);
}

void	ft_split_env(char *envp_str, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(envp_str, '=');
	if (equal_sign)
	{
		*key = ft_strndup(envp_str, equal_sign - envp_str);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(envp_str);
		*value = NULL;
	}
}

pid_t	ft_getuid(void)
{
	char	buffer[256];
	ssize_t	bytes_read;
	char	*uid_line;
	pid_t	uid;

	uid = -1;
	bytes_read = read_status_file(buffer, sizeof(buffer));
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		uid_line = ft_strstr(buffer, "Uid:");
		if (uid_line)
		{
			uid_line = ft_strchr(uid_line, '\t');
			if (uid_line)
				uid = ft_atoi(uid_line + 1);
		}
	}
	return (uid);
}
