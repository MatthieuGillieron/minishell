/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:14:40 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:14:41 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*create_env_node(const char *entry)
{
	t_env	*node;
	char	*equal;

	equal = ft_strchr(entry, '=');
	if (!equal)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_substr(entry, 0, equal - entry);
	node->value = ft_strdup(equal + 1);
	node->next = NULL;
	return (node);
}
