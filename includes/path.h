/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:16:28 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:16:29 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

char	*find_command_path(char *cmd, char **paths);
char	*get_path_env(t_env *env);
char	*join_path(char *path, char *cmd);
void	free_split(char **split);
char	*get_command_path(char *cmd, t_env *env);

#endif