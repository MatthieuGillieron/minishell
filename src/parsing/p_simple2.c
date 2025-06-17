/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_simple2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:12:16 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:12:17 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

int	add_redirect(t_simple_cmd *cmd, t_redirect *redirect)
{
	t_redirect	*current;

	if (!cmd->redirects)
		cmd->redirects = redirect;
	else
	{
		current = cmd->redirects;
		while (current->next)
			current = current->next;
		current->next = redirect;
	}
	return (1);
}
