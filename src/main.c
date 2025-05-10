/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:05:28 by mg                #+#    #+#             */
/*   Updated: 2025/05/10 17:15:26 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

/**
 * Point d'entrée principal du shell.
 * Initialise les signaux, copie l'environnement, démarre la boucle principale.
 *
 * @param argc Nombre d'arguments (non utilisé).
 * @param argv Arguments du programme (non utilisé).
 * @param envp Environnement initial du système.
 * @return Le code de sortie final (g_exit_status).
 */
int	main(int argc, char **argv, char **envp)
{
	char	**env_copy;

	(void)argc;
	(void)argv;
	env_copy = copy_env(envp);
	if (!env_copy)
		return (1);
	init_signals();
	shell_loop(env_copy);
	free_env(env_copy);
	return (g_exit_status);
}
