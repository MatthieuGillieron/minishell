#include "../../includes/minishell.h"

int	builtin_echo_status(t_status *status)
{
	printf("%d\n", status->exit_code);
	return (0);
}