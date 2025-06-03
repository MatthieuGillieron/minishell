#include "../../includes/minishell.h"

char	*expand_variables(char *str, t_env *env, t_status *status)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) * 4 + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			i = process_dollar(str, i, result, &j, env, status);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
