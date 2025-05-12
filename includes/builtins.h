/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:46:02 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/12 15:36:15 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		check_builtin(char **argv, t_env **env);
int		builtin_cd(char **argv, t_env **env);
int		builtin_exit(char **argv);
int		builtin_unset(char **argv, t_env **env);
int		builtin_env(t_env *env);
int		builtin_pwd(void);
int		builtin_echo(char **argv);

/* Commande export et fonctions associées */
int		builtin_export(char **argv, t_env **env);
void	print_sorted_env(t_env *env);

#endif