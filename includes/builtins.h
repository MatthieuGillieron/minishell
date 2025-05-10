/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:46:02 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/10 12:04:02 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		check_builtin(char **argv);
void	builtin_pwd(void);
void	builtin_echo(char **argv);
void	builtin_env(void);
int		builtin_cd(char **argv);

#endif