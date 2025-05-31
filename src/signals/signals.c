#include "../includes/minishell.h"

static void	sigint_interactive_handler(int sig)
{
	(void)sig;
	g_sig_received = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigint_execution_handler(int sig)
{
	(void)sig;
	g_sig_received = 1;
}

static void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_sig_received = 1;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	set_signal_mode(t_signal_mode mode)
{
	if (mode == INTERACTIVE_MODE)
	{
		signal(SIGINT, sigint_interactive_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == EXECUTION_MODE)
	{
		signal(SIGINT, sigint_execution_handler);
		signal(SIGQUIT, sigint_execution_handler);
	}
	else if (mode == HEREDOC_MODE)
	{
		signal(SIGINT, sigint_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	init_signals(void)
{
	set_signal_mode(INTERACTIVE_MODE);
}

void	handle_signals_parent(void)
{
	set_signal_mode(EXECUTION_MODE);
}

void	handle_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}