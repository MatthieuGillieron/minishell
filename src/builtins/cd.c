/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:33:41 by mg                #+#    #+#             */
/*   Updated: 2025/05/10 12:23:32 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Gère le cas où cd est appelé sans argument (aller au $HOME)
 * 
 * @return 0 en cas de succès, 1 sinon
 */
static int	handle_home_directory(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		fprintf(stderr, "minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

/**
 * Implémentation de la commande builtin cd
 * Change le répertoire courant
 *
 * @param argv Arguments de la commande (argv[0] est "cd")
 * @return 0 en cas de succès, 1 sinon
 */
int	builtin_cd(char **argv)
{
    if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
        return (handle_home_directory());
    else if (ft_strcmp(argv[1], "-") == 0)
    {
        // Implémentation du cd - (retour au répertoire précédent)
        char *oldpwd = getenv("OLDPWD");
        if (!oldpwd)
        {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            return (1);
        }
        if (chdir(oldpwd) != 0)
        {
            perror("minishell: cd");
            return (1);
        }
        printf("%s\n", oldpwd);
        return (0);
    }
    else
    {
        if (chdir(argv[1]) != 0)
        {
            perror("minishell: cd");
            return (1);
        }
    }
    
    // Mise à jour des variables d'environnement PWD et OLDPWD
    char current_dir[1024];
    char *old_pwd;
    
    old_pwd = getenv("PWD");
    if (old_pwd)
        setenv("OLDPWD", old_pwd, 1);
    
    if (getcwd(current_dir, sizeof(current_dir)))
        setenv("PWD", current_dir, 1);
    
    return (0);
}
