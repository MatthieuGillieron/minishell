/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:57:02 by mg                #+#    #+#             */
/*   Updated: 2025/05/12 14:45:57 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

struct s_env;
typedef struct s_env t_env;

int		builtin_export(char **argv, t_env **env);
void	print_sorted_env(t_env *env);

#endif