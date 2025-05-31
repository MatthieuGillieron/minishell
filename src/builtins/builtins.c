#include "../../includes/minishell.h"

static int	check_builtin_display(char **argv, t_env *env, t_status *status)
{
	if (ft_strcmp(argv[0], "echo") == 0)
	{
		builtin_echo(argv);
		status->exit_code = 0;
		return (1);
	}
	if (ft_strcmp(argv[0], "pwd") == 0)
	{
		builtin_pwd();
		status->exit_code = 0;
		return (1);
	}
	if (ft_strcmp(argv[0], "env") == 0)
	{
		builtin_env(env);
		status->exit_code = 0;
		return (1);
	}
	return (0);
}

static int	check_builtin_control(char **argv, t_env **env, t_status *status)
{
	if (ft_strcmp(argv[0], "cd") == 0)
	{
		builtin_cd(argv, env);
		status->exit_code = 0;
		return (1);
	}
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		builtin_exit(argv);
		return (1);
	}
	if (ft_strcmp(argv[0], "unset") == 0)
	{
		builtin_unset(argv, env);
		status->exit_code = 0;
		return (1);
	}
	if (ft_strcmp(argv[0], "export") == 0)
	{
		builtin_export(argv, env);
		status->exit_code = 0;
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