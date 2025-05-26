/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:14:24 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/26 16:17:56 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Gestionnaire de signal pour le mode interactif (prompt)
 * Ctrl+C (SIGINT) affiche un nouveau prompt
 */

static void	sigint_interactive_handler(int sig)
{
	(void)sig;
	g_sig_received = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
/**
 * Gestionnaire de signal pour le mode d'exécution
 * Utilisé quand un processus enfant est en cours d'exécution
 */

static void	sigint_execution_handler(int sig)
{
	(void)sig;
	g_sig_received = 1;
}

/**
 * Gestionnaire de signal pour le mode heredoc
 * Ctrl+C (SIGINT) doit interrompre la lecture du heredoc
 */

static void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_sig_received = 1;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

/**
 * Configure le mode de traitement des signaux
*/

void	set_signal_mode(t_signal_mode mode)
{
	if (mode == INTERACTIVE_MODE)
	{
		signal(SIGINT, sigint_interactive_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == EXECUTION_MODE)
	{
		signal(SIGINT, sigint_execution_handler);
		signal(SIGQUIT, sigint_execution_handler);
	}
	else if (mode == HEREDOC_MODE)
	{
		signal(SIGINT, sigint_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);		
	}
}

void	init_signals(void)
{
	set_signal_mode(INTERACTIVE_MODE);
}

/**
 * Configure les signaux pour un processus parent
*/

void	handle_signal_parent(void)
{
	set_signal_mode(EXECUTION_MODE);
}

void	handle_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
