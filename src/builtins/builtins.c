/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:58:52 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/10 12:10:37 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Vérifie si la commande est une builtin et l'exécute le cas échéant
 *
 * @param argv Arguments de la commande
 * @return 1 si c'est une builtin, 0 sinon
 */

/**
 * Vérifie si la commande est une builtin et l'exécute le cas échéant
 *
 * @param argv Arguments de la commande
 * @return 1 si c'est une builtin, 0 sinon
 */

int	check_builtin(char **argv)
{
    int	ret;

    ret = 0;
    if (!argv || !argv[0])
        return (0);
    if (ft_strncmp(argv[0], "echo", 5) == 0)
    {
        builtin_echo(argv);
        ret = 1;
    }
    else if (ft_strncmp(argv[0], "pwd", 4) == 0)
    {
        builtin_pwd();
        ret = 1;
    }
    else if (ft_strncmp(argv[0], "env", 4) == 0)
    {
        builtin_env();
        ret = 1;
    }
    else if (ft_strncmp(argv[0], "cd", 3) == 0)
    {
        builtin_cd(argv);
        ret = 1;
    }
    return (ret);
}
