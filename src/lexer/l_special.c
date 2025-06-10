#include "../../includes/minishell.h"

int	is_special_command(char *str, t_status *status)
{
	// Traiter le cas où l'utilisateur tape directement une variable d'environnement
	if (str[0] == '$' && str[1] && !is_whitespace(str[1]))
	{
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