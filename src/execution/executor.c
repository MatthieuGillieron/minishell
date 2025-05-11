/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:14:37 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/11 13:57:40 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * execute_command - Fonction principale pour exécuter une commande.
 *
 * Cette fonction prend une ligne de commande splittée (argv),
 * vérifie si c'est une commande builtin (comme cd, echo, etc.),
 * et l'exécute si c’est le cas.
 * Sinon, elle essaie de localiser le binaire via PATH, puis forke
 * un processus fils pour l’exécuter avec execve.
 *
 * @param argv: Liste des arguments de la commande (argv[0] est le nom de la commande)
 * @param env: Liste chaînée contenant les variables d’environnement (type t_env*)
 */
void	execute_command(char **argv, t_env *env)
{
	pid_t	pid;
	char	*path;
	int		status;
	char	**envp;
 
	if (check_builtin(argv, env))
		return ;
	path = get_command_path(argv[0], env);
	if (!path)
		return (ft_putstr_fd("command not found: ", 2),
			ft_putendl_fd(argv[0], 2));
	pid = fork();
	if (pid == 0)
	{
		envp = env_to_array(env);
		execve(path, argv, envp);
		perror("execve");
		free_split(envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	free(path);
} 
