/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:08:26 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:08:27 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Met à jour les variables d'environnement PWD et OLDPWD.
 */
static int	update_env_vars(t_env **env)
{
	char	cwd[1024];
	char	*old_pwd;

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	old_pwd = env_get(*env, "PWD");
	if (env_set(env, "OLDPWD", old_pwd) != 0)
		return (1);
	if (env_set(env, "PWD", cwd) != 0)
		return (1);
	return (0);
}

/**
 * Gère `cd` sans argument : changement vers le répertoire HOME.
 */
static int	handle_home_directory(t_env **env)
{
	char	*home;

	home = env_get(*env, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("cd");
		return (1);
	}
	return (update_env_vars(env));
}

/**
 * Gère `cd -` : retour au répertoire précédent (OLDPWD).
 */
static int	handle_oldpwd(t_env **env)
{
	char	*old_pwd;

	old_pwd = env_get(*env, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(old_pwd) != 0)
	{
		perror("cd");
		return (1);
	}
	printf("%s\n", old_pwd);
	return (update_env_vars(env));
}

/**
 * Implémentation du builtin `cd`.
 */
int	builtin_cd(char **argv, t_env **env)
{
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		return (handle_home_directory(env));
	if (ft_strcmp(argv[1], "-") == 0)
		return (handle_oldpwd(env));
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (update_env_vars(env));
}
