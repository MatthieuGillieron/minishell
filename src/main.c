/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:05:28 by mg                #+#    #+#             */
/*   Updated: 2025/05/27 15:04:42 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Fonction principale du programme minishell.
 *
 * - Initialise les signaux pour intercepter Ctrl+C / Ctrl+\
 * - Transforme le tableau d’environnement de base `envp` en liste chaînée
 * - Démarre la boucle d'exécution du shell (`shell_loop`)
 * - Nettoie la mémoire à la fin de l'exécution
 *
 * @param argc Nombre d’arguments passés au programme (non utilisé ici)
 * @param argv Tableau des arguments (non utilisé ici)
 * @param envp Tableau de chaînes représentant l’environnement système initial
 * @return Code de sortie global défini dans `g_exit_status`
 */

int	g_sig_received = 0;

int	main(int argc, char **argv, char **envp)
{
	t_status	status;

	(void)argc;
	(void)argv;

	status.env = init_env_list(envp);

	if (!status.env)
		return (1);
	status.exit_code = 0;
	status.running = 1;

	if (!status.env)
		return (1);
	init_signals();
	shell_loop(&status);
	free_env_list(status.env);
	return (status.exit_code);
}
