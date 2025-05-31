#include "../../includes/minishell.h"

/**
 * Expande les variables d'environnement dans une chaîne
 * @param str La chaîne contenant potentiellement des variables
 * @param env L'environnement contenant les variables
 * @param status Structure contenant l'état du shell
 * @return Une nouvelle chaîne avec les variables remplacées
 */
char	*expand_variables(char *str, t_env *env, t_status *status)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	// Allocation généreuse pour éviter les problèmes de taille
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
