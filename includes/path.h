/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:53:19 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/11 13:42:12 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

char	*get_path_env(t_env *env);
char	*get_command_path(char *cmd, t_env *env);
void	free_split(char **split);
char	*get_command_path(char *cmd, t_env *env);

#endif
