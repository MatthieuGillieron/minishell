/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:13:43 by mg                #+#    #+#             */
/*   Updated: 2025/05/11 19:00:47 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * is_valid_identifier - Vérifie si un nom de variable est valide.
 * @name: Nom à vérifier.
 * 
 * Un nom valide commence par une lettre ou '_' et ne contient
 * que des lettres, chiffres ou '_'.
 * 
 * Retourne 1 si valide, 0 sinon.
 */
static int	is_valid_identifier(char *name)
{
    int	i;

    if (!name || !*name)
        return (0);
    if (!ft_isalpha(name[0]) && name[0] != '_')
        return (0);
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

/**
 * handle_export_arg - Traite un argument de export.
 * @arg: Argument à traiter.
 * @env: Pointeur sur la liste d'environnement.
 * 
 * Retourne 0 si succès, 1 si erreur.
 */
static int	handle_export_arg(char *arg, t_env **env)
{
    char	*eq_pos;
    char	*key;
    char	*value;
    int		result;

    eq_pos = ft_strchr(arg, '=');
    if (!eq_pos)
    {
        if (!is_valid_identifier(arg))
        {
            ft_putstr_fd("minishell: export: '", 2);
            ft_putstr_fd(arg, 2);
            ft_putendl_fd("': not a valid identifier", 2);
            return (1);
        }
        return (0);
    }
    *eq_pos = '\0';
    if (!is_valid_identifier(arg))
    {
        *eq_pos = '=';
        ft_putstr_fd("minishell: export: '", 2);
        ft_putstr_fd(arg, 2);
        ft_putendl_fd("': not a valid identifier", 2);
        return (1);
    }
    key = ft_strdup(arg);
    value = ft_strdup(eq_pos + 1);
    *eq_pos = '=';
    result = env_set(env, key, value);
    free(key);
    free(value);
    return (result);
}

/**
 * builtin_export - Implémente la commande builtin export.
 * @argv: Arguments de la commande.
 * @env: Pointeur sur la liste d'environnement.
 * 
 * Sans arguments, affiche toutes les variables triées.
 * Avec arguments, ajoute ou met à jour les variables.
 * 
 * Retourne 0 si succès, code d'erreur sinon.
 */
int	builtin_export(char **argv, t_env **env)
{
    int	i;
    int	status;

    if (!argv[1])
    {
        print_sorted_env(*env);
        return (0);
    }
    status = 0;
    i = 1;
    while (argv[i])
    {
        if (handle_export_arg(argv[i], env))
            status = 1;
        i++;
    }
    return (status);
}
