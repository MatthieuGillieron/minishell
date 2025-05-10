/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:46:02 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/10 15:28:39 by mtaramar         ###   ########.fr       */
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