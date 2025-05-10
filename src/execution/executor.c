/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:14:37 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/10 17:15:54 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Exécute une commande donnée.
 * Vérifie si c'est un builtin, sinon cherche le chemin et
 			exécute via fork+execve.
 *
 * @param argv Tableau des arguments de la commande.
 * @param env_copy Le tableau d'environnement dynamique à utiliser.
 */
void	execute_command(char **argv, char **env_copy)
{
	pid_t	pid;
	char	*path;
	int		status;

	if (check_builtin(argv, env_copy))
		return ;
	path = get_command_path(argv[0], env_copy);
	if (!path)
		return (ft_putstr_fd("command not found: ", 2),
			ft_putendl_fd(argv[0], 2));
	pid = fork();
	if (pid == 0)
	{
		execve(path, argv, env_copy);
		perror("execve");
		exit(1);
	}
	if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
	free(path);
}
