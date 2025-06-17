/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:08:21 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:08:23 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_builtin_display(char **argv, t_env *env, t_status *status)
{
	if (ft_strcmp(argv[0], "echo") == 0)
	{
		status->exit_code = builtin_echo(argv);
		return (1);
	}
	if (ft_strcmp(argv[0], "pwd") == 0)
	{
		status->exit_code = builtin_pwd();
		return (1);
	}
	if (ft_strcmp(argv[0], "env") == 0)
	{
		status->exit_code = builtin_env(env);
		return (1);
	}
	return (0);
}

static int	check_builtin_control(char **argv, t_env **env, t_status *status)
{
	if (ft_strcmp(argv[0], "cd") == 0)
	{
		status->exit_code = builtin_cd(argv, env);
		return (1);
	}
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		status->exit_code = builtin_exit(argv);
		return (1);
	}
	if (ft_strcmp(argv[0], "unset") == 0)
	{
		status->exit_code = builtin_unset(argv, env);
		return (1);
	}
	if (ft_strcmp(argv[0], "export") == 0)
	{
		status->exit_code = builtin_export(argv, env);
		return (1);
	}
	return (0);
}

int	check_builtin(char **argv, t_env **env, t_status *status)
{
	if (!argv || !argv[0])
		return (0);
	if (check_builtin_display(argv, *env, status))
		return (1);
	if (check_builtin_control(argv, env, status))
		return (1);
	return (0);
}
