#include "../../includes/minishell.h"

/**
 * Extrait le nom d'une variable d'environnement
 * @param str La chaîne commençant par le nom de la variable
 * @return Le nom de la variable alloué dynamiquement
 */
char	*extract_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 0)
		return (NULL);
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

/**
 * Expande la variable $? avec le code de sortie
 * @param result Le buffer de résultat
 * @param j Pointeur sur l'index courant dans le buffer
 * @param status Structure contenant l'état du shell
 */
void	expand_exit_code(char *result, int *j, t_status *status)
{
	char	*exit_code;
	int		k;

	exit_code = ft_itoa(status->exit_code);
	if (!exit_code)
		return ;
	k = 0;
	while (exit_code[k])
		result[(*j)++] = exit_code[k++];
	free(exit_code);
}

/**
 * Expande une variable d'environnement spécifique
 * @param result Le buffer de résultat
 * @param j Pointeur sur l'index courant dans le buffer
 * @param var_name Nom de la variable à expandre
 * @param env L'environnement contenant les variables
 */
void	expand_env_var(char *result, int *j, char *var_name, t_env *env)
{
	char	*var_value;
	int		k;

	var_value = env_get(env, var_name);
	if (var_value)
	{
		k = 0;
		while (var_value[k])
			result[(*j)++] = var_value[k++];
	}
}

/**
 * Traite un caractère $ et expande la variable correspondante
 * @param str La chaîne d'entrée
 * @param i Index actuel dans la chaîne d'entrée
 * @param result Buffer de résultat
 * @param j Pointeur sur l'index courant dans le buffer
 * @param env L'environnement contenant les variables
 * @param status Structure contenant l'état du shell
 * @return Nouvel index dans la chaîne d'entrée après traitement
 */
int		process_dollar(char *str, int i, char *result, int *j,
						t_env *env, t_status *status)
{
	char	*var_name;
	int		name_len;

	i++;  // Avancer après le $
	if (str[i] == '?')
	{
		expand_exit_code(result, j, status);
		return (i + 1);
	}
	var_name = extract_var_name(&str[i]);
	if (var_name)
	{
		expand_env_var(result, j, var_name, env);
		name_len = ft_strlen(var_name);
		free(var_name);
		return (i + name_len);
	}
	// Si ce n'est pas une variable valide, on garde le $ tel quel
	result[(*j)++] = '$';
	return (i);
}
