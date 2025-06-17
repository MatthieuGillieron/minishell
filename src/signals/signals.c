/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:14:35 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:14:35 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	handle_signals_parent(void)
{
	set_signal_mode(EXECUTION_MODE);
}

void	handle_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
