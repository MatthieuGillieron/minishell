#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

typedef struct s_expand
{
	char		*str;
	char		*result;
	int			i;
	int			*j;
	t_env		*env;
	t_status	*status;
}	t_expand;

#endif