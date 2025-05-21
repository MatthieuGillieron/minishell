/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:53:08 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/21 16:47:51 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Initialise la liste chaînée des variables d'environnement à partir de envp.
 */
t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*node;
	char	*equal;
	int		i;

	head = NULL;
	i = 0;
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
 */
int	env_set(t_env **env, const char *key, const char *value)
{
	t_env	*tmp;
	t_env	*new_node;

	tmp = *env;
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
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
	return (0);
}

/**
 * Supprime une variable d'environnement de la liste.
 */
int	env_unset(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
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
 */
char	**env_to_array(t_env *env)
{
	char	**envp;
	char	*tmp;
	int		count;
	int		i;
	t_env	*iter;

	count = 0;
	iter = env;
	while (iter)
	{
		count++;
		iter = iter->next;
	}
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
