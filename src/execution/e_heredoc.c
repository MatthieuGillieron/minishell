/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:09:29 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:09:30 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	read_heredoc_input(int pipe_fd, char *delimiter)
{
	char	*line;
	int		has_content;

	has_content = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strcmp(line, delimiter) == 0))
		{
			free(line);
			if (has_content)
				ft_putstr_fd("\n", pipe_fd);
			break ;
		}
		if (has_content)
			ft_putstr_fd("\n", pipe_fd);
		has_content = 1;
		ft_putstr_fd(line, pipe_fd);
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
	size_t	content_len;

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	heredoc_content = process_heredoc(current->file_or_delimiter, env, status);
	if (!heredoc_content)
		return (-1);
	content_len = ft_strlen(heredoc_content);
	write(pipe_fd[1], heredoc_content, content_len);
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
