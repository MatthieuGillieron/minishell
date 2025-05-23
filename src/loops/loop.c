/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:18:22 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/22 15:12:07 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Variable globale utilisée pour stocker
// 	le code de retour de la dernière commande
extern int	g_exit_status;

/**
 * @brief Boucle principale de l'interpréteur Minishell.
 *
 * Cette boucle lit une ligne de commande de l'utilisateur via readline,
 * la stocke dans l'historique si elle n'est pas vide,
 * la parse en tokens (arguments), exécute la commande,
 * puis libère toute la mémoire allouée.
 *
 * Elle continue jusqu'à ce que l'utilisateur entre EOF (Ctrl+D),
 * auquel cas "exit" est affiché et la boucle se termine.
 *
 * @param env Structure chaînée contenant l'environnement courant.
 */
void	shell_loop(t_env **env)
{
	char		*line;
	t_token		**tokens;
	t_command	*cmd;
	int			i;

	while (1)
	{
		line = readline(MAGENTA"MNM$ "RST);
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		tokens = tokenize_input(line);
		if (tokens)
		{
			cmd = parse_tokens(tokens);
			if (cmd)
			{
				(void)*env; // c est en attendant trou de bal  pour vesqui le flag
				 
				// TODO: Implémenter l'exécution de la commande
                // execute_command(cmd, env);
				free_command(cmd);
			}
			i = 0;
			while (tokens[i])
				free_token(tokens[i++]);
			free(tokens);
		}
		free(line);
	}
}
