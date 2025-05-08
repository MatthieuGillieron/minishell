/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:18:22 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/08 17:01:08 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int g_exit_status;

void	shell_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline("shell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*line)
			add_history(line);
		free(line);
	}
}
