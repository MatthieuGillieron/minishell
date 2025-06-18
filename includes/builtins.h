/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magillie <magillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:15:58 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 16:23:49 by magillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		check_builtin(char **argv, t_env **env, t_status *status);
int		builtin_cd(char **argv, t_env **env);
int		builtin_exit(char **argv);
int		builtin_unset(char **argv, t_env **env);
int		builtin_env(t_env *env);
int		builtin_pwd(void);
int		builtin_echo(char **argv);
int		builtin_echo_status(t_status *status);

/* Commande export et fonctions associées */
int		builtin_export(char **argv, t_env **env);
void	print_sorted_env(t_env *env);
int		handle_export_no_value(char *arg, t_env **env);

#endif