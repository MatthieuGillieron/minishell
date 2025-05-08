/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:18:22 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/08 16:59:07 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_status;

void	shell_loop(void)
{
	char	*line;
	char	**argv;

	while (1)
	{
		line = readline("shell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		argv = parse_line(line);
		if (argv && argv[0])
		{
			print_tokens(argv);
			free_tokens(argv);
		}
		free(line);
	}
}
