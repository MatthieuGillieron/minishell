/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:15:20 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:15:21 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig_received = 0;

int	main(int argc, char **argv, char **envp)
{
	t_status	status;

	(void)argc;
	(void)argv;
	status.env = init_env_list(envp);
	if (!status.env)
		return (1);
	status.exit_code = 0;
	status.running = 1;
	init_signals();
	shell_loop(&status);
	free_env_list(status.env);
	return (status.exit_code);
}
