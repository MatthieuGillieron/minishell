/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:09:42 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:09:44 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Libère la mémoire allouée pour les pipes
 * @param pipes Tableau de descripteurs de fichiers
 * @param count Nombre de pipes
 */
void	free_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

/**
 * Attend la fin de tous les processus enfants
 * @param pids Tableau des PIDs des processus enfants
 * @param count Nombre de processus
 * @param status Structure contenant l'état du shell
 */
void	wait_for_children(pid_t *pids, int count, t_status *status)
{
	int	i;
	int	cmd_status;

	if (!pids)
		return ;
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &cmd_status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(cmd_status))
				status->exit_code = WEXITSTATUS(cmd_status);
			else if (WIFSIGNALED(cmd_status))
				status->exit_code = 128 + WTERMSIG(cmd_status);
		}
		i++;
	}
}

/**
 * Restaure les descripteurs de fichiers standard
 * @param stdin_fd Sauvegarde du descripteur d'entrée standard
 * @param stdout_fd Sauvegarde du descripteur de sortie standard
 */
void	restore_std_fds(int stdin_fd, int stdout_fd)
{
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
	set_signal_mode(INTERACTIVE_MODE);
}

/**
 * Exécute une commande dans un processus enfant du pipeline
 * @param cmd_data Structure contenant les données de la commande
 * @param env Pointeur vers l'environnement
 * @param status Structure contenant l'état du shell
 */
void	execute_child_process(t_simple_cmd *cmd_data, t_env **env,
							t_status *status)
{
	handle_signals_child();
	if (cmd_data->redirects)
	{
		if (apply_redirections(cmd_data->redirects, *env, status) == -1)
			exit(1);
	}
	if (check_builtin(cmd_data->args, env, status))
		exit(status->exit_code);
	execute_command(cmd_data->args, env, status);
	exit(status->exit_code);
}
