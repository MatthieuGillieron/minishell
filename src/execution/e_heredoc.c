#include "../../includes/minishell.h"

static void	read_heredoc_input(int pipe_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strcmp(line, delimiter) == 0))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd);
		ft_putstr_fd("\n", pipe_fd);
		free(line);
	}
}

int	apply_heredoc_redirection(char *delimiter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	set_signal_mode(HEREDOC_MODE);
	read_heredoc_input(pipe_fd[1], delimiter);
	set_signal_mode(INTERACTIVE_MODE);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}

int	apply_heredoc_with_expansion(t_redirect *current,
	t_env *env, t_status *status)
{
	int		pipe_fd[2];
	char	*heredoc_content;

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	heredoc_content = process_heredoc(current->file_or_delimiter, env, status);
	if (!heredoc_content)
		return (-1);
	write(pipe_fd[1], heredoc_content, ft_strlen(heredoc_content));
	close(pipe_fd[1]);
	free(heredoc_content);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}
