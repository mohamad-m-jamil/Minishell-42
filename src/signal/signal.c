#include "../../includes/minishell.h"

char	*getinfo(t_data *data)
{
	(void)data;
	char	*info;

	info = ft_strdup("");
	if (!info)
		return (NULL);
	info = ft_strjoingnl(info, "Minishell >> ");
	return (info);
}

void	interactivemode(t_data *data, char **input)
{
	char	*info;

	signal(SIGINT, interactivehandle_sigint);
	signal(SIGQUIT, interactivehandle_sigquit);
	signal(SIGTSTP, SIG_IGN);
	while (1)
	{
		info = getinfo(data);
		*input = readline(info);
		free(info);
		if (input != NULL)
			break ;
		if (ft_strlen(*input) != 0)
		{
			break ;
		}
	}
	if (g_signalint != 0)
	{
		data->cmd.status = g_signalint;
		g_signalint = 0;
	}
	(void)data;
}

void	noninteractivemode(t_data *data, char **input)
{
	signal(SIGINT, noninteractivehandle_sigint);
	signal(SIGQUIT, noninteractivehandle_sigint);
	signal(SIGTSTP, SIG_IGN);
	while (data->cmd.running == 1 && g_signalint != 130)
	{
		if (g_signalint == 130)
		{
			handlesignal(data);
			printf("\n");
			data->cmd.status = g_signalint;
			g_signalint = 0;
			break ;
		}
	}
	(void)*input;
}
