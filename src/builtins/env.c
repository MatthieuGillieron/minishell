#include "../includes/minishell.h"

/**
 * builtin_env - Affiche les variables d'environnement avec valeur.
 * @env: Liste chainée t_env.
 * 
 * Retourne toujours 0.
 */
int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
