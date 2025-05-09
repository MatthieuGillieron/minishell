/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:58:52 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/09 10:58:52 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtin(char **argv)
{
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
	{
		builtin_pwd();
		return (1);
	}
	if (ft_strncmp(argv[0], "echo", 5) == 0)
	{
		builtin_echo(argv);
		return (1);
	}
	if (ft_strncmp(argv[0], "env", 4) == 0)
	{
		builtin_env();
		return (1);
	}
	return (0);
}
