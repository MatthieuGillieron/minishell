/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:58:52 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/26 17:05:02 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * check_builtin_display - Vérifie et exécute les commandes builtins d'affichage.
 * @argv: Liste des arguments de la commande.
 * @env: Liste chaînée des variables d'environnement.
 * 
 * Retourne 1 si un builtin a été exécuté, 0 sinon.
 */
static int	check_builtin_display(char **argv, t_env *env, t_status *status)
{
	if (ft_strcmp(argv[0], "echo") == 0)
	{
		builtin_echo(argv);
		status->exit_code = 0;
		return (1);
	}
	if (ft_strcmp(argv[0], "pwd") == 0)
	{
		builtin_pwd();
		status->exit_code = 0;
		return (1);
	}
	if (ft_strcmp(argv[0], "env") == 0)
	{
		builtin_env(env);
		status->exit_code = 0;
		return (1);
	}
	return (0);
}

/**
 * check_builtin_control - Vérifie et exécute les builtins de contrôle.
 * @argv: Liste des arguments.
 * @env: Environnement modifiable.
 * 
 * Retourne 1 si un builtin a été exécuté, sinon 0.
 */
static int	check_builtin_control(char **argv, t_env **env, t_status *status)
{
	if (ft_strcmp(argv[0], "cd") == 0)
	{
		builtin_cd(argv, env);
		status->exit_code = 0;
		return (1);
	}
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		builtin_exit(argv);
		return (1);
	}
	if (ft_strcmp(argv[0], "unset") == 0)
	{
		builtin_unset(argv, env);
		status->exit_code = 0;
		return (1);

	}
	if (ft_strcmp(argv[0], "export") == 0)
	{
		builtin_export(argv, env);
		status->exit_code = 0;
		return (1);
	}
	return (0);
}

/**
 * check_builtin - Teste si une commande est un builtin et l'exécute.
 * @argv: Commande et ses arguments.
 * @env: Pointeur sur l'environnement courant.
 * 
 * Retourne 1 si exécutée, 0 sinon.
 */
int	check_builtin(char **argv, t_env **env, t_status *status)
{
	if (!argv || !argv[0])
		return (0);
	if (check_builtin_display(argv, *env, status))
		return (1);
	if (check_builtin_control(argv, env, status))
		return (1);
	return (0);
}
