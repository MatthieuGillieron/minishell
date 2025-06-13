#include "../includes/minishell.h"

int	builtin_echo(char **args)
{
	int	i;
	int	n_flag;
	int	j;

	n_flag = 0;
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0' && j > 1)
		{
			n_flag = 1;
			i++;
		}
		else
			break;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	
	return (0);
}
