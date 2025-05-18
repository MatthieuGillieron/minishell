/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_core.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:19:26 by mg                #+#    #+#             */
/*   Updated: 2025/05/18 16:11:34 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

t_command	*parse_tokens(t_token **tokens)
{
	t_command	*cmd;
	t_token		**current_token;
	int i;

	if (!tokens || !tokens[0])
		return (NULL);

	// Allouer la structure de commande principale
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);

	// Compter le nombre de commandes (nombre de pipes + 1)
	cmd->cmd_count = 1; // au moin une commande
	current_token = tokens;
	while (*current_token)
	{
		if ((*current_token)->type == PIPE)
			cmd->cmd_count++;
		current_token++;
	}

	// Allouer le tableau de commandes simples
	cmd->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *) * cmd->cmd_count);
	if (!cmd->commands)
	{
		free(cmd);
		return (NULL);
	}

	 
    // Initialiser le tableau à NULL
    i = 0;
    while (i < cmd->cmd_count)
    {
        cmd->commands[i] = NULL;
        i++;
    }
    
    // Parser chaque commande simple
    current_token = tokens;
    i = 0;
    while (i < cmd->cmd_count)
    {
        cmd->commands[i] = parse_simple_command(&current_token);
        if (!cmd->commands[i])
        {
            free_command(cmd);
            return (NULL);
        }
        
        // Si on est sur un pipe, avancer au token suivant
        if (*current_token && (*current_token)->type == PIPE)
            current_token++;
        i++;
    }
    
    return (cmd);
}
