/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:05:28 by mg                #+#    #+#             */
/*   Updated: 2025/05/11 14:00:41 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

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
int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env_list(envp);
	if (!env)
		return (1);
	init_signals();
	shell_loop(env);
	free_env_list(env);
	return (g_exit_status);
}
