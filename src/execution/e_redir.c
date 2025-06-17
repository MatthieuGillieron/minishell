/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:09:50 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:09:50 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	apply_input_redirection(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	process_redirection(t_redirect *current)
{
	if (current->type == REDIR_INPUT)
		return (apply_input_redirection(current->file_or_delimiter));
	else if (current->type == REDIR_OUTPUT)
		return (apply_output_redirection(current->file_or_delimiter));
	else if (current->type == REDIR_APPEND_OUT)
		return (apply_append_redirection(current->file_or_delimiter));
	else if (current->type == REDIR_HEREDOC_OUT)
		return (apply_heredoc_redirection(current->file_or_delimiter));
	return (0);
}

int	apply_redirections(t_redirect *redirects, t_env *env, t_status *status)
{
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (current->type == REDIR_HEREDOC_OUT)
		{
			if (apply_heredoc_with_expansion(current, env, status) == -1)
				return (-1);
		}
		else
		{
			if (process_redirection(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
