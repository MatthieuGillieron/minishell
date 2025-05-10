/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:18:22 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/10 17:15:35 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_status;

/**
 * Boucle principale du shell.
 * Lit les entrées utilisateur, les parse, exécute les commandes.
 *
 * @param env_copy Le tableau d'environnement dynamique à utiliser.
 */
void	shell_loop(char **env_copy)
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
			execute_command(argv, env_copy);
		free_tokens(argv);
		free(line);
	}
}
