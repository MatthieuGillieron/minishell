/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:14:30 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:14:31 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_interactive_handler(int sig)
{
	(void)sig;
	g_sig_received = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_execution_handler(int sig)
{
	(void)sig;
	g_sig_received = 1;
}

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_sig_received = 1;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}
