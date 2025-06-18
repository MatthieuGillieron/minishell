/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_export_alone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magillie <magillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:19:51 by magillie          #+#    #+#             */
/*   Updated: 2025/06/17 16:25:12 by magillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * handle_export_no_value - Traite un argument d'export sans valeur.
 * @arg: Argument à traiter.
 * @env: Pointeur sur la liste d'environnement.
 * 
 * Retourne 0 si succès, 1 si erreur.
 */
int	handle_export_no_value(char *arg, t_env **env)
{
	char	*key;
	int		result;

	key = ft_strdup(arg);
	if (!env_get(*env, key))
		result = env_set(env, key, "");
	else
		result = 0;
	free(key);
	return (result);
}
