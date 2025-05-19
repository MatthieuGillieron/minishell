/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:37:37 by mg                #+#    #+#             */
/*   Updated: 2025/05/19 12:08:36 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Libérer une redirection et toutes celles qui suivent
static void free_redirects(t_redirect *redirect)
{
    t_redirect *next;

    while (redirect)
    {
        next = redirect->next;
        // Ne pas libérer file_or_delimiter car il pointe vers
        // la valeur d'un token qui sera libéré ailleurs
        free(redirect);
        redirect = next;
    }
}

// Libérer une commande simple
static void free_simple_cmd(t_simple_cmd *cmd)
{
    if (!cmd)
        return;

    // Libérer les arguments
    if (cmd->args)
    {
        // Ne pas libérer les strings individuelles car elles
        // pointent vers les valeurs des tokens
        free(cmd->args);
    }
    
    // Libérer les redirections
    free_redirects(cmd->redirects);
    
    free(cmd);
}

// Libérer une structure de commande complète
void free_command(t_command *cmd)
{
    int i;

    if (!cmd)
        return;

    if (cmd->commands)
    {
        for (i = 0; i < cmd->cmd_count; i++)
            free_simple_cmd(cmd->commands[i]);
        free(cmd->commands);
    }
    
    free(cmd);
}
