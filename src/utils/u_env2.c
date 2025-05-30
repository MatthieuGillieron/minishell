#include "../includes/minishell.h"

/**
 * Libère toute la mémoire associée à la liste chaînée d’environnement.
 */
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

static int	count_env_elements(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/**
 * Convertit la liste chaînée d'environnement en tableau de strings "KEY=VALUE".
 */
char	**env_to_array(t_env *env)
{
	char	**envp;
	char	*tmp;
	int		count;
	int		i;

	count = count_env_elements(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		envp[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
