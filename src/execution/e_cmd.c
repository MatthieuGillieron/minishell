/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:21:31 by mg                #+#    #+#             */
/*   Updated: 2025/05/26 16:46:57 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Exécute une commande simple
 * @param cmd Commande simple à exécuter
 * @param env Pointeur vers l'environnement
 * @param status Structure contenant l'état du shell
*/

static void	execute_simple_cmd(t_simple_cmd *cmd, t_env **env, t_status *status)
{
	if (!cmd)
}