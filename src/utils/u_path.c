/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_path.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:53:04 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/21 15:30:27 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (find_command_path(cmd, ft_split(get_path_env(env), ':')));
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
