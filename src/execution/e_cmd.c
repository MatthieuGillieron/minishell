/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:21:31 by mg                #+#    #+#             */
/*   Updated: 2025/05/30 16:00:18 by mtaramar         ###   ########.fr       */
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
	if (!cmd || !cmd->args[0])
		return ;

	execute_command(cmd->args, env, status);
}

void	execute_parsed_command(t_command *cmd, t_env **env, t_status *status)
{
	
if (!cmd || !cmd->commands)
return ;
if (cmd->cmd_count == 1)
{
	execute_simple_cmd(cmd->commands[0], env, status);
	return ;
}
ft_putstr_fd("Pipeline pas encore fais (", 2);
ft_putnbr_fd(cmd->cmd_count, 2);
ft_putendl_fd(" commandes)", 2);
status->exit_code = 1;
// a faire
}

