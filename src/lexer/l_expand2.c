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

int	process_dollar(char *str, int i, char *result, int *j,
		t_env *env, t_status *status)
{
	char	*var_name;
	int		name_len;

	i++;
	if (str[i] == '?')
	{
		expand_exit_code(result, j, status);
		return (i + 1);
	}
	var_name = extract_var_name(&str[i]);
	if (var_name)
	{
		expand_env_var(result, j, var_name, env);
		name_len = ft_strlen(var_name);
		free(var_name);
		return (i + name_len);
	}
	result[(*j)++] = '$';
	return (i);
}
