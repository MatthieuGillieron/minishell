/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:33:41 by mg                #+#    #+#             */
/*   Updated: 2025/05/10 16:25:53 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Gère le cas où cd est appelé sans argument ou avec "~"
 * Va dans le répertoire $HOME si défini.
 *
 * @return 0 si succès, 1 en cas d'erreur
 */
static int	handle_home_directory(void)
{
	char	*home;

	// Récupère la variable d'environnement HOME
	home = getenv("HOME");
	if (!home)
	{
		// HOME n'est pas défini → affiche une erreur
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	// Tente de changer de répertoire vers HOME
	if (chdir(home) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

/**
 * Met à jour les variables d'environnement PWD et OLDPWD
 * après un changement de répertoire réussi.
 */
static void	update_env_vars(void)
{
	char	current_dir[1024];
	char	*old_pwd;

	// Sauvegarde l'ancien PWD dans OLDPWD
	old_pwd = getenv("PWD");
	if (old_pwd)
		setenv("OLDPWD", old_pwd, 1);
	// Met à jour PWD avec le répertoire courant
	if (getcwd(current_dir, sizeof(current_dir)))
		setenv("PWD", current_dir, 1);
}

/**
 * Gère le cas "cd -" → revient au répertoire précédent ($OLDPWD)
 *
 * @return 0 si succès, 1 en cas d'erreur
 */
static int	handle_oldpwd(void)
{
	char	*old_pwd;

	// Récupère la variable d'environnement OLDPWD
	old_pwd = getenv("OLDPWD");
	if (!old_pwd)
	{
		// OLDPWD n'est pas défini → affiche une erreur
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	// Change de répertoire vers OLDPWD
	if (chdir(old_pwd) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	// Affiche le nouveau répertoire courant
	printf("%s\n", old_pwd);
	// Met à jour PWD et OLDPWD
	update_env_vars();
	return (0);
}

/**
 * Gère le cas général "cd <path>" → change vers un chemin donné
 *
 * @param path Le chemin cible
 * @return 0 si succès, 1 en cas d'erreur
 */
static int	handle_target_directory(char *path)
{
	// Tente de changer de répertoire vers <path>
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	// Met à jour PWD et OLDPWD
	update_env_vars();
	return (0);
}

/**
 * Fonction principale builtin_cd
 * Redirige vers les bons cas : HOME, "-", ou un chemin spécifique.
 *
 * @param argv Arguments de la commande (argv[0] est "cd")
 * @return 0 si succès, 1 en cas d'erreur
 */
int	builtin_cd(char **argv)
{
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		return (handle_home_directory());
	else if (ft_strcmp(argv[1], "-") == 0)
		return (handle_oldpwd());
	else
		return (handle_target_directory(argv[1]));
}
