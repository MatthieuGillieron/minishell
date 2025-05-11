/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:46:02 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/11 13:39:06 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	check_builtin(char **argv, t_env *env);
int	builtin_cd(char **argv, t_env **env);
int	builtin_exit(char **argv);
int	builtin_unset(char **argv, t_env **env);
int	builtin_env(t_env *env);
int	builtin_pwd(void);
int	builtin_echo(char **argv);

#endif