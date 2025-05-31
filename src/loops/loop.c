#include "../includes/minishell.h"

static void	process_tokens(t_token **tokens, t_status *status)
{
	t_command	*cmd;
	int			i;

	expand_tokens(tokens, status->env, status);
	cmd = parse_tokens(tokens);
	if (cmd)
	{
		execute_parsed_command(cmd, &status->env, status);
		free_command(cmd);
	}
	i = 0;
	while (tokens[i])
		free_token(tokens[i++]);
	free(tokens);
}

static int	read_and_process_line(t_status *status)
{
	char		*line;
	t_token		**tokens;

	line = readline(MAGENTA"MNM$ "RST);
	if (!line)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (*line)
		add_history(line);
	if (is_special_command(line, status))
	{
		free(line);
		return (1);
	}
	tokens = tokenize_input(line);
	if (tokens)
		process_tokens(tokens, status);
	free(line);
	return (1);
}

void	shell_loop(t_status *status)
{
	while (status->running)
	{
		set_signal_mode(INTERACTIVE_MODE);
		g_sig_received = 0;
		if (!read_and_process_line(status))
			break;
	}
}