/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:53:08 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/27 21:20:55 by mg               ###   ########.fr       */
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
	t_env	*last;
	char	*equal;
	int		i;

	head = NULL;
	last = NULL;
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
			node->next = NULL;
			
			if (!head)
				head = node;
			else
				last->next = node;
			last = node;
		}
		i++;
	}
	
	// Si PATH n'est pas défini, ajoutons un PATH par défaut
	if (!env_get(head, "PATH"))
	{
		node = malloc(sizeof(t_env));
		if (node)
		{
			node->key = ft_strdup("PATH");
			node->value = ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
			node->next = NULL;
			
			if (!head)
				head = node;
			else
				last->next = node;
		}
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
