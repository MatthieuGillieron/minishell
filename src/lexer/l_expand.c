/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:09:59 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:09:59 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_variables(char *str, t_env *env, t_status *status)
{
	t_expand	exp;
	char		*result;
	int			j;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) * 4 + 1);
	if (!result)
		return (NULL);
	j = 0;
	exp.str = str;
	exp.result = result;
	exp.i = 0;
	exp.j = &j;
	exp.env = env;
	exp.status = status;
	while (str[exp.i])
	{
		if (str[exp.i] == '$' && str[exp.i + 1] && str[exp.i + 1] != ' ')
			exp.i = process_dollar(&exp);
		else
			result[j++] = str[exp.i++];
	}
	result[j] = '\0';
	return (result);
}
