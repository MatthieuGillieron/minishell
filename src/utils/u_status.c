/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:47:01 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/23 14:47:01 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_status *get_status(void)
{
	static t_status status = {0};
	return (&status);
}
