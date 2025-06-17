/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:09:21 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:09:22 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * builtin_unset - Supprime des variables d’environnement.
 * @argv: Liste de variables à supprimer.
 * @env: Double pointeur vers liste env.
 * 
 * Retourne toujours 0.
 */
int	builtin_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		env_unset(env, argv[i]);
		i++;
	}
	return (0);
}
