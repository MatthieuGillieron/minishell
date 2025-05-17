/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:16:14 by mg                #+#    #+#             */
/*   Updated: 2025/05/16 14:10:02 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_arg(t_simple_cmd *cmd, char *arg)
{
	char	**new_args;
	int i;

	new_args = (char **)malloc(sizeof(char *) * (cmd->arg_count + 2));
	if (!new_args)
		return (0);
	
	i = 0;
	while (i < cmd->arg_count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[cmd->arg_count] = arg;
	new_args[cmd->arg_count + 1] = NULL;

	if (cmd->args)
		free(cmd->args);
	
	cmd->args = new_args;
	cmd->arg_count++;

	return (1);
}

// Fonction utilitaire pour ajouter une redirection à la commande
static int	add_redirect(t_simple_cmd *cmd, t_redirect *redirect)
{
	t_redirect *current;
	if (!cmd->redirects)
		cmd->redirects = redirect;
	else
	{
		 // Ajouter à la fin de la liste
		 current = cmd->redirects;
		 while (current->next)
			 current = current->next;
		 current->next = redirect;
	}
	return 1;
}

t_simple_cmd *parse_simple_command(t_token ***tokens_ptr)
{
    t_simple_cmd *cmd;
    t_redirect *redirect;

    cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
    if (!cmd)
        return (NULL);
    
    // Initialiser la commande
    cmd->args = NULL;
    cmd->arg_count = 0;
    cmd->redirects = NULL;
    
    // Parcourir les tokens jusqu'à trouver un pipe ou la fin
    while (**tokens_ptr && (***tokens_ptr).type != PIPE)
    {
        if ((***tokens_ptr).type == WORD)
        {
            // Ajouter l'argument à la commande
            if (!add_arg(cmd, (***tokens_ptr).value))
                return (NULL);
            (*tokens_ptr)++;
        }
        else if ((***tokens_ptr).type == REDIR_IN || (***tokens_ptr).type == REDIR_OUT || 
                 (***tokens_ptr).type == REDIR_APPEND || (***tokens_ptr).type == HEREDOC)
        {
            t_token_type redir_type = (***tokens_ptr).type;
            (*tokens_ptr)++; // Avancer au token après la redirection
            
            // Parser la redirection
            redirect = parse_redirection(tokens_ptr, redir_type);
            if (!redirect)
                return (NULL);
            
            // Ajouter la redirection à la commande
            if (!add_redirect(cmd, redirect))
                return (NULL);
        }
        else
        {
            // Token inattendu, erreur de syntaxe
            return (NULL);
        }
    }
    
    return (cmd);
}
