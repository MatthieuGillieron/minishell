/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:33:41 by mg                #+#    #+#             */
/*   Updated: 2025/05/11 13:54:47 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * update_env_vars - Met à jour les variables PWD et OLDPWD.
 * @env: Double pointeur sur liste env.
 * 
 * Retourne 0 si tout est ok, 1 en cas d'erreur.
 */
static int	update_env_vars(t_env **env)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	return (
		env_set(env, "OLDPWD", env_get(*env, "PWD")) ||
		env_set(env, "PWD", cwd)
	);
}

/**
 * handle_home_directory - Gère `cd` sans argument, vers HOME.
 * @env: Pointeur sur env.
 * 
 * Retourne 0 si succès, sinon 1.
 */
static int	handle_home_directory(t_env **env)
{
	char	*home = env_get(*env, "HOME");

	if (!home)
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	if (chdir(home) != 0)
		return (perror("cd"), 1);
	return (update_env_vars(env));
}

/**
 * handle_oldpwd - Gère `cd -`, pour revenir à l’ancien répertoire.
 * @env: Environnement.
 * 
 * Retourne 0 si succès, sinon 1.
 */
static int	handle_oldpwd(t_env **env)
{
	char	*old_pwd = env_get(*env, "OLDPWD");

	if (!old_pwd)
		return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
	if (chdir(old_pwd) != 0)
		return (perror("cd"), 1);
	printf("%s\n", old_pwd);
	return (update_env_vars(env));
}

/**
 * builtin_cd - Implémente le builtin cd (déplacement répertoire).
 * @argv: Arguments.
 * @env: Liste env modifiable.
 * 
 * Retourne 0 ou 1 selon le succès.
 */
int	builtin_cd(char **argv, t_env **env)
{
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		return (handle_home_directory(env));
	else if (ft_strcmp(argv[1], "-") == 0)
		return (handle_oldpwd(env));
	else if (chdir(argv[1]) != 0)
		return (perror("cd"), 1);
	return (update_env_vars(env));
}
