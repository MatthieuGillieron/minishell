/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env_principal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:14:44 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:14:45 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function prototype for the helper function in u_env_principal2.c */
t_env	*create_env_node_with_kv(const char *key, const char *value);

static void	setup_default_env(t_env **head)
{
	char	cwd[1024];

	env_set(head, "TERM", "xterm-256color");
	if (getcwd(cwd, sizeof(cwd)))
		env_set(head, "PWD", cwd);
}

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*node;
	t_env	*last;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (node)
		{
			if (!head)
				head = node;
			else
				last->next = node;
			last = node;
		}
		i++;
	}
	if (!head)
		setup_default_env(&head);
	return (head);
}

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
	new_node = create_env_node_with_kv(key, value);
	if (!new_node)
		return (1);
	new_node->next = *env;
	*env = new_node;
	return (0);
}

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
