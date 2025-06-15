#include "../../includes/minishell.h"

static int	run_execve(char *path, char **argv, t_env *env)
{
	char	**envp;

	handle_signals_child();
	envp = env_to_array(env);
	execve(path, argv, envp);
	perror("execve");
	free_split(envp);
	free(path);
	exit(126);
}

static void	handle_child_signals(int cmd_status, t_status *status)
{
	if (WIFEXITED(cmd_status))
		status->exit_code = WEXITSTATUS(cmd_status);
	else if (WIFSIGNALED(cmd_status))
	{
		status->exit_code = 128 + WTERMSIG(cmd_status);
		if (WTERMSIG(cmd_status) == SIGINT)
			write(1, "^C\n", 3);
		else if (WTERMSIG(cmd_status) == SIGQUIT)
			write(1, "^\\Quit\n", 7);
	}
}

static void	exec_non_builtin(char **argv, t_env **env,
			t_status *status, char *path)
{
	pid_t	pid;
	int		cmd_status;

	handle_signals_parent();
	pid = fork();
	if (pid == 0)
		run_execve(path, argv, *env);
	waitpid(pid, &cmd_status, 0);
	set_signal_mode(INTERACTIVE_MODE);
	handle_child_signals(cmd_status, status);
}

void	execute_command(char **argv, t_env **env, t_status *status)
{
	char	*path;
	struct stat file_stat;

	if (!argv || !argv[0] || !argv[0][0])
	{
		status->exit_code = 0;
		return ;
	}

	if (check_builtin(argv, env, status))
		return ;
	if (ft_strchr(argv[0], '/'))
	{
		if (stat(argv[0], &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
			{
				ft_putstr_fd(argv[0], 2);
				ft_putendl_fd(": is a directory", 2);
				status->exit_code = 126;
				return ;
			}
		}
	}
	path = get_command_path(argv[0], *env);
	if (!path)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(argv[0], 2);
		status->exit_code = 127;
		return ;
	}
	exec_non_builtin(argv, env, status, path);
	free(path);
}
