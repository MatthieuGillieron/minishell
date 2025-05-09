/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:53:19 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/09 10:52:43 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

char	*get_path_env(char **envp);
char	*find_command_path(char *cmd, char **envp);
void	free_split(char **split);
char	*get_command_path(char *cmd, char **envp);

#endif
