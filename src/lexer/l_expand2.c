/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_expand2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:10:03 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:10:04 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 0)
		return (NULL);
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

void	expand_exit_code(char *result, int *j, t_status *status)
{
	char	*exit_code;
	int		k;

	exit_code = ft_itoa(status->exit_code);
	if (!exit_code)
		return ;
	k = 0;
	while (exit_code[k])
		result[(*j)++] = exit_code[k++];
	free(exit_code);
}

void	expand_env_var(char *result, int *j, char *var_name, t_env *env)
{
	char	*var_value;
	int		k;

	var_value = env_get(env, var_name);
	if (var_value)
	{
		k = 0;
		while (var_value[k])
			result[(*j)++] = var_value[k++];
	}
}

static int	handle_question_mark(t_expand *exp)
{
	expand_exit_code(exp->result, exp->j, exp->status);
	return (exp->i + 1);
}

int	process_dollar(t_expand *exp)
{
	char	*var_name;
	int		name_len;

	exp->i++;
	if (exp->str[exp->i] == '?')
		return (handle_question_mark(exp));
	var_name = extract_var_name(&exp->str[exp->i]);
	if (var_name)
	{
		expand_env_var(exp->result, exp->j, var_name, exp->env);
		name_len = ft_strlen(var_name);
		free(var_name);
		return (exp->i + name_len);
	}
	exp->result[(*exp->j)++] = '$';
	return (exp->i);
}
