/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:11:09 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:11:33 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*read_input_line(void)
{
	char	*line;
	char	*tmp;

	if (isatty(fileno(stdin)))
		line = readline("MNM$ ");
	else
	{
		line = get_next_line(fileno(stdin));
		if (line)
		{
			tmp = line;
			line = ft_strtrim(line, "\n");
			free(tmp);
		}
	}
	return (line);
}

void	process_tokens(t_token **tokens, t_status *status)
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

static void	handle_tokens(t_token **tokens, t_status *status)
{
	int	i;

	if (!check_syntax(tokens))
	{
		status->exit_code = 2;
		i = 0;
		while (tokens[i])
			free_token(tokens[i++]);
		free(tokens);
	}
	else
		process_tokens(tokens, status);
}

static int	read_and_process_line(t_status *status)
{
	char		*line;
	t_token		**tokens;

	line = read_input_line();
	if (!line)
	{
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
		handle_tokens(tokens, status);
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
