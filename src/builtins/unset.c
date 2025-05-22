/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:33:28 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/21 15:50:06 by mtaramar         ###   ########.fr       */
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
