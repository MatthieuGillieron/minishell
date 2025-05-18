/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:26:59 by mg                #+#    #+#             */
/*   Updated: 2025/05/18 16:11:49 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

// Afficher le type de redirection
static void print_redir_type(t_redir_type type)
{
    if (type == REDIR_INPUT)
        printf("<");
    else if (type == REDIR_OUTPUT)
        printf(">");
    else if (type == REDIR_APPEND_OUT)
        printf(">>");
    else if (type == REDIR_HEREDOC_OUT)
        printf("<<");
}

// Afficher les redirections d'une commande
static void print_redirects(t_redirect *redirect)
{
    while (redirect)
    {
        printf(" ");
        print_redir_type(redirect->type);
        printf(" %s", redirect->file_or_delimiter);
        redirect = redirect->next;
    }
}

// Afficher une commande simple
static void print_simple_cmd(t_simple_cmd *cmd)
{
    int i;

    if (!cmd)
        return;

    // Afficher les arguments
    for (i = 0; i < cmd->arg_count; i++)
    {
        printf("%s", cmd->args[i]);
        if (i < cmd->arg_count - 1)
            printf(" ");
    }
    
    // Afficher les redirections
    if (cmd->redirects)
        print_redirects(cmd->redirects);
}

// Afficher la structure complète de commande
void print_command(t_command *cmd)
{
    int i;

    if (!cmd)
    {
        printf("Command is NULL\n");
        return;
    }

    printf("Command with %d parts:\n", cmd->cmd_count);
    for (i = 0; i < cmd->cmd_count; i++)
    {
        printf("  %d: ", i + 1);
        print_simple_cmd(cmd->commands[i]);
        if (i < cmd->cmd_count - 1)
            printf(" | ");
        printf("\n");
    }
}
