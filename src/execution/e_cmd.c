/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:21:31 by mg                #+#    #+#             */
/*   Updated: 2025/05/27 14:52:20 by mg               ###   ########.fr       */
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
/*
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
*/

void execute_parsed_command(t_command *cmd, t_env **env, t_status *status)
{
    ft_putendl_fd("DEBUG: Entrée dans execute_parsed_command", 2);
    
    if (!cmd)
    {
        ft_putendl_fd("DEBUG: cmd est NULL", 2);
        return;
    }
    
    ft_putstr_fd("DEBUG: cmd_count = ", 2);
    ft_putnbr_fd(cmd->cmd_count, 2);
    ft_putendl_fd("", 2);
    
    if (!cmd->commands)
    {
        ft_putendl_fd("DEBUG: cmd->commands est NULL", 2);
        return;
    }
    
    if (cmd->cmd_count == 1)
    {
        ft_putendl_fd("DEBUG: Commande simple détectée", 2);
        
        if (!cmd->commands[0])
        {
            ft_putendl_fd("DEBUG: Première commande est NULL", 2);
            return;
        }
        
        // Afficher les arguments de la commande
        ft_putendl_fd("DEBUG: Arguments de la commande:", 2);
        if (cmd->commands[0]->args)
        {
            int i = 0;
            while (cmd->commands[0]->args[i])
            {
                ft_putstr_fd("DEBUG: arg[", 2);
                ft_putnbr_fd(i, 2);
                ft_putstr_fd("] = ", 2);
                ft_putendl_fd(cmd->commands[0]->args[i], 2);
                i++;
            }
        }
        else
        {
            ft_putendl_fd("DEBUG: args est NULL", 2);
        }
        
        execute_simple_cmd(cmd->commands[0], env, status);
        return;
    }
    // Reste du code...
}
