/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:53:19 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/27 12:01:32 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

char	*get_path_env(t_env *env);
char	*get_command_path(char *cmd, t_env *env);
void	free_split(char **split);
char	*get_command_path(char *cmd, t_env *env);
char *join_path(char *path, char *cmd);

#endif
