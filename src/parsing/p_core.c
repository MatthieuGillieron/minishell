/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_core.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:11:38 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:11:38 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Initialise une structure de commande avec un nombre donné de commandes
 */
t_command	*initialize_command(int cmd_count)
{
	t_command	*cmd;
	int			i;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->cmd_count = cmd_count;
	cmd->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *) * cmd_count);
	if (!cmd->commands)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (i < cmd->cmd_count)
	{
		cmd->commands[i] = NULL;
		i++;
	}
	return (cmd);
}

/**
 * Compte le nombre de commandes dans un pipeline (nombre de pipes + 1)
 */
static int	count_commands(t_token **tokens)
{
	int			count;
	t_token		**current;

	count = 1;
	current = tokens;
	while (*current)
	{
		if ((*current)->type == PIPE)
			count++;
		current++;
	}
	return (count);
}

/**
 * Remplit la structure de commandes avec des commandes simples
 * extraites depuis la liste de tokens.
 *
 * @param cmd      Structure de commande à remplir.
 * @param tokens   Liste de tokens à parser.
 * @return         1 en cas de succès, 0 si une erreur survient.
 */
static int	fill_commands(t_command *cmd, t_token **tokens)
{
	t_token	**current;
	int		i;

	current = tokens;
	i = 0;
	while (i < cmd->cmd_count)
	{
		cmd->commands[i] = parse_simple_command(&current);
		if (!cmd->commands[i])
			return (0);
		if (*current && (*current)->type == PIPE)
			current++;
		i++;
	}
	return (1);
}

/**
  * Fonction principale du parsing qui transforme
  * un tableau de tokens en structure de commande.
  *
  * @param tokens   Tableau de tokens analysés.
  * @return         Structure t_command ou NULL en cas d'erreur.
*/
t_command	*parse_tokens(t_token **tokens)
{
	t_command	*cmd;
	int			cmd_count;

	if (!tokens || !tokens[0])
		return (NULL);
	cmd_count = count_commands(tokens);
	cmd = initialize_command(cmd_count);
	if (!cmd)
		return (NULL);
	if (!fill_commands(cmd, tokens))
	{
		free_command(cmd);
		return (NULL);
	}
	return (cmd);
}
