/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:13:28 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/26 17:09:57 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void	execute_command(char **argv, t_env **env, t_status *status);
void	execute_parsed_command(t_command *cmd, t_env **env, t_status *status);

#endif