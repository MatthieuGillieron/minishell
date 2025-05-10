/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:58:52 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/10 15:36:57 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Vérifie si la commande correspond à un builtin d'affichage (echo, pwd, env)
 * et l'exécute si c'est le cas.
 *
 * @param argv Arguments de la commande
 * @return 1 si un builtin a été exécuté, 0 sinon
 */
static int	check_builtin_display(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv), 1);
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(), 1);
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(), 1);
	return (0);
}

/**
 * Vérifie si la commande correspond à un builtin de contrôle
 	(cd, export, unset, exit)
 * et l'exécute si c'est le cas.
 *
 * @param argv Arguments de la commande
 * @return 1 si un builtin a été exécuté, 0 sinon
 */
static int	check_builtin_control(char **argv)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv), 1);
	// Ajouter export, unset, exit quand fonction cree
	return (0);
}

/**
 * Vérifie si la commande est un builtin, en la cherchant d'abord
 * dans les commandes d'affichage, puis dans les commandes de contrôle.
 *
 * @param argv Arguments de la commande
 * @return 1 si un builtin a été exécuté, 0 sinon
 */
int	check_builtin(char *argv[])
{
	if (!argv || !argv[0])
		return (0);
	if (check_builtin_display(argv))
		return (1);
	if (check_builtin_control(argv))
		return (1);
	return (0);
}
