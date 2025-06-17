/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:16:02 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:16:03 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

t_env	*init_env_list(char **envp);
char	*env_get(t_env *env, const char *key);
int		env_set(t_env **env, const char *key, const char *value);
int		env_unset(t_env **env, const char *key);
void	free_env_list(t_env *env);
char	**env_to_array(t_env *env);

t_env	*create_env_node(const char *entry);
void	add_default_path_if_missing(t_env **head);

#endif