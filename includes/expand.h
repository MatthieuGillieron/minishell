/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:16:10 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:16:10 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

//  *** Forward declarations ***
struct						s_env;
typedef struct s_env		t_env;

struct						s_status;
typedef struct s_status		t_status;

typedef struct s_expand
{
	char		*str;
	char		*result;
	int			i;
	int			*j;
	t_env		*env;
	t_status	*status;
}	t_expand;

#endif