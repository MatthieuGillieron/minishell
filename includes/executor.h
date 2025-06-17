/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:16:06 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:16:07 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void	execute_command(char **argv, t_env **env, t_status *status);
void	execute_parsed_command(t_command *cmd, t_env **env, t_status *status);
void	execute_pipeline(t_command *cmd, t_env **env, t_status *status);
typedef struct s_pipeline_data
{
	int		**pipes;
	pid_t	*pids;
	int		pipe_count;
}	t_pipeline_data;

void	execute_pipeline_commands(t_command *cmd, t_env **env, t_status *status,
			t_pipeline_data *data);
void	restore_std_fds(int stdin_fd, int stdout_fd);
void	close_all_pipes(int **pipes, int count);
void	free_pipes(int **pipes, int count);
void	setup_pipes(int cmd_index, int pipe_count, int **pipes);
int		apply_output_redirection(char *file_path);
int		apply_append_redirection(char *file_path);
void	execute_child_process(t_simple_cmd *cmd_data, t_env **env,
			t_status *status);
void	wait_for_children(pid_t *pids, int count, t_status *status);
int		apply_redirections(t_redirect *redirects, t_env *env, t_status *status);

// Fonctions pour les heredocs
int		apply_heredoc_redirection(char *delimiter);
int		apply_heredoc_with_expansion(t_redirect *current,
			t_env *env, t_status *status);

#endif