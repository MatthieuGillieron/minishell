/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipeline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:09:38 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:09:38 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_pipeline_commands(t_command *cmd, t_env **env, t_status *status,
				t_pipeline_data *data)
{
	int	i;

	handle_signals_parent();
	i = 0;
	while (i < cmd->cmd_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
		{
			perror("minishell: fork");
			status->exit_code = 1;
			break ;
		}
		else if (data->pids[i] == 0)
		{
			setup_pipes(i, data->pipe_count, data->pipes);
			execute_child_process(cmd->commands[i], env, status);
		}
		i++;
	}
	close_all_pipes(data->pipes, data->pipe_count);
	if (i > 0)
		wait_for_children(data->pids, i, status);
	free_pipes(data->pipes, data->pipe_count);
	free(data->pids);
}
