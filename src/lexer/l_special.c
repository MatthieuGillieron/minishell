#include "../../includes/minishell.h"

int	is_special_command(char *str, t_status *status)
{
	if (str[0] == '$' && str[1] && !is_whitespace(str[1]))
	{
		if (str[1] == '?' && (str[2] == '\0' || is_whitespace(str[2])))
			return (0);
			
		char *var_name = extract_var_name(&str[1]);
		if (var_name)
		{
			char *var_value = env_get(status->env, var_name);
			if (var_value)
				ft_putendl_fd(var_value, 1);
			else
				ft_putendl_fd("", 1);
			free(var_name);
			return (1);
		}
	}
	return (0);
}
