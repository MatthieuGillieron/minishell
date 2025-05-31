#include "../includes/minishell.h"

/**
 * Tente de trouver un chemin exécutable valide pour une commande.
 * Construit un chemin complet avec chaque dossier de PATH
 * et vérifie avec access() si la commande y est exécutable.
 *
 * @param cmd Le nom de la commande.
 * @param paths Un tableau de chemins extraits de PATH.
 * @return Un chemin alloué contenant la commande valide, ou NULL.
 */
char	*find_command_path(char *cmd, char **paths)
{
	char	*path;
	char	*tmp;
	int		i;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (free_split(paths), path);
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

/**
 * Recherche la variable PATH dans la liste chaînée de l’environnement.
 *
 * @param env La liste chaînée contenant les paires clé/valeur.
 * @return Une chaîne représentant la valeur de PATH, ou NULL si absente.
 */
char	*get_path_env(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char *join_path(char *path, char *cmd)
{
	char *tmp;
	char *result;
	
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	
	result = ft_strjoin(tmp, cmd);
	free(tmp);
	
	return (result);
}

/**
 * Retourne le chemin complet vers une commande, en vérifiant
 * si elle est absolue ou en la recherchant dans les dossiers de PATH.
 *
 * @param cmd La commande à exécuter.
 * @param env L’environnement sous forme de liste chaînée.
 * @return Une chaîne allouée avec le chemin trouvé, ou NULL.
 */
char	*get_command_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	
	// Si la commande contient un '/', c'est déjà un chemin
	if (ft_strchr(cmd, '/'))
	{
		// Vérifier si le fichier est exécutable
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = env_get(env, "PATH");
	if (!path_env)
		return (NULL);    
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
		
	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}


/**
 * Libère un tableau de chaînes alloué dynamiquement.
 *
 * @param split Le tableau à libérer.
 */
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
