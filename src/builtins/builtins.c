/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:58:52 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/11 19:01:28 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * check_builtin_display - Vérifie et exécute les commandes builtins d'affichage.
 * @argv: Liste des arguments de la commande.
 * @env: Liste chaînée des variables d'environnement.
 * 
 * Retourne 1 si un builtin a été exécuté, 0 sinon.
 */
static int	check_builtin_display(char **argv, t_env *env)
{
    if (ft_strcmp(argv[0], "echo") == 0)
        return (builtin_echo(argv), 1);
    if (ft_strcmp(argv[0], "pwd") == 0)
        return (builtin_pwd(), 1);
    if (ft_strcmp(argv[0], "env") == 0)
        return (builtin_env(env), 1);
    return (0);
}

/**
 * check_builtin_control - Vérifie et exécute les builtins de contrôle.
 * @argv: Liste des arguments.
 * @env: Environnement modifiable.
 * 
 * Retourne 1 si un builtin a été exécuté, sinon 0.
 */
static int	check_builtin_control(char **argv, t_env *env)
{
    if (ft_strcmp(argv[0], "cd") == 0)
        return (builtin_cd(argv, &env), 1);
    if (ft_strcmp(argv[0], "exit") == 0)
        return (builtin_exit(argv), 1);
    if (ft_strcmp(argv[0], "unset") == 0)
        return (builtin_unset(argv, &env), 1);
    if (ft_strcmp(argv[0], "export") == 0)
        return (builtin_export(argv, &env), 1);
    return (0);
}

/**
 * check_builtin - Teste si une commande est un builtin et l'exécute.
 * @argv: Commande et ses arguments.
 * @env: Environnement courant.
 * 
 * Retourne 1 si exécutée, 0 sinon.
 */
int	check_builtin(char *argv[], t_env *env)
{
    if (!argv || !argv[0])
        return (0);
    if (check_builtin_display(argv, env))
        return (1);
    if (check_builtin_control(argv, env))
        return (1);
    return (0);
}
