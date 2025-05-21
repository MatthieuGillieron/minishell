/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:18:22 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/21 16:02:35 by mtaramar         ###   ########.fr       */
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
	char	*line;
	char	**argv;

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
		argv = parse_line(line);
		if (argv && argv[0])
			execute_command(argv, env);
		free_args(argv);
		free(line);
	}
}
