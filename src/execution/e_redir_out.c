/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:09:46 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:09:47 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Applique une redirection de sortie (>)
 * @param file_path Chemin du fichier à ouvrir en écriture
 * @return 0 si succès, -1 si erreur
 */
int	apply_output_redirection(char *file_path)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/**
 * Applique une redirection de sortie en mode append (>>)
 * @param file_path Chemin du fichier à ouvrir en écriture (append)
 * @return 0 si succès, -1 si erreur
 */
int	apply_append_redirection(char *file_path)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
