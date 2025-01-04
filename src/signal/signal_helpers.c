
#include "../../includes/minishell.h"

void	handlesignal(t_data *data)
{
	if (data->cmd.running == 1)
		kill(data->cmd.pid, SIGINT);
	data->cmd.running = 0;
}

void	interactivehandle_sigint(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signalint = 130;
	(void)sig;
}

void	interactivehandle_sigquit(int sig)
{
	(void)sig;
}

void	noninteractivehandle_sigint(int sig)
{
	printf("\n");
	g_signalint = 130;
	(void)sig;
}

void	noninteractivehandle_sigquit(int sig)
{
	(void)sig;
}
