/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:37:37 by mg                #+#    #+#             */
/*   Updated: 2025/05/21 15:44:42 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Libérer une redirection et toutes celles qui suivent
static void	free_redirects(t_redirect *redirect)
{
	t_redirect	*next;

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
static void	free_simple_cmd(t_simple_cmd *cmd)
{
	if (!cmd)
		return ;
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
void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->commands)
	{
		i = 0;
		while (i < cmd->cmd_count)
		{
			free_simple_cmd(cmd->commands[i]);
			i++;
		}
		free(cmd->commands);
	}
	free(cmd);
}
