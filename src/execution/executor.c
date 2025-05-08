/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:14:37 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/08 18:22:57 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_command(char **argv, char **envp)
{
	pid_t	pid;
	char	*path;
	int		status;

	path = NULL;
	if (ft_strchr(argv[0], '/'))
		path = ft_strdup(argv[0]);
	else
		path = find_command_path(argv[0], envp);
	if (!path)
		return (ft_putstr_fd("command not found: ", 2),
			ft_putendl_fd(argv[0], 2));
	pid = fork();
	if (pid == 0)
	{
		execve(path, argv, envp);
		perror("execve");
		exit(1);
	}
	if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
	free(path);
}
