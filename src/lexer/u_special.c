#include "../../includes/minishell.h"

int	is_special_command(char *str, t_status *status)
{
	if (ft_strcmp(str, "$?") == 0)
	{
		builtin_echo_status(status);
		return (1);
	}
	return (0);
}