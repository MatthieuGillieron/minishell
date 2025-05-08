/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:05:28 by mg                #+#    #+#             */
/*   Updated: 2025/05/08 14:14:17 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);       
}

int	main(int argc, char **argv, char **envp)
{
    char	*line;

    (void)argc;
    (void)argv;
    (void)envp;

    init_signals(); // Ajout du point-virgule ici
    while (1)
    {
        line = readline("shell$ ");  // <- ton prompt personnalisé ici
        if (!line) // ctrl-D
        {
            write(1, "exit\n", 5);
            break;
        }
        if (*line)
            add_history(line);
        free(line);
    }
    return (g_exit_status);
}
