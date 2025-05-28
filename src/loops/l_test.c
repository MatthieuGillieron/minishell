/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:10:31 by mg                #+#    #+#             */
/*   Updated: 2025/05/28 09:11:33 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void	shell_loop(t_status *status)
{
    char		*line;
    t_token		**tokens;
    t_command	*cmd;
    int			i;
	
    while (status->running)
    {
        set_signal_mode(INTERACTIVE_MODE);
        g_sig_received = 0;
        
        // Afficher le prompt et lire une ligne
        ft_putendl_fd("\nDEBUG: Attente d'une commande...", 2);
        line = readline(MAGENTA"MNM$ "RST);
        
        // Vérifier si l'utilisateur a tapé Ctrl+D
        if (!line)
        {
            ft_putendl_fd("DEBUG: Fin de l'entrée (Ctrl+D)", 2);
            write(1, "exit\n", 5);
            break ;
        }
        
        // Déboguer la ligne lue
        ft_putstr_fd("DEBUG: Ligne lue: '", 2);
        ft_putstr_fd(line, 2);
        ft_putendl_fd("'", 2);
        
        // Ajouter à l'historique si non vide
        if (*line)
        {
            add_history(line);
            ft_putendl_fd("DEBUG: Ajouté à l'historique", 2);
        }
        else
        {
            ft_putendl_fd("DEBUG: Ligne vide, ignorée", 2);
        }
        
        // Tokeniser la ligne de commande
        ft_putendl_fd("DEBUG: Tokenisation de la ligne...", 2);
        tokens = tokenize_input(line);
        
        // Vérifier si la tokenisation a réussi
        if (tokens)
        {
            // Afficher les tokens générés pour debug
            ft_putendl_fd("DEBUG: Tokens générés:", 2);
            i = 0;
            while (tokens[i])
            {
                ft_putstr_fd("DEBUG: Token ", 2);
                ft_putnbr_fd(i, 2);
                ft_putstr_fd(": type=", 2);
                ft_putnbr_fd(tokens[i]->type, 2);
                ft_putstr_fd(" (", 2);
                
                // Afficher le type en texte pour plus de clarté
                if (tokens[i]->type == WORD)
				ft_putstr_fd("WORD", 2);
                else if (tokens[i]->type == PIPE)
				ft_putstr_fd("PIPE", 2);
                else if (tokens[i]->type == REDIR_IN)
				ft_putstr_fd("REDIR_IN", 2);
                else if (tokens[i]->type == REDIR_OUT)
				ft_putstr_fd("REDIR_OUT", 2);
                else if (tokens[i]->type == REDIR_APPEND)
				ft_putstr_fd("REDIR_APPEND", 2);
                else if (tokens[i]->type == HEREDOC)
				ft_putstr_fd("HEREDOC", 2);
                else if (tokens[i]->type == ENV_VAR)
				ft_putstr_fd("ENV_VAR", 2);
                else if (tokens[i]->type == QUOTE)
				ft_putstr_fd("QUOTE", 2);
                else if (tokens[i]->type == WHITESPACE)
				ft_putstr_fd("WHITESPACE", 2);
                else if (tokens[i]->type == END_OF_INPUT)
				ft_putstr_fd("END_OF_INPUT", 2);
                else
				ft_putstr_fd("UNKNOWN", 2);
                
                ft_putstr_fd("), value='", 2);
                if (tokens[i]->value)
				ft_putstr_fd(tokens[i]->value, 2);
                else
				ft_putstr_fd("(NULL)", 2);
                ft_putendl_fd("'", 2);
                i++;
            }
            
            // Parser les tokens
            ft_putendl_fd("DEBUG: Parsing des tokens...", 2);
            cmd = parse_tokens(tokens);
            
            if (cmd)
            {
                // Afficher la structure de la commande
                ft_putendl_fd("\n--- Structure de commande ---", 2);
                print_command(cmd);
                ft_putendl_fd("---------------------------\n", 2);
                
                // Debug supplémentaire pour inspecter la structure
                ft_putstr_fd("DEBUG: Commande parsée avec ", 2);
                ft_putnbr_fd(cmd->cmd_count, 2);
                ft_putendl_fd(" sous-commande(s)", 2);
                
                // Vérification détaillée des arguments
                for (int j = 0; j < cmd->cmd_count; j++)
                {
                    ft_putstr_fd("DEBUG: Sous-commande ", 2);
                    ft_putnbr_fd(j, 2);
                    ft_putstr_fd(": ", 2);
                    
                    if (!cmd->commands[j])
                    {
                        ft_putendl_fd("NULL", 2);
                        continue;
                    }
                    
                    ft_putstr_fd("arg_count=", 2);
                    ft_putnbr_fd(cmd->commands[j]->arg_count, 2);
                    ft_putendl_fd("", 2);
                    
                    if (cmd->commands[j]->args)
                    {
                        int k = 0;
                        while (k < cmd->commands[j]->arg_count)
                        {
                            ft_putstr_fd("DEBUG:   arg[", 2);
                            ft_putnbr_fd(k, 2);
                            ft_putstr_fd("]=", 2);
                            if (cmd->commands[j]->args[k])
                            {
                                ft_putstr_fd("'", 2);
                                ft_putstr_fd(cmd->commands[j]->args[k], 2);
                                ft_putstr_fd("'", 2);
                            }
                            else
							ft_putstr_fd("NULL", 2);
                            ft_putendl_fd("", 2);
                            k++;
                        }
                        
                        // Vérification de la terminaison NULL
                        if (cmd->commands[j]->args[cmd->commands[j]->arg_count] != NULL)
						ft_putendl_fd("DEBUG:   ATTENTION: Le tableau args n'est pas NULL-terminé!", 2);
                    }
                    else
					ft_putendl_fd("DEBUG:   args est NULL", 2);
                }
                
                // Exécuter la commande
                ft_putendl_fd("DEBUG: Exécution de la commande...", 2);
                execute_parsed_command(cmd, &status->env, status);
                
                // Libérer la mémoire
                ft_putendl_fd("DEBUG: Libération de la structure de commande", 2);
                free_command(cmd);
            }
            else
            {
                ft_putendl_fd("DEBUG: Échec du parsing des tokens", 2);
            }
            
            // Libérer les tokens
            ft_putendl_fd("DEBUG: Libération des tokens", 2);
            i = 0;
            while (tokens[i])
			free_token(tokens[i++]);
            free(tokens);
        }
        else
        {
            ft_putendl_fd("DEBUG: Échec de la tokenisation", 2);
        }
        
        // Libérer la ligne
        free(line);
        ft_putendl_fd("DEBUG: Ligne libérée", 2);
    }
}
*/