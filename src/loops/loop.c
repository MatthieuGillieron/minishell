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
/*
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
	{
		if (!check_syntax(tokens))
		{
			status->exit_code = 2;
			int i = 0;
			while (tokens[i])
			free_token(tokens[i++]);
			free(tokens);
		}
		else
		process_tokens(tokens, status);
	}
	free(line);
	return (1);
}
*/

static int	read_and_process_line(t_status *status)
{
	char		*line;
	t_token		**tokens;

	// 🌐 Choisir entre readline et get_next_line selon le mode
	if (isatty(fileno(stdin)))
		line = readline(MAGENTA"MNM$ "RST);
	else
	{
		line = get_next_line(fileno(stdin));
		if (line)
		{
			char *tmp = line;
			line = ft_strtrim(line, "\n"); // ⚠️ n'oublie pas de libérer `tmp` ensuite
			free(tmp);
		}
	}

	if (!line) // CTRL+D ou EOF
	{
		// Afficher "exit" uniquement en mode interactif
		if (isatty(fileno(stdin)))
			write(1, "exit\n", 5);
		return (0);
	}

	if (*line && isatty(fileno(stdin)))
		add_history(line);

	if (is_special_command(line, status))
	{
		free(line);
		return (1);
	}

	tokens = tokenize_input(line);
	if (tokens)
	{
		if (!check_syntax(tokens))
		{
			status->exit_code = 2;
			int i = 0;
			while (tokens[i])
				free_token(tokens[i++]);
			free(tokens);
		}
		else
			process_tokens(tokens, status);
	}

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
			break ;
	}
}
