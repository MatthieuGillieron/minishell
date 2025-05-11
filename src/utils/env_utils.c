/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:53:08 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/11 13:59:45 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/**
 * Initialise la liste chaînée des variables d'environnement à partir de envp.
 *
 * @param envp Tableau classique des variables d'environnement.
 * @return La tête de la liste chaînée nouvellement créée.
 */
t_env	*init_env_list(char **envp)
{
	t_env	*head = NULL;
	t_env	*node;
	char	*equal;
	int		i = 0;

	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			node = malloc(sizeof(t_env));
			if (!node)
				return (NULL);
			node->key = ft_substr(envp[i], 0, equal - envp[i]);
			node->value = ft_strdup(equal + 1);
			node->next = head;
			head = node;
		}
		i++;
	}
	return (head);
}

/**
 * Récupère la valeur associée à une clé donnée dans la liste env.
 *
 * @param env Liste des variables d'environnement.
 * @param key Nom de la variable recherchée.
 * @return La valeur de la variable, ou NULL si non trouvée.
 */
char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * Modifie ou ajoute une variable d'environnement dans la liste.
 *
 * @param env Pointeur vers la liste des variables d'environnement.
 * @param key Nom de la variable.
 * @param value Valeur de la variable.
 * @return 0 si succès, 1 en cas d'erreur d'allocation.
 */
int	env_set(t_env **env, const char *key, const char *value)
{
	t_env	*tmp = *env;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return (1);
	tmp->key = ft_strdup(key);
	tmp->value = ft_strdup(value);
	tmp->next = *env;
	*env = tmp;
	return (0);
}

/**
 * Supprime une variable d'environnement de la liste.
 *
 * @param env Pointeur vers la liste des variables.
 * @param key Nom de la variable à supprimer.
 * @return 0 si la variable est supprimée ou non trouvée.
 */
int	env_unset(t_env **env, const char *key)
{
	t_env	*curr = *env;
	t_env	*prev = NULL;

	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

/**
 * Convertit la liste chaînée d'environnement en tableau de strings "KEY=VALUE".
 *
 * @param env Liste des variables d’environnement.
 * @return Tableau de chaînes au format classique pour execve.
 */
char	**env_to_array(t_env *env)
{
	char	**envp;
	char	*tmp;
	int		count = 0;
	int		i = 0;
	t_env	*iter = env;

	while (iter && ++count)
		iter = iter->next;
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		envp[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

/**
 * Libère toute la mémoire associée à la liste chaînée d’environnement.
 *
 * @param env Liste à libérer.
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
