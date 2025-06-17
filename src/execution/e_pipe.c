/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:09:34 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:09:35 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Alloue la mémoire pour les pipes
 * @param count Nombre de pipes à créer
 * @return Tableau de descripteurs alloué ou NULL
 */
static int	**allocate_pipes(int count)
{
	int	**pipes;
	int	i;

	if (count <= 0)
		return (NULL);
	pipes = malloc(sizeof(int *) * count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

/**
 * Crée les pipes nécessaires pour un pipeline
 * @param count Nombre de pipes à créer (nombre de commandes - 1)
 * @return Tableau de descripteurs de fichiers pour les pipes
 */
static int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	pipes = allocate_pipes(count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("minishell: pipe");
			free_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

/**
 * Ferme tous les descripteurs de fichiers des pipes
 * @param pipes Tableau de descripteurs de fichiers
 * @param count Nombre de pipes
 */
void	close_all_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

/**
 * Configure les redirections pour un processus dans un pipeline
 * @param cmd_index Index de la commande dans le pipeline
 * @param pipe_count Nombre total de pipes
 * @param pipes Tableau de descripteurs de fichiers
 */
void	setup_pipes(int cmd_index, int pipe_count, int **pipes)
{
	if (!pipes)
		return ;
	if (cmd_index == 0)
		dup2(pipes[0][1], STDOUT_FILENO);
	else if (cmd_index == pipe_count)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
	close_all_pipes(pipes, pipe_count);
}

/**
 * Exécute un pipeline de commandes
 * @param cmd Structure de commande contenant le pipeline
 * @param env Pointeur vers l'environnement
 * @param status Structure contenant l'état du shell
 */
void	execute_pipeline(t_command *cmd, t_env **env, t_status *status)
{
	t_pipeline_data	data;

	if (!cmd || cmd->cmd_count <= 0)
	{
		status->exit_code = 1;
		return ;
	}
	data.pipe_count = cmd->cmd_count - 1;
	data.pipes = create_pipes(data.pipe_count);
	if (!data.pipes)
	{
		status->exit_code = 1;
		return ;
	}
	data.pids = malloc(sizeof(pid_t) * cmd->cmd_count);
	if (!data.pids)
	{
		free_pipes(data.pipes, data.pipe_count);
		status->exit_code = 1;
		return ;
	}
	execute_pipeline_commands(cmd, env, status, &data);
}
