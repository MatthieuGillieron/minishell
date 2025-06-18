/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:09:26 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:09:26 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_heredoc(t_redirect *redirects)
{
	t_redirect	*current;
	int			has_heredoc;

	has_heredoc = 0;
	current = redirects;
	while (current)
	{
		if (current->type == REDIR_HEREDOC_OUT)
			has_heredoc = 1;
		current = current->next;
	}
	return (has_heredoc);
}

static void	restore_fds(int stdin_fd, int stdout_fd)
{
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
}

static void	handle_command(t_simple_cmd *cmd, t_env **env,
						t_status *status, int has_heredoc)
{
	char	buffer[1024];

	if (has_heredoc && (!cmd->args || !cmd->args[0]))
	{
		while (read(STDIN_FILENO, buffer, sizeof(buffer)) > 0)
			;
	}
	else if (cmd->args && cmd->args[0])
	{
		execute_command(cmd->args, env, status);
		if (has_heredoc && cmd->args[0] && ft_strcmp(cmd->args[0], "cat") == 0)
			write(STDOUT_FILENO, "\n", 1);
	}
}

static void	execute_simple_cmd(t_simple_cmd *cmd, t_env **env, t_status *status)
{
	int	stdin_backup;
	int	stdout_backup;
	int	has_heredoc;

	if (!cmd)
		return ;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	has_heredoc = 0;
	if (cmd->redirects)
	{
		has_heredoc = check_heredoc(cmd->redirects);
		if (apply_redirections(cmd->redirects, *env, status) == -1)
		{
			status->exit_code = 1;
			restore_fds(stdin_backup, stdout_backup);
			return ;
		}
	}
	handle_command(cmd, env, status, has_heredoc);
	restore_fds(stdin_backup, stdout_backup);
}

void	execute_parsed_command(t_command *cmd, t_env **env, t_status *status)
{
	if (!cmd || !cmd->commands)
		return ;
	if (cmd->cmd_count == 1)
	{
		execute_simple_cmd(cmd->commands[0], env, status);
		return ;
	}
	execute_pipeline(cmd, env, status);
}
