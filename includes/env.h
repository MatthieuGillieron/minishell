/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:56:36 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/11 13:27:41 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

t_env	*init_env_list(char **envp);
char	*env_get(t_env *env, const char *key);
int		env_set(t_env **env, const char *key, const char *value);
int		env_unset(t_env **env, const char *key);
char	**env_to_array(t_env *env);
void	free_env_list(t_env *env);

#endif